# Module map

Every module in the repo with a one-line description, so you can find a topic
when you remember the subject but not where it lives. The sections follow the
[main README](README.md): each heading links to the section index, each entry
links to the module.

## [Design Patterns](design-patterns/)

Classic patterns in clean C, one buildable project each.

- **[adt](design-patterns/adt/)**: an abstract data type behind an opaque pointer, the reference module for hiding a struct so the caller sees only the interface.
- **[hardware-proxy](design-patterns/hardware-proxy/)**: one struct owns a device's address and bit encoding, so that knowledge lives in one place instead of leaking into every client.
- **[hardware-adapter](design-patterns/hardware-adapter/)**: converts a device's interface into the one the application expects, built on top of the hardware proxy.
- **[strategy](design-patterns/strategy/)**: pull the algorithm out into an interchangeable function pointer so the choice can change at runtime without editing the client.
- **[client-server](design-patterns/client-server/)**: a server (a shared queue of samples) sits between one producer and many consumers so none of them knows the others.
- **[publisher-subscriber](design-patterns/publisher-subscriber/)**: consumers register callbacks with a publisher that only knows it has a list to fire, the same pattern as observer.
- **[state](design-patterns/state/)**: three ways to build a state machine (conditional, table-based, and the state pattern) with the trade-offs of each.
- **[bit-fields](design-patterns/bit-fields/)**: C bit-fields and the implementation-defined-layout warning that keeps them away from hardware registers.
- **[template](design-patterns/template/)**: the base project skeleton to copy when starting a new pattern module.

## [Optimized Patterns](optimized-patterns/)

The same patterns revisited under embedded constraints, memory cost and determinism.

- **[singleton](optimized-patterns/singleton/)**: why a singleton in embedded is usually just a static variable in the module, shown with a lazy-initialized UART instance.
- **[builder](optimized-patterns/builder/)**: build a UART configuration field by field, and the honest comparison with a designated initializer.
- **[factory](optimized-patterns/factory/)**: an enum-to-vtable switch that returns a communication protocol implementation without allocating.
- **[hw-proxy](optimized-patterns/hw-proxy/)**: a protection proxy, a GPIO with a `pins_allowed` mask gating each operation, contrasted with the encapsulation proxy in design-patterns.
- **[decorator](optimized-patterns/decorator/)**: wrap an ADC read to add logging while keeping the same interface.
- **[mediator](optimized-patterns/mediator/)**: a hub that routes messages between components so they never reference each other directly (minimal form).
- **[mediator-example](optimized-patterns/mediator-example/)**: the fuller worked example of the mediator hub.
- **[observer](optimized-patterns/observer/)**: a subject holding a fixed array of observer pointers with attach, detach, and notify, cross-linked to publisher-subscriber.
- **[strategy](optimized-patterns/strategy/)**: interchangeable filters behind a struct-with-self interface, a moving-average filter carrying its own ring buffer.
- **[state](optimized-patterns/state/)**: the minimal state machine (a traffic light, transition is just repointing the state global).
- **[state-example](optimized-patterns/state-example/)**: the richer state machine with an enter, execute, exit lifecycle driving an ADC pipeline.
- **[template](optimized-patterns/template/)**: the base project skeleton to copy when starting a new module.

## [Data Structures](data-structures/)

Structures chosen for constrained targets, with the cost of each spelled out.

- **[memory](data-structures/memory/)**: static versus dynamic allocation, when to use each, and the catalog of heap bugs static allocation avoids.
- **[pools](data-structures/pools/)**: a fixed-block allocator with the free list threaded through the free blocks themselves, O(1) alloc and free with no extra RAM.
- **[queues](data-structures/queues/)**: the ring buffer between an ISR and the main loop, and exactly what makes it safe without a lock.
- **[linked](data-structures/linked/)**: a linked list on an MCU, when it beats a fixed array and when the array wins.
- **[bit-packed](data-structures/bit-packed/)**: compiler-laid-out bit-fields versus hand-written masks, and packing a peripheral register as a bit-packed struct.
- **[mcu-background](data-structures/mcu-background/)**: the MCU theory page (8/16/32-bit architectures, memory types, endianness) that the rest of the section assumes.
- **[template](data-structures/template/)**: the base project skeleton to copy when starting a new module.

## [Build Systems](build-systems/)

What happens between source and flash, one stage or tool at a time.

- **[build-process](build-systems/build-process/)**: the five stages from source to flash run by hand, with the artifact each stage leaves behind (preprocess, compile, assemble, link, objcopy).
- **[linker-startup](build-systems/linker-startup/)**: the linker script and startup code, VMA versus LMA, copying `.data`, zeroing `.bss`, and the vector table.
- **[the-make](build-systems/the-make/)**: make itself, the dependency graph and timestamp-driven incremental rebuild that a shell script cannot give you.
- **[cmsis](build-systems/cmsis/)**: the vendor register-definition layer, `GPIOA->ODR` instead of a raw pointer cast, and the three files CMSIS adds.
- **[newlib](build-systems/newlib/)**: the embedded libc and the syscall layer you supply, retargeting `printf` to UART, the `_sbrk` heap, and running constructors before `main`.
- **[semihosting](build-systems/semihosting/)**: `printf` routed to the debugger through a `BKPT`, and why it is debug-only and hard-faults standalone.
- **[optimized](build-systems/optimized/)**: what each `-O` level does in firmware and the bugs the optimizer exposes (missing `volatile`, debugging at `-O2`).
- **[assembly](build-systems/assembly/)**: what a hand-written assembly example shows and when assembly is still necessary.
- **[cpp](build-systems/cpp/)**: using C++ on bare metal, what changes in the build and what to avoid.

## [Bootloader](bootloader/)

From a minimal bootloader to a multi-slot design with a factory fallback.

- **[linkerscript](bootloader/linkerscript/)**: the memory-regions example that is the foundation of everything else in the section.
- **[bootloader-v1](bootloader/bootloader-v1/)**: the first minimal bootloader, its limits, and what the multi-slot design fixes.
- **[multi-slot](bootloader/multi-slot/)**: the full multi-slot system with a factory fallback image, memory map, boot flow, and build guide.
- **[shared](bootloader/shared/)**: what is shared between bootloader and application and why.
- **[template](bootloader/template/)**: the base skeleton for a bootloader project.

## [TDD](tdd/)

Notes on test-driven development for embedded, expanded in the [unity-embedded-tdd](https://github.com/slemanz/unity-embedded-tdd) repo.

- **[intro](tdd/intro/)**: the feedback advantage of TDD over debug-later programming.
- **[tools](tdd/tools/)**: unit test harnesses and the frameworks (Unity, CppUTest).
- **[starting](tdd/starting/)**: building testable modules in C, the single-instance and multiple-instance module patterns.
- **[testing_way](tdd/testing_way/)**: growing a LED driver one failing test at a time.
- **[strategy](tdd/strategy/)**: dual-targeting, running the code on the host and the target from day one.
- **[doubts](tdd/doubts/)**: the common objections to TDD (no time, more code) and the answers.
- **[test_doubles](tdd/test_doubles/)**: collaborators and the doubles that stand in for real hardware in a test.
- **[production_code](tdd/production_code/)**: the taxonomy of test doubles (dummy, stub, spy, mock).
