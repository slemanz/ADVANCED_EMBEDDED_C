# Linker and Startup

Between the last object file and a chip that actually runs, two things have to
happen that no desktop program worries about. Someone has to assign the real
flash and RAM addresses of every section, and someone has to run before `main`
to move initialized data into RAM, zero the rest, and point the core at the
vector table. That someone is the linker script plus the startup code. This is
the part of the build that fades from memory fastest, so this module keeps the
smallest complete example: one blink, one linker script, one hand-written
startup, and the dumps that show where everything landed.

## The idea

Two files do the work. [linker.ld](linker.ld) is the memory map and section
placement, the *locating* step. [startup.c](startup.c) is the vector table and
the `Reset_Handler` that runs first and hands control to `main`.

### VMA and LMA, the one idea the rest hangs on

A section has two addresses. The **LMA** (load memory address) is where its
bytes sit in the image that gets burned to flash. The **VMA** (virtual, or run,
address) is where the code expects to find them while executing. For `.text`
they are the same, because code runs straight out of flash. For `.data` they
differ, and that difference is the entire reason startup code exists.
`objdump -h` on the linked ELF ([flash.txt](flash.txt)) shows it:

```
Idx Name    Size      VMA       LMA
  0 .text   0000033c  08000000  08000000
  1 .data   00000004  20000000  0800033c
  2 .bss    0000000c  20000004  08000340
```

`.data` runs at `0x20000000` in SRAM but is stored at `0x0800033c` in flash,
right after `.text` ends. It has to be stored there, because RAM is empty at
power-on and the initial value has to live somewhere non-volatile. Compare the
same dump on `main.o` before linking ([main.txt](main.txt)): every VMA and LMA
is `0`, the addresses are unassigned. Locating is what filled that table in.

The `> SRAM AT> FLASH` in the script says exactly this: put the section's VMA in
SRAM, but its LMA (its stored copy) in FLASH.

### The linker script

The `MEMORY` block names the regions the part actually has: FLASH `rx` at
`0x08000000`, SRAM `rwx` at `0x20000000`, with the sizes written as the script
sees them (256K and 60K here). `ENTRY(Reset_Handler)` names the first function.
`_estack` is set to the top of SRAM, because the stack grows downward from
there.

`SECTIONS` decides the order and destination of each output section. `.text`
comes first and takes the vector table, then the code, then read-only data, all
into FLASH. `.data` and `.bss` go to SRAM. The location counter `.` tracks the
current address, `ALIGN(4)` pads to a word boundary, and the script defines
boundary symbols the startup code will read back:

```
.data :
{
    _sdata = .;      /* start of .data in SRAM */
    *(.data)
    _edata = .;      /* end of .data */
} > SRAM AT> FLASH   /* VMA in SRAM, LMA in FLASH */
```

A linker symbol is an address, not a variable. `_sdata` does not hold a value,
`_sdata` *is* the address where `.data` begins. That is why the startup code
takes `&_sdata`, not `_sdata`.

One asymmetry worth seeing: `.bss` has no stored image. In [flash.txt](flash.txt)
it is marked `ALLOC` only, no `LOAD`, no `CONTENTS`. It just needs to exist in
RAM and be zeroed, so its LMA is meaningless and the `AT> FLASH` on it does
nothing. Only `.data` needs a flash copy, because only `.data` has non-zero
initial values to preserve.

### What runs before main

`Reset_Handler` is the second word of the vector table, the address the core
loads into the program counter at reset (the first word is the initial stack
pointer). It does three things and then calls `main`:

```c
uint32_t *src = (uint32_t *)&_etext;   /* .data image, in flash          */
uint32_t *dst = (uint32_t *)&_sdata;   /* .data home,  in SRAM           */
/* 1. copy .data from its LMA to its VMA, up to _edata */
/* 2. zero .bss from _sbss to _ebss                    */
/* 3. main();                                          */
```

The stakes are visible in [main.c](main.c). `led_data = 27` is a `.data`
variable: the `27` lives in flash, the variable lives in SRAM, and it only reads
back as `27` because step 1 copied it across. `led_data0 = 0`, `led_size`, and
`led_length` are `.bss`: they only read as `0` because step 2 zeroed them. Skip
the startup code and every one of these globals holds garbage. That is the whole
job made concrete.

### The vector table

