# CMSIS

Every module before this one poked registers through hand-written macros like
`#define GPIOA_ODR (*(volatile unsigned int *)(0x40020014))`. That works, but
each project reinvents it, the addresses are magic numbers, and nothing stops
you from writing to a read-only register. CMSIS (Cortex Microcontroller Software
Interface Standard) is Arm's standard answer: a vendor-supplied set of headers
that turn those raw addresses into typed, named register structs, plus a
matching startup file and a clock-init file. Same blink, now written
`GPIOA->ODR ^= (1 << 5)`.

## The idea

The earlier modules reached a register like this:

```c
#define GPIOA_ODR (*(volatile unsigned int *)(0x40020000 + 0x14))
GPIOA_ODR ^= (1 << 5);
```

This module, after `#include "stm32f401xe.h"`, writes:

```c
GPIOA->ODR ^= (1 << 5);
```

`GPIOA` comes from the device header, which defines a struct whose members sit at
each register's real offset, then points a pointer at the peripheral's base
address:

```c
typedef struct {
  __IO uint32_t MODER;    /* offset 0x00 */
  /* ... */
  __IO uint32_t ODR;      /* offset 0x14 */
  /* ... */
} GPIO_TypeDef;

#define GPIOA ((GPIO_TypeDef *) GPIOA_BASE)   /* 0x40020000 */
```

So `GPIOA->ODR` resolves to the same `*(volatile uint32_t *)0x40020014` you wrote
by hand. The difference is that the offset now comes from the struct layout, the
name comes straight from the reference manual, and the type carries both the
`volatile` and the access rights.

That `__IO` in front of every member is a CMSIS qualifier, and it is where the
read/write intent lives:

| CMSIS qualifier | Expands to | Register access |
| --- | --- | --- |
| `__I` | `volatile const` | read only |
| `__O` | `volatile` | write only |
| `__IO` | `volatile` | read and write |

The `volatile` forces the real load or store on every access (the
[optimized](../optimized/) story), and the `const` on `__I` makes the compiler
reject a write to a read-only register at build time instead of letting it fault
at runtime.

### The three files CMSIS adds

A full CMSIS bring-up wires three files into a project:

- the **startup file**, carrying the CMSIS vector table and `Reset_Handler`;
- **`system_<device>.c`**, whose `SystemInit()` sets up the clock tree (PLL,
  flash wait states) before `main`;
- the **device header** (`stm32f401xe.h` here), which pulls in the core headers
  (`core_cm4.h`, `cmsis_gcc.h`) and defines every peripheral struct and base
  address.

This example only wires up the third one. It keeps the hand-written `startup.c`
and `linker.ld` from [linker-startup](../linker-startup/) and never calls
`SystemInit`, so it runs at the chip's reset-default clock, the internal 16 MHz
oscillator. That is enough to blink an LED. The moment you want the PLL and full
speed, that is exactly what the `system_` file is for.

### What is in the box

The device header is one slice of CMSIS. The standard also ships:

- **Core (CMSIS-M):** register definitions and intrinsics for the Cortex-M core
  itself (NVIC, SysTick, SCB), the part that is identical across every vendor's
  M4.
- **DSP:** a fixed and floating point math library tuned for the SIMD
  instructions.
- **Driver:** generic peripheral interfaces (UART, SPI, I2C) for middleware to
  sit on.
- **RTOS, PACK, DAP** and others, down to the debug-probe protocol.

The point of all of it is portability: core access and peripheral names look the
same across vendors and toolchains, so code and middleware move between parts
with less rework. The coding standard leans on MISRA C, which is why the headers
use `uint32_t` everywhere instead of `unsigned int`.

## When to use it (and when not to)

Use CMSIS whenever you are not deliberately writing the register layer by hand,
which is almost always. The device header is the sane default even for bare-metal
work: you get the reference-manual names, the correct offsets, and the
access-type checking for free, and you stop copying magic addresses into a
`#define` block that the next chip will silently break. It is also the layer the
vendor HAL is built on, so you can drop from HAL calls to raw CMSIS register
access in the same file without changing headers.

When not to: the hand-rolled macro style of the earlier modules is worth keeping
for exactly one purpose, seeing what the struct hides. Once you know that
`GPIOA->ODR` is a cast to a fixed address, the raw form has done its teaching and
CMSIS is the version you ship. And CMSIS names registers, it does not abstract
peripheral behaviour: it will not make an F4 UART act like an F7 UART. The
portability is real but skin deep, at the register-name level.

The cost in code is essentially nothing (the structs compile to the same loads
and stores) plus one include path in the build. The one real trap is the missing
`SystemInit`: include the device header, assume the clock is configured, and you
will be debugging why every timing is off when the chip is actually sitting at
its reset default.

## Build and run

Cortex-M4 (STM32F401), device header in `Inc/`. The Makefile is the
[the-make](../the-make/) one plus an include path:

```
INCLUDES += -I Inc/
main.o : main.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^
```

```bash
make          # builds flash.elf
make load     # flashes with OpenOCD over ST-Link
make clean
```

It blinks PA5 at the reset-default clock. Only `main.o` gets the include path,
because `startup.c` never touches the device header.

## Files

- [main.c](main.c): the blink, written against CMSIS structs (`GPIOA->ODR`,
  `RCC->AHB1ENR`).
- [Inc/stm32f401xe.h](Inc/stm32f401xe.h): the device header, every peripheral
  struct and base address.
- [Inc/core_cm4.h](Inc/core_cm4.h) and the `cmsis_*.h` / `mpu_armv7.h` files: the
  Arm core headers the device header pulls in.
- [Inc/system_stm32f4xx.h](Inc/system_stm32f4xx.h): the clock-init interface
  (`SystemInit`), present but unused by this example.
- [startup.c](startup.c) and [linker.ld](linker.ld): the hand-written startup and
  script from [linker-startup](../linker-startup/), reused unchanged. A full
  CMSIS setup would replace both with the vendor's versions.
- [Makefile](Makefile): the-make's Makefile with `-I Inc/` added.

The register-poking modules before this one ([build-process](../build-process/)
and [linker-startup](../linker-startup/)) are the by-hand version of what CMSIS
packages.
