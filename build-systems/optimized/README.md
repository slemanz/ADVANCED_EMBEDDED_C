# Optimization

The optimizer has two goals that pull in different directions, speed and size,
and `-O` picks a bundle of passes toward one of them. On firmware the interesting
part is rarely the speedup. It is two other things: how much smaller the image
gets once the linker and a size-tuned libc do their work, which this module
measures step by step, and the class of bugs that switch on the moment the
compiler is allowed to keep values in registers and delete code that has no
visible effect. This is the [newlib](../newlib/) blink from the previous module,
rebuilt at different settings.

## What each -O level does

The optimizer works per translation unit: it reorders, inlines, keeps values in
registers, unrolls loops, and drops code it can prove has no effect. The levels
are just bundles of those passes.

| Level | What it does | Firmware use |
| --- | --- | --- |
| `-O0` | none, code maps 1:1 to source | debugging; biggest and slowest |
| `-Og` | optimize but keep the debug view intact | the level to step through |
| `-O1` | basic passes, a modest size and speed win | rare on its own |
| `-O2` | the full standard set | the usual release level |
| `-O3` | adds aggressive inlining and vectorization | rarely worth it on Cortex-M |
| `-Os` | `-O2` minus the passes that grow code | the firmware default when flash is tight |

Two things worth holding onto. `-O3` is not a free upgrade over `-O2`: the extra
inlining and unrolling usually add flash for no measurable gain on an M-class
core, and can even run slower by thrashing the instruction cache where there is
one. And `-Os` is the one to reach for on a small part, because it is `-O2`'s
logic aimed at size, which is the thing you are short of.

## The bugs the optimizer exposes

This is the part that bites, and it is why people wrongly fear optimization.
Turning `-O` up does not create these bugs. It reveals defects that `-O0` was
accidentally hiding.

### Missing volatile

At `-O0` the compiler reloads a variable from memory on nearly every access, so a
missing `volatile` is usually masked. At `-O1` and up it may keep the value in a
register, and three things break:

- **A register poll spins forever.** `while (!(UART->SR & RXNE));` through a
  non-volatile pointer reads the status register once, caches it, and loops on the
  stale copy. CMSIS marks registers `__IO`, which is `volatile`, and that is
  exactly why [cmsis](../cmsis/) matters here.
- **An ISR flag is never seen.** A flag set in an interrupt and polled in the main
  loop gets cached in a register in the loop, so the loop never re-reads the
  memory the ISR wrote. The flag has to be `volatile`, and the tick counter this
  module's delay rides on is precisely such a variable.
- **A busy-wait delay is deleted.** `for (i = 0; i < N; i++);` has no side effect
  the compiler can see, so it is removed whole and the delay vanishes. The fix is
  not `volatile` on `i`, it is to stop spinning: use a timer, which is why
  [main.c](app/Src/main.c) delays on `ticks_get()` instead of a counting loop.

The way to confirm any of these is the `-S` output from
[build-process](../build-process/): compile the file, read the assembly, and the
load you expected on every pass will simply be gone.

### Debugging an optimized build

At `-O2` the debugger loses its 1:1 map to the source. Breakpoints land on a
nearby line or jump around, single-stepping skips lines, inlined functions have no
call to break on, and locals read `<optimized out>` because they live in a
register or were folded away and never touched memory. None of that is a broken
debugger, it is the optimizer having reordered and merged the code. Build the
debug image at `-Og` (optimized but debuggable) or `-O0`, and keep the release
image separate.

The corollary is the most useful heuristic on this page: a bug that appears at
`-O2` and disappears at `-O0` is almost never a compiler bug. It is undefined
behaviour or a missing `volatile` that the optimizer is now free to act on.
Turning the level down hides it again; the fix is in the code.

## Shrinking the image

The rest is the worked example, the same blink rebuilt while watching
`--print-memory-usage`. Every row is a real measurement from this project on gcc
10.3:

