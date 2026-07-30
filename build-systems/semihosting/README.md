# Semihosting

You want `printf` while bringing up a board, but no UART is wired yet. Or you
want to read a test file off the host, or dump a capture to one. Semihosting
gives the target's standard I/O a path straight to the debugger's console and the
host filesystem, over the SWD wires already attached, with no peripheral on the
target at all. The catch is in how it does that, and the catch is exactly why it
never leaves the bench.

## The idea

When you call `printf`, the C library eventually calls `_write`. Normally you
retarget `_write` to a UART. Semihosting retargets it to the debugger: the
library's `_write` executes a `BKPT 0xAB` with an operation code and a pointer to
its arguments, which halts the core. The attached debugger (OpenOCD or GDB) is
watching for that breakpoint, reads the operation and the buffer out of target
memory, performs the I/O on the host (prints to its console, reads a host file),
writes the result back, and resumes the core. `printf` returns as if a UART had
taken the bytes, except the bytes went to your PC.

Two pieces make it work in this example. On the target side:

```c
extern void initialise_monitor_handles(void);
...
initialise_monitor_handles();   /* first line of main */
printf("Init board!\n");
```

`initialise_monitor_handles()` comes from the semihosting library and opens the
host's stdin, stdout, and stderr through a semihosting call. Call it before the
first `printf`, or the handles are never set up.

The other piece is the link line:

```
--specs=rdimon.specs -lc -lrdimon
```

`rdimon` is Arm's debug-monitor semihosting library. It supplies the `_write`,
`_read`, `_sbrk` and friends that issue the `BKPT`, in place of the do-nothing
stubs you would get from `--specs=nosys.specs`. This is the same newlib
retargeting covered in [newlib](../newlib/), pointed at the debugger instead of
at nothing or at a UART.

### Turning it on at the probe

The target half is not enough. The debugger has to be told to service the
breakpoints, or the `BKPT` just halts the core and looks like a crash. That is
the `semi` target in the Makefile:

```
openocd ... -c "arm semihosting enable" -c "reset"
```

With semihosting enabled, OpenOCD prints the target's `printf` output to its own
console. Without it, the first `printf` halts the CPU and the board appears dead.

## When to use it (and when not to)

Semihosting is a bring-up and debug tool. Its one real advantage is that it needs
zero target hardware: no UART, no pins, no level shifter, and it can do real file
I/O on the host, which a UART cannot. That makes it genuinely useful for feeding a
test vector from a host file or dumping a capture to one during development.

Everything else about it is a reason not to ship it:

- **It halts the CPU on every call.** Each `printf` traps to the debugger, which
  does the work while the target is stopped, then resumes. It is far slower than a
  UART and it wrecks real-time behaviour, so any timing measured with semihosting
  logging still in the loop is meaningless.
- **It only works with a debugger attached and listening.** Run the same firmware
  from a power supply with no probe and every semihosting call hits a `BKPT` that
  nobody services. The core halts or hard-faults on the first `printf`. A build
  with semihosting left in is a board that hangs the instant it runs standalone.

So the rule is: semihosting for the first hours of bring-up when no UART exists
yet, or when you specifically need host file access. For any logging that has to
survive on a standalone board, retarget `printf` to a UART instead (non-halting,
works with no probe), which is what the data-structures modules do. For faster,
less intrusive trace with a probe attached, SWO or ITM beats semihosting, though
it still needs the probe.

The build cost is real too: `-lrdimon` and its startup pull the full library in,
so a semihosting build is larger and is not the configuration to measure code
size against.

Noted, not fixed: the Makefile carries the same gaps flagged in
[the-make](../the-make/) (no `.PHONY` on `all`, `load`, `semi`, `clean`, and
`flash.elf` not depending on `Src/linker.ld`), and it adds `-I Inc/` for a
directory this module does not have, a harmless dead include path.

## Build and run

Cortex-M4, a raw-register PA5 blink plus a counter printed on each toggle. It
takes two terminals: one to flash, one to run OpenOCD with semihosting enabled so
the output has somewhere to land.

```bash
make          # builds Build/flash.elf, linked against rdimon
make load     # flash it
make semi     # start OpenOCD with `arm semihosting enable`; printf lands here
```

The flags set `-O0` and `-mfloat-abi=soft`. The output appears in the OpenOCD
console started by `make semi`, not on any UART.

## Files

- [Src/main.c](Src/main.c): a PA5 blink that calls `initialise_monitor_handles()`
  and prints a counter each toggle.
- [Makefile](Makefile): the `rdimon` spec and libraries in `LDFLAGS`, plus the
  `semi` target that enables semihosting on the probe.
- [Src/startup.c](Src/startup.c) and [Src/linker.ld](Src/linker.ld): the same
  hand-written startup and script from [linker-startup](../linker-startup/).

For the `_write` retargeting mechanism and the `specs` files that select it, see
[newlib](../newlib/); for the Makefile pattern, [the-make](../the-make/).
