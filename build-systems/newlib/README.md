# Newlib

`printf`, `snprintf`, `malloc`, and every standard header are just C. On a hosted
system the operating system sits under the library and provides `write`, `read`,
`sbrk`, and the rest, which is where those functions bottom out. Bare metal has no
operating system, so the library's bottom layer is missing. Newlib is the
embedded C library, but it still expects that layer to exist. This module supplies
it: the syscall stubs, a startup that runs the library's initializers, and a
linker script that places the sections newlib generates. It is the capstone of
this block, because it uses every piece before it.

## The idea

Newlib is linked in by default with `arm-none-eabi-gcc`. You opt out with
`-nostdlib`, which is exactly what [linker-startup](../linker-startup/) and
[the-make](../the-make/) did to stay minimal. Once it is in, calling `printf`
pulls the library, and the library calls down to functions it assumes the "OS"
provides. Supply them and it links. Leave one out and you get the `undefined
reference to _write` link error from the [build-process](../build-process/)
story.

### The retarget chain

The path that matters is output. `printf` formats into a buffer and calls
`_write`. The `_write` in [syscalls.c](linkers/syscalls.c) knows nothing about
UARTs; it loops over the bytes calling `__io_putchar`:

```c
int _write(int file, char *ptr, int len) {
    for (int i = 0; i < len; i++) __io_putchar(*ptr++);
    return len;
}
```

`__io_putchar` is the hook, and [constructors.c](linkers/constructors.c) points
it at the serial port:

```c
int __io_putchar(int ch) { uart2_write_byte((uint8_t)ch); return ch; }
```

So the full path is `printf` -> `_write` -> `__io_putchar` -> `uart2_write_byte`.
That chain is what "retarget printf to UART" means, and it is why the same
`printf("Init the board\n")` in [main.c](app/Src/main.c) comes out of USART2
instead of nowhere. Point `__io_putchar` at a different sink and every `printf`
follows. Semihosting is the same idea with `_write` aimed at the debugger instead
(see [semihosting](../semihosting/)).

`_fstat` returning `S_IFCHR` tells newlib that stdout is a character device, which
keeps output unbuffered and byte-at-a-time, so each character reaches the UART as
it is written.

### The heap

`malloc` bottoms out at `_sbrk`, which grows the heap upward from the `end` symbol
(the top of `.bss`, defined by the linker) toward the stack:

```c
if (heap_end + incr > stack_ptr) { errno = ENOMEM; return (caddr_t)-1; }
```

That single comparison is the entire protection between heap and stack on a part
with no MMU. It checks the stack pointer at the instant `sbrk` runs, and nothing
stops the stack from later growing down into memory that was already handed out.
This is the concrete version of the warning in
[memory](../../data-structures/memory/): you can have `malloc`, but the
fragmentation and the silent collision are exactly why most firmware does not.

The remaining stubs (`_close`, `_lseek`, `_open`, `_kill`, `_getpid`, `_fork`, and
the rest) are minimal: return an error or a fixed answer. They exist only because
newlib references them, and each missing one is a link error, not a runtime
feature.

### Running the library's initializers

`linker-startup` established that `Reset_Handler` copies `.data` and zeroes
`.bss`. A newlib startup adds one line before `main`:

```c
copy_data();
clear_bss();
__libc_init_array();   /* run the constructors collected in .init_array */
main();
```

`__libc_init_array()` walks the `.init_array` section and calls every function in
it: C++ static constructors, and any C function marked
`__attribute__((constructor))`. Here that is `serial_init` in constructors.c,
which calls `uart2_init()`. So the UART is up before the first `printf`, with no
explicit call at the top of `main`. The tradeoff is that the init is now invisible
in `main`: it runs automatically, which is convenient and also easy to forget is
happening.

### The sections newlib adds

A minimal script placing `.text`, `.data`, and `.bss` is no longer enough.
Building with newlib and constructors generates more sections the script must
place:

```
.init_array          pointers __libc_init_array walks (the constructors)
.fini_array          destructors, for completeness
.init / .fini        libc init and fini code
.ARM.exidx           exception unwind tables
._user_heap_stack    the reserved heap and stack region
```

Miss `.init_array` and the constructors silently never run: the UART stays dead
and `printf` goes nowhere. The full script is in [linker.ld](linkers/linker.ld),
which is why a real libc build needs the complete script, not the hand-cut one
from linker-startup.