| Build | FLASH |
| --- | --- |
| `-O0`, float `printf` on (`-u _printf_float`) | 26.1 KB |
| drop float `printf` | 11.0 KB |
| `nosys` + `--gc-sections` + `-ffunction-sections -fdata-sections` + `-static` + nano | 9.3 KB |
| `-Os` | 8.3 KB |
| same flags, gcc 12.3 | 5.7 KB |

The biggest single win is not an `-O` level at all. It is dropping floating-point
`printf`, which `-u _printf_float` had pulled in (the [newlib](../newlib/)
gotcha), and that alone more than halves the image. After that:

- **`--gc-sections`** drops unused functions and data, but only if each was placed
  in its own section with `-ffunction-sections -fdata-sections` at compile time.
  It is close to free and should be on. The catch: the linker will also
  garbage-collect the vector table and the libc `.init` and `.init_array`
  sections, because nothing references them by symbol, so those must be wrapped in
  `KEEP()` in the script. That is the `KEEP` from
  [linker-startup](../linker-startup/), and forgetting it is a board that does not
  boot.
- **`--specs=nano.specs`** selects newlib-nano, **`--specs=nosys.specs`** supplies
  failing syscall stubs, **`-static`** forces self-contained linking (the target
  has no shared libraries anyway), and **`--start-group -lc -lm --end-group`**
  lets the linker make repeated passes over libc and libm to resolve their
  circular references.
- **`-Os`** trims the last bit, and a newer toolchain trims more for free. The
  compiler version is itself an optimization knob, so a size number only means
  something next to its gcc version.

`-Os` earns the caution the old notes gave it: it is `-O2`-class optimization, so
it exposes the `volatile` and UB bugs above just as much. Reach for it once the
code is clean, not to paper over a build that only works at `-O0`.

## When to use it (and when not to)

Ship a release build at `-Os` (small part) or `-O2` (speed matters and flash is
roomy), with `--gc-sections` on and the vector table `KEEP`-protected. Build the
debug image separately at `-Og` or `-O0`. Skip `-O3` on Cortex-M unless a profile
proves a specific hot loop gains from it; the default outcome is a larger image at
the same speed.

The real cost of optimization is not risk, it is debuggability, and the answer is
to keep a debug build, not to ship `-O0`. If a feature only works at `-O0`, that
is a latent bug (a missing `volatile` or UB) to find now, because it resurfaces
the moment anyone raises the level or changes compiler.

Noted, not fixed: the Makefile carries the same non-`.PHONY` and missing
linker-script-dependency gaps flagged in [the-make](../the-make/).

## Build and run

STM32F401 with the FPU on, USART2 for the retargeted `printf`, PA8 toggled off the
SysTick counter. The live Makefile is the last flag set above: `-Os`, nano,
`--gc-sections`, function and data sections. `--print-memory-usage` prints the
FLASH and RAM table after every link.

```bash
make          # builds Build/flash.elf and flash.bin, prints size and memory usage
make load     # flash with OpenOCD over a J-Link (SWD)
make clean
```

To reproduce a row of the table, swap `CFLAGS` and `LDFLAGS` for that step and
rebuild; the printed numbers move with it.

## Files

- [Makefile](Makefile): the live `-Os` + nano + `--gc-sections` flag set and
  `--print-memory-usage`.
- [app/Src/main.c](app/Src/main.c): the blink, delaying on `ticks_get()` rather
  than a spin loop, the `volatile` lesson applied.
- [linkers/linker.ld](linkers/linker.ld): the script with `KEEP` on the sections
  `--gc-sections` would otherwise drop.
- [linkers/syscalls.c](linkers/syscalls.c) and
  [linkers/startup.c](linkers/startup.c): the newlib layer from
  [newlib](../newlib/).

### Reference

- [Demystifying Arm GNU Toolchain Specs: nano and nosys](https://metebalci.com/blog/demystifying-arm-gnu-toolchain-specs-nano-and-nosys/)
