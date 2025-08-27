# Strategy

### Hardware Bottleneck and Dual-Targeting

Embedded development often faces significant delays due to dependencies on
target hardware. Issues like late hardware availability, high costs, scarcity,
hardware bugs, long build/upload times, and expensive compiler licenses can halt
progress. These bottlenecks lead to accumulated unverified code, making
integration and debugging a nightmare when hardware finally arrives.

Dual-targeting involves designing code to run on both the final embedded target
and the host development system from day one. This strategy allows developers to
write and test code continuously, even without hardware. By isolating software
testing from hardware uncertainties, teams avoid the "debugging chaos" that
arises when hardware and software issues intertwine.

Dual-targeting forces a modular design with clear boundaries between
hardware-specific and hardware-independent code. This improves software quality
and maintainability. Additionally, it future-proofs the code: porting to new
hardware becomes easier, and existing unit tests ensure behavior remains
consistent across platforms. This approach transforms potential blockers into
opportunities for robust, portable design.

Teams using dual-targeting report faster development cycles and reduced
debugging time. By testing on host systems first, they catch software bugs
early, leaving only hardware-specific issues for target testing. This practice
not only accelerates development but also enhances collaboration between
hardware and software teams.

Start by identifying hardware-dependent code (e.g., direct register access) and
abstracting it behind interfaces. Use dependency injection (as in the LedDriver)
to substitute hardware interactions with test doubles on the host. Maintain a
strict separation between pure logic and hardware glue code, ensuring most tests
run off-target without sacrificing reliability.

Dual-targeting isn’t just a workaround—it’s a strategic practice that builds
resilience. As hardware evolves, your code adapts effortlessly, supported by a
comprehensive test suite. This approach turns embedded development constraints
into strengths, fostering agility and innovation.