The table is an array placed in section `.isr_vector_tbl`, which the script
forces to the very front of flash (`0x08000000`) so the core finds it at reset.
The map file confirms `vector_tbl` sitting at `0x08000000`. Word 0 is the
initial stack pointer (`&_estack`), word 1 is `Reset_Handler`, and the rest are
the exception and interrupt handlers in the fixed order the Cortex-M4 expects,
with `0` in the reserved slots.

Every handler is declared like this:

```c
void USART2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
```

`Default_Handler` is a placeholder that loops forever. `weak` means any
strong definition wins, so writing `void USART2_IRQHandler(void) { ... }`
anywhere in the application silently takes over that slot, no table edit needed.
That is the mechanism behind every driver that "just works" by defining its
handler. When a script uses `--gc-sections`, `KEEP()` is what stops the linker
from discarding the vector table as unreferenced; this script keeps it simply by
not garbage-collecting.

## When to use it (and when not to)

You rarely write these from scratch. The vendor ships a startup file and a
linker script (that is [cmsis](../cmsis/)), and that is the right default. You
reach for a hand-written pair when the stock map does not fit: a bootloader that
carves out a slot, an application linked to run above a bootloader, code copied
into RAM for speed, or a custom section for a config block or a region shared
between two images. The bootloader work in this repo is exactly that
([../../bootloader](../../bootloader/)). Knowing the copy-and-zero is also what
lets you debug the classic symptom where a global reads correctly in the
debugger's flash view but is garbage at runtime: the `.data` copy never ran, or
a boundary symbol is wrong.

The cost is that you now own the correctness of the earliest code on the chip,
before any tool can help you. A wrong symbol or an off-by-one in the copy loop
faults before `main` and presents as a dead board with nothing to attach to.

Noted in this code, not fixed: the copy and zero loops use the byte count
(`&_edata - &_sdata`) as an iteration count while advancing a `uint32_t *`, so
each loop moves four times as many bytes as the section holds and runs past its
end. It survives here only because the sections are a few words and the overrun
lands in adjacent RAM that is about to be zeroed anyway. The usual forms compare
the pointer against the end symbol (`while (dst < &_edata)`) or divide the size
by four. Separately, `__max_heap_size` and `__max_stack_size` are defined but
never used to reserve or guard space, so nothing here catches a stack that grows
down into `.bss`.

## Build and run

Not the shared Makefile. This one is compiled by hand so every artifact stays on
disk to read. Cortex-M4, 256K flash and 60K RAM as the script is written, and it
blinks PA5.

```bash
arm-none-eabi-gcc -c -mcpu=cortex-m4 -mthumb -std=gnu99 main.c    -o main.o
arm-none-eabi-gcc -c -mcpu=cortex-m4 -mthumb -std=gnu99 startup.c -o startup.o
arm-none-eabi-gcc -nostdlib -T linker.ld *.o -o flash.elf -Wl,-Map=flash.map
```

`-nostdlib` because there is no C library and no default startup here: the
linker script and `startup.c` are the entire runtime. Then dump the sections and
flash it:

```bash
arm-none-eabi-objdump -h flash.elf > flash.txt   # VMA/LMA after locating
arm-none-eabi-objdump -h main.o    > main.txt    # same, before locating (all zero)
openocd -f interface/stlink-v2.cfg -f target/stm32f4x.cfg \
  -c init -c "reset init" -c "flash write_image erase flash.elf" -c "reset run" -c shutdown
```

The map file is where you read the final layout: every symbol's address, every
section's placement, and the `region FLASH overflowed` message when the image
does not fit. This picks up where [build-process](../build-process/) stopped,
which ended with an object file whose sections were still at address zero.

## Files

- [linker.ld](linker.ld): the memory map, section placement, and boundary
  symbols.
- [startup.c](startup.c): the vector table with weak-aliased handlers and the
  `Reset_Handler` that copies `.data`, zeroes `.bss`, and calls `main`.
- [main.c](main.c): a PA5 blink whose `.data` (`led_data = 27`) and `.bss`
  globals make the copy-and-zero observable.
- [flash.txt](flash.txt): `objdump -h` of the linked ELF, the VMA/LMA split.
- [main.txt](main.txt) and [startup.txt](startup.txt): `objdump -h` before
  locating; `startup.txt` shows `.isr_vector_tbl` as its own section.
- [flash.map](flash.map): the full link map, symbol addresses and section
  placement.

For the vendor-supplied version of all this see [cmsis](../cmsis/), for the
Makefile that drives a real build see [the-make](../the-make/), and for where it
gets used in anger see [the bootloader](../../bootloader/).
