# Testing Your Way

### Completing the LED Driver Through Incremental TDD

We continue developing the LedDriver from where we left off: with a skeletal
structure, a defined interface, and three passing tests. The goal is to grow the
implementation incrementally, one test at a time, ensuring each step is verified
before moving forward. This steady rhythm is the essence of TDD.

The next test, TurnOnMultipleLeds, turns on LEDs 8 and 9 and expects virtualLeds
to be 0x180. This fails because the current implementation only handles a single
LED. The solution involves bit manipulation: *ledsAddress |= (1 << (ledNumber -
1));. However, an off-by-one error (shifting too much) causes failures in
existing tests. This error is caught immediately, demonstrating TDD’s power to
detect issues early. Fixing it (subtracting 1 from ledNumber) restores
stability.

With tests passing, we refactor the bit manipulation into a helper function,
convertLedNumberToBit(), to improve readability. This follows the TDD cycle:
after making a test pass, we improve the code without changing behavior.

The test TurnOffAnyLed initially fails because the simple TurnOff implementation
turns off all LEDs. To properly test masking (turning off one LED without
affecting others), we first implement TurnAllOn (using 0xffff) and refactor
magic numbers into enums (ALL_LEDS_ON, ALL_LEDS_OFF). Then, TurnOff uses bitwise
AND with the complement of the LED bit: `*ledsAddress &= ~(convertLedNumberToBit(ledNumber));`.

We learn the hardware LEDs are write-only, meaning the driver cannot read their
state. To simulate this, we introduce ledsImage, a private variable that mirrors
the LED states. All operations now update ledsImage and write it to virtualLeds
via a new updateHardware() function. This ensures the driver works correctly
regardless of hardware readability.

Tests for upper/lower bounds (TurnOn(1) and TurnOn(16)) pass easily. However,
out-of-bounds values (e.g., -1, 0, 17) cause unexpected behavior due to bit
shifting quirks. We add **guard clauses** in TurnOn and TurnOff to ignore invalid
inputs, ensuring safety.

We discover that the guard clause in TurnOff was untested. We rename tests to be
specific (e.g., OutOfBoundsTurnOnDoesNoHarm) and add
OutOfBoundsTurnOffDoesNoHarm, which turns all LEDs on first to verify that
TurnOff doesn’t alter valid states. This reinforces the rule: never let
production code get ahead of tests. Always write a test for each new behavior.

For better error handling, we use a `RUNTIME_ERROR()` macro to log out-of-bounds
accesses. During tests, a stub captures the error message and parameters,
allowing verification. The test OutOfBoundsProducesRuntimeError checks that
calling TurnOn(-1) triggers the expected error.

For unresolved questions, we use `IGNORE_TEST` to create executable reminders.
These tests compile but don’t run, serving as TODOs that appear in test outputs.
For example, `IGNORE_TEST(LedDriver, OutOfBoundsToDo)` prompts future action
without breaking the build.

### Keep Code Clean

Always refactor **only when all tests are passing**. This is your safety net.
Refactoring on green ensures that any structural changes you make don’t
accidentally break existing functionality. If tests are failing, you lack the
stability to safely improve the code.

Refactoring addresses code "smells" like duplication and magic numbers early,
preventing them from evolving into larger problems. In the LedDriver, functions
like `TurnOn` and `TurnOff` had duplicated logic for bounds checking and bit
manipulation. By refactoring, we eliminate this duplication, making the code
more maintainable and less error-prone.

When extracting a new helper function (e.g., `IsLedOutOfBounds`), **copy the
code first—don’t cut it**. Define the new function, paste the code, and adjust
parameters and return types. Compile to ensure syntax correctness. Once it
works, replace the original code with a call to the new function. This approach
keeps you one undo away from working code if something goes wrong.

Magic numbers (like `1` and `16` for LED bounds) obscure meaning. Replace them
with named constants (e.g., `FIRST_LED`, `LAST_LED`) to improve readability and
centralize changes. This makes the code self-documenting and easier to modify.

Extract helper functions to match the abstraction level of the calling code. For
example, `setLedImageBit` and `clearLedImageBit` hide the complex bit
manipulation details, making `TurnOn` and `TurnOff` more readable and focused on
their high-level goals.

Refactoring in small, incremental steps reduces risk. Change one caller at a
time to a new helper function, and verify tests pass after each change. If a
test fails, **undo immediately** rather than debugging. This minimizes confusion
and keeps you in a known good state.

Duplicate code is a primary source of bugs. When the same logic appears in
multiple places, a change in one spot must be replicated everywhere—a
error-prone process. By centralizing logic into single functions, you ensure
consistency and reduce future maintenance effort.

Tips:

- Use `static` helper functions to avoid polluting the global namespace.
- Compile frequently to catch syntax errors early.
- If a refactoring breaks tests, revert and reassess rather than pressing forward.
- Keep functions small and focused on a single responsibility.

**LED Driver Tests:**

- ~~All LEDs are off after the driver is initialized.~~
- ~~A single LED can be turned on.~~
- ~~A single LED can be turned off.~~
- Multiple LEDs can be turned ~~on~~/off.
- ~~turn on all LEDs~~
- Turn off all LEDs
- Query LED state
- ~~Check boundary values~~
- Check out-of-bounds values
    - ~~Beyond max breaks nothing~~
    - ~~Under min breaks nothing~~
    - ~~Runtime Error~~
    - What should really happen?
- ~~Hardware interaction~~

### Repeat until Done
