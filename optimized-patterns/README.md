# Optimized Design Patterns

This section revisits design patterns under embedded constraints: memory cost,
determinism, and direct interaction with hardware. Some patterns also appear in
[Design Patterns](../design-patterns/), which presents the canonical form and
intent; the versions here focus on what changes when resources are tight.

## What changes under embedded constraints

The canonical pattern descriptions assume a desktop-class environment. On a
microcontroller, a few assumptions break, and every module in this section is
shaped by them:

- **Memory is static.** Dynamic allocation risks fragmentation on a heap
  measured in kilobytes, so instances tend to be static and object creation
  happens at init, not on demand.
- **Timing is part of correctness.** Many targets have real-time deadlines,
  so a pattern that adds unbounded or variable latency in the wrong place is
  a bug, not a style choice.
- **The hardware is right there.** Patterns wrap registers, interrupts and
  peripherals directly, so indirection layers must earn their cost in every
  call path.
- **Deployment is long.** Firmware can run for years without updates, which
  raises the value of structures that isolate change and keep failures
  contained.

Each module states what the pattern costs, so the decision to use it stays
honest.

## Quick reference

Pick a pattern by the problem it solves and what it costs, then read its entry
below or open the module.

| Pattern | Problem it solves | Cost |
| --- | --- | --- |
| [Singleton](singleton/) | One instance of a resource (a UART) with a global access point | Global state (hidden coupling, harder to test); lazy init races if called from an ISR and main |
| [Builder](builder/) | Construct a complex configuration step by step, readably | A builder struct and more code than a designated initializer; pays off only when construction has real logic |
| [Factory](factory/) | Pick one of several implementations (a comm protocol) behind one call | An indirect call through the vtable, and every candidate linked even if one is used |
| [Hardware Proxy](hw-proxy/) | Gate and control access to a peripheral behind a checked interface | Double indirection plus a mask check per operation; worth it only if gating or a swappable backend is real |
| [Decorator](decorator/) | Add behavior (logging) around an interface without touching the wrapped code | An extra indirection per call; the static-self version here supports only one instance |
| [Mediator](mediator/) | Let components coordinate without referencing each other | The hub becomes a single point (god object), string routing is fragile, notify can re-enter |
| [Mediator Example](mediator-example/) | The same, applied to three coordinated devices | Same god-object and stringly-typed routing cost at larger scale |
| [Strategy](strategy/) | Swap an algorithm (a filter) at runtime, with per-strategy state | An indirect call, and each strategy carries its own state in RAM |
| [Observer](observer/) | Notify several observers when a subject changes | A fixed observer array in RAM; notify in an ISR runs blocking observer code in interrupt context |
| [State](state/) | Model modes as handlers instead of scattered flags | An indirect call per step; transition is just repointing a global (no lifecycle) |
| [State Example](state-example/) | The same, with an enter, execute, exit lifecycle | More structure and per-state files; re-init on entry is an easy trap |

## Patterns

All modules run on the STM32F411.

1. [Singleton](singleton/): a module guaranteed to have one instance,
   statically allocated.
2. [Builder](builder/): constructing a complex configuration step by step
   through one build process.
3. [Factory](factory/): selecting a communication protocol (UART, SPI or I2C)
   behind a single creation interface.
4. [Hardware Proxy](hw-proxy/): a proxy mediating every GPIO access, adding
   control without exposing registers.
5. [Decorator](decorator/): wrapping an ADC interface with a logger without
   touching the wrapped code.
6. [Mediator](mediator/): a sensor and an actuator coordinated by a central
   mediator instead of talking directly.
7. [Mediator Example](mediator-example/): the applied counterpart, a home
   automation simulation with three devices.
8. [Strategy](strategy/): interchangeable filter algorithms applied to ADC
   readings at runtime.
9. [Observer](observer/): a subject notifying LED and UART observers when its
   state changes.
10. [State](state/): a traffic light where each state is a function pointer
    handler.
11. [State Example](state-example/): the applied counterpart, an
    idle/read/transmit/error machine with each state in its own file.
