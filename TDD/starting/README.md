# Starting

### Building Testable Modules in C

To create testable code, we must organize it into **modules**. A module is a
self-contained unit with a well-defined interface, hiding its internal workings.
This practice, known as **encapsulation**, is the cornerstone of good software
design and is a natural outcome of Test-Driven Development (TDD).

There are two main patterns for creating modules in C, both centered on the
principle of hiding data:

**1. Single-Instance Module:**

-   **Use Case:** When you only need one instance of the module's data (e.g., a
central LED driver for a system).
-   **How it works:** Data is declared as `static` inside the `.c` file. This
makes it private and persistent, but inaccessible from outside. The public `.h`
file only contains the function prototypes that act as the module's interface.

**2. Multiple-Instance Module (Abstract Data Type - ADT):**

-   **Use Case:** When you need multiple, separate instances of data (e.g.,
multiple circular buffers, similar to how `FILE*` works in the standard
library).
-   **How it works:** The `.h` file uses a **forward declaration** to hide the
data structure's internals:

    ```c
    // In the .h file (Public Interface)
    typedef struct CircularBufferStruct *CircularBuffer;
    ```

    The actual struct members are defined *only* inside the `.c` file. Clients
    can hold and pass around a `CircularBuffer` pointer but cannot see or
    directly modify what's inside it.

### The Three-File Convention for Every Module

To consistently apply these concepts, follow this structure for each module you create:

| File Type | Purpose | Contains |
| --- | --- | --- |
| **Header (.h)** | **Public Interface** | Function prototypes. For ADTs, a `typedef` for a pointer to a hidden struct. |
| **Source (.c)** | **Private Implementation** | The full code for all functions, private `static` helpers, and the actual definition of hidden data structs. |
| **Test (.c or .cpp)** | **Verification** | All test cases for the module, separate from production code. |

### Testable LED Driver Module

An LED driver is a software module that provides a clean interface to control
hardware LEDs, abstracting away the low-level memory operations. The
requirements specify control over 16 individual LEDs, including the ability to
turn any single or all LEDs on/off, query their state, and ensure they start in
an off state after initialization. The hardware interaction is defined by
memory-mapping the LEDs to a 16-bit word where each bit corresponds to an LED
(bit 0 for LED 1, bit 15 for LED 16), with a '1' lighting the LED and a '0'
turning it off.

To ensure reliability and testability off the target hardware, the driver will
be designed as a single-instance module, hiding its internal data and operations
behind a well-defined interface. This approach allows us to verify the driver's
logic without physical hardware, using tests that simulate and check the memory
writes and reads. The test list includes validating initialization, individual
and group LED operations, state queries, and error handling for boundary and
out-of-bounds values.

LED Driver Tests:

- All LEDs are off after the driver is initialized.
- A single LED can be turned on.
- A single LED can be turned off.
- Multiple LEDs can be turned on/off .
- Turn on all LEDs
- Turn off all LEDs
- Query LED state
- Check boundary values
- Check out-of-bounds values

### Test List in TDD

Creating a test list is the first crucial step in Test-Driven Development (TDD),
acting as a practical roadmap derived directly from your requirements. This
list—whether jotted on a notepad or typed as comments in your test file—captures
your initial vision of what "done" looks like, including key behaviors and edge
cases (like handling out-of-bounds values). It doesn’t need to be perfect; its
purpose is to prevent oversight and provide direction. Spend only a few minutes
drafting it, and stop once you hit diminishing returns (when new tests slow
down). The list evolves as you code: tests may be split, combined, or added
later, but it serves as a reorientation tool during deep dives.

Contrary to the common advice of tackling the hardest problem first, TDD
advocates starting with the simplest, most verifiable test that moves you toward
your goal. This approach builds capability incrementally, ensuring a robust and
well-tested foundation. Each small step is validated, reducing risk and
clarifying design choices along the way. Over time, you’ll develop the skill to
anticipate and prioritize tests effectively, turning uncertainty into structured
progress.

### The First Test: Initializing the LED Driver

The journey begins by creating the test file [LedDriverTest.c](tests/LedDriverTests.c)
and setting up the basic structure with a `TEST_GROUP` and a failing test. The
initial goal is to verify that all LEDs are off after initialization. To test this
without real hardware, we use **dependency injection**: instead of hardcoding the
hardware's memory address, the driver receives the address of a variable (`virtualLeds`)
that simulates the LED bank in RAM. This technique "fakes out" the driver,
allowing it to operate on a virtual representation that the test can inspect.
The test sets `virtualLeds` to all ones (`0xffff`) before calling
`LedDriver_Create()`, then asserts that the driver wrote zeros to it, proving it
turned all LEDs off.

The process follows TDD’s **red-green cycle**:

1.  **Red:** Write a test that fails because the production function doesn’t
exist or doesn’t work (`TEST_ASSERT_EQUAL_HEX16(0, virtualLeds)` fails).

2.  **Green:** Implement the simplest code to pass the test (e.g., `*address = 0;`
in `LedDriver_Create`).

3.  **Refactor:** Improve the code without changing behavior (not needed yet).

A key discipline is to **not let the code get ahead of the tests**. Even though
you know the driver will need to store the LED address for future tests, you
only add that functionality when a test requires it. This ensures every line of
production code is justified by a test, leading to a robust and well-tested
design. Dependency injection not only enables testing off-target but also makes
the driver more reusable and flexible.

### Evolving the Interface and Implementation Through TDD

A well-designed module starts with its interface, and TDD ensures we focus on
this from the user’s perspective. The first tests act as the initial clients of
the code, driving the design of how the module will be used. By starting with
simple boundary conditions—like turning on LED 1, we gradually shape a clean and
intuitive interface. This outside-in approach prioritizes usability and ensures
the module meets actual needs before internal complexities are addressed.

The process is guided by **Bob Martin’s Three Laws of TDD**:

1.  **No production code without a failing test.**  
2.  **No more test code than needed to fail.**  
3.  **No more production code than needed to pass the test.**  

These rules enforce discipline: each test must fail first, proving it can detect
errors, and each production code change must be minimal and directly address the
failure. This iterative cycle—red, green, refactor—builds reliability
incrementally.

Initially, implementations are intentionally simplistic—even "wrong"—like
hardcoding `*ledsAddress = 1` in `TurnOn()`. This might feel uncomfortable, but
it serves a critical purpose: it validates the test itself. By observing the
test fail and then pass with the hardcoded value, we confirm the test is
effective. This approach acts as a **software vice**, locking behavior in place
and ensuring changes are controlled and deliberate.

Resist the urge to over-engineer prematurely. Adding unneeded code introduces
complexity without validation. Instead, trust the test list to guide progress.
For example, after testing `TurnOn()`, the next logical step is `TurnOff()`,
which complements the functionality and expands the interface. Each test forces
the implementation to evolve—like storing the LED address only when
necessary—ensuring every line of code is justified and tested. This structured
procrastination leads to a robust, flexible design where the tests accumulate as
a valuable artifact, documenting behavior and preventing regressions.