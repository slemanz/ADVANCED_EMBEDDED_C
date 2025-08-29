# Test Doubles

### Collaborators

So far, we've focused on testing self-contained code without dependencies.
However, most real-world code consists of modules that depend on other
functions, modules, or hardware devices. These dependencies make testing more
challenging because the code under test must work through collaborators to
perform its functions.

A collaborator is any external dependency that the code under test interacts
with. Even seemingly standalone modules like the LedDriver have collaborators -
in this case, the memory-mapped I/O address. During testing, we replace actual
hardware with test doubles like virtualLeds, which impersonate the real
collaborator while allowing us to monitor the code's behavior.

Test doubles (such as stubs) temporarily replace production collaborators during
testing. While developers often view stubs as temporary solutions, in TDD they
become permanent fixtures that enable automated unit testing throughout the
code's lifecycle. The code under test interacts with these doubles exactly as it
would with real collaborators, making comprehensive testing possible without
actual dependencies.

### Stub or Mock

In software testing, a stub provides pre-determined responses for methods or
objects to control the test's flow and simplify it, while a mock verifies that
specific interactions (like method calls with correct parameters) occurred
during the test. You use a stub when you need a component to return specific
data to test your code's behavior, and a mock when you need to check how your
code interacted with a dependency. 