### The build flags that select newlib

[The Makefile](Makefile) carries the knobs:

- `--specs=nano.specs` picks newlib-nano, the size-optimized variant (smaller
  `printf` and `malloc`). Default newlib is bigger, and `--specs=nosys.specs`
  gives stubs that just fail. This is the same `--specs` switch
  [semihosting](../semihosting/) used to select `rdimon`.
- `-u _printf_float` force-references the floating-point `printf` code, because
  nano's `printf` drops `%f` to save space. Without this flag `%f` prints nothing
  or garbage, a classic afternoon lost. With it, floats print and the binary
  grows.
- `-Wl,--print-memory-usage` prints flash and RAM totals after the link, which is
  what you watch when the libc starts eating the budget.
- `-mfloat-abi=hard` uses the FPU, which the F4 has and `driver_fpu.c` enables.

## When to use it (and when not to)

Newlib is the default and the right one whenever you want standard headers,
formatted output, and the familiar library. The retarget (`_write` to UART) plus a
constructor for early init is the standard bring-up on any Cortex-M, and it is
what this whole repo assumes.

Where to hold back is inside newlib, not around it:

- **Flash.** Pulling in `printf` and friends costs kilobytes; here `.text` is
  around 25 KB, most of it library. `nano.specs` shrinks it, but on a small part
  it is real, and it is why a code-size number has to say which libc it used.
- **The heap.** `malloc` works, but `_sbrk` guards heap against stack with one
  runtime compare and no MMU. On firmware that runs for months, the fragmentation
  and collision risk from [memory](../../data-structures/memory/) still apply, so
  most designs keep the library and skip its allocator, using static buffers and
  [pools](../../data-structures/pools/) instead.
- **`printf` on a real-time path.** It is large, slow, and not reentrant. Call it
  from both an ISR and the main loop and the output interleaves or corrupts. For
  logging on a hot path, a lighter custom formatter or a UART ring buffer beats
  it.

So the practical shape is: link newlib, retarget output, run constructors, then
mostly stay in the static, allocation-free style the rest of the repo argues for,
reaching into the library for formatting and headers rather than for the heap.

Noted in this code, not fixed: `Reset_Handler` resets the main stack pointer with
`MSR MSP` after `__libc_init_array()` has already run and right before `main()`.
Doing that in the middle of a C function, after calls, is fragile, because the
compiler may hold values relative to the old `SP`. And `_sbrk`'s collision check
only sees the stack pointer at call time, so a later stack growth into the heap
goes undetected, the fundamental heap-stack fragility above. The Makefile also
carries the same non-`.PHONY` and missing linker-script-dependency gaps flagged in
[the-make](../the-make/).

## Build and run

STM32F401 with the FPU on, USART2 for the retargeted output. It is a full build:
app, drivers, syscalls, startup, and constructors.

```bash
make          # builds Build/flash.elf and flash.bin, prints size and memory usage
make load     # flash with OpenOCD over ST-Link
make clean
```

`printf("Init the board\n\r")` appears on USART2, and PA5 toggles once a second.
`--print-memory-usage` reports the flash and RAM the libc build consumes.

## Files

- [linkers/syscalls.c](linkers/syscalls.c): the syscall layer, `_write` / `_read`
  / `_sbrk` and the minimal stubs.
- [linkers/constructors.c](linkers/constructors.c): `__io_putchar` (the UART
  retarget) and `serial_init` (the constructor that runs `uart2_init` before
  `main`).
- [linkers/startup.c](linkers/startup.c): the `Reset_Handler` with
  `__libc_init_array()` added.
- [linkers/linker.ld](linkers/linker.ld): the full script placing `.init_array`,
  `.fini_array`, and the heap and stack region.
- [app/Src/main.c](app/Src/main.c): the app, one `printf` and a 1 Hz blink.
- [Drivers/](Drivers/): the GPIO, UART, SysTick, and FPU drivers.
- [Makefile](Makefile): the `--specs=nano.specs`, `-u _printf_float`, and
  memory-usage flags.

### References

- [The most thoroughly commented linker script (probably)](https://blog.thea.codes/the-most-thoroughly-commented-linker-script/)
- [From Zero to main(): Bootstrapping libc with Newlib](https://interrupt.memfault.com/blog/boostrapping-libc-with-newlib)
- [How a Microcontroller starts](https://www.youtube.com/watch?v=MhOba73z-dQ)
