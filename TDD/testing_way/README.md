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


