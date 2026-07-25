# Make Build System

A shell script running the three `gcc` commands by hand would build this
firmware just fine. Make earns its place by doing the least work that still
produces a correct result: it models the build as a dependency graph and reruns
only the steps whose inputs actually changed. This module is the same blink and
the same linker script as its neighbours, wrapped in the Makefile that drives
them, so the file to read here is the [Makefile](Makefile) itself.

## The idea

A Makefile is a set of rules. Each rule names a target, the files it depends on,
and the commands that rebuild it. Every command line must begin with a real tab,
not spaces.

```
target: prerequisites
	command
```

The real link rule in this folder:

```
$(BUILD_DIR)/flash.elf : $(BUILD_DIR)/main.o $(BUILD_DIR)/startup.o
	$(CC) $(LDFLAGS) $^ -o $@
```

Variables (`CC`, `CFLAGS`, `LDFLAGS`) keep the toolchain name and its flags in
one place. The automatic variables carry the rule's own parts: `$^` expands to
the whole prerequisite list, `$@` to the target. So that line reads "link both
object files into the elf" without spelling the names out twice.

### The dependency graph is the point

`all` is the first target, which makes it the default goal when you type `make`
with no argument. It depends on `flash.elf`, which depends on `main.o` and
`startup.o`, which each depend on their `.c`. Make walks that chain backwards and
rebuilds from the bottom up.

Here is the payoff. Make stats every file's timestamp and runs a recipe only
when a prerequisite is newer than its target. Edit `main.c` and `make`
recompiles `main.o` and relinks, but never touches `startup.o`. A plain shell
script cannot make that distinction: it reruns everything, every time. On this
three-file example the saving is nothing. On a real tree it is the difference
between a one-second and a one-minute build, which is the entire reason make
exists.

### What this Makefile drives

Nothing new, just the earlier modules automated. `CFLAGS = -c -mcpu=cortex-m4
-mthumb -std=gnu99` is the compile-and-assemble stop from
[build-process](../build-process/), applied once per source. `LDFLAGS = -nostdlib
-T Src/linker.ld -Wl,-Map=Build/flash.map` is the link with the custom script
from [linker-startup](../linker-startup/): no standard library, place the
sections with `linker.ld`, and write a map file. `make load` hands the elf to
OpenOCD, `make clean` deletes the objects.

## When to use it (and when not to)

Make is the default for a firmware project small enough to hold the whole build
in your head, and it is what every module in this repo uses. It is installed
everywhere, needs no generator step, and a short Makefile reads end to end. It
begins to hurt as the project grows: listing header dependencies by hand gets
error-prone, and multi-config or cross-platform builds turn the file into
something you maintain instead of read. That is where a generator like CMake pays
off, by writing the Makefile for you and tracking header dependencies
automatically. For one board and a handful of files, that machinery is overhead
you do not need.

The honest cost: make's model is only as correct as the prerequisites you list.
Anything left out of a rule is a dependency make cannot see, and the symptom is a
stale build that a `make clean` "fixes". That fix is the tell that a prerequisite
is missing, not that make is flaky.

Noted in this Makefile, not fixed:

- `all`, `load`, and `clean` are actions, not files, but none is marked
  `.PHONY`. Let a file named `clean` (or `load`, or `all`) ever appear in the
  directory and make sees the target as already up to date and silently stops
  running the recipe.
- `flash.elf` does not list `Src/linker.ld` as a prerequisite, so editing the
  linker script does not trigger a relink. The section layout can change with the
  binary never rebuilt, exactly the stale-build trap above.
- `Build/` is used as an ordinary prerequisite and created with `mkdir` (no
  `-p`), so a directory timestamp can force spurious rebuilds; the idiom is an
  order-only prerequisite, `| $(BUILD_DIR)`. And `clean` removes only `*.o`,
  leaving `flash.elf` and `flash.map` in place.

## Build and run

Cortex-M4 target, 256K flash and 60K RAM as the linker script is written, and it
blinks PA5.

```bash
make          # runs the default goal: creates Build/ and builds Build/flash.elf
make load     # flashes it with OpenOCD over ST-Link
make clean    # removes the object files
```

The first `make` compiles both sources and links. A second `make` with nothing
changed prints `Nothing to be done for 'all'` and does no work, which is the
incremental behaviour on display.

## Files

- [Makefile](Makefile): the rules, variables, and the load and clean actions.
- [Src/main.c](Src/main.c): the PA5 blink, the thing being built.
- [Src/startup.c](Src/startup.c) and [Src/linker.ld](Src/linker.ld): the same
  startup code and linker script explained in [linker-startup](../linker-startup/),
  reused here as the build's other inputs.

For the raw commands this Makefile is automating see
[build-process](../build-process/); every other module in the repo carries a
richer version of this same Makefile.
