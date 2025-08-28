# Doubts

### We Dont Have Time

A common objection to TDD is the perceived lack of time. Developers worry that
writing tests will slow them down, especially when production code already feels
behind schedule. However, this view often overlooks the time spent on debugging
and fixing bugs later. TDD may require more initial code (like the LedDriver,
which had more test lines than production code), but it reduces overall effort
by catching errors early.

Proficient TDD practitioners report that it speeds them up by reducing debug
time and maintaining a cleaner codebase. If you currently spend about 50% of
your time testing and debugging (as many conference attendees report), TDD
offers a proactive alternative. Instead of reacting to bugs, you prevent them,
trading reactive debug time for proactive test writing.

Manual testing has a low initial investment but offers almost no future return.
Every code change requires re-running manual tests, which is time-consuming and
often incomplete. TDD automates this process, ensuring tests are run
consistently and thoroughly with each change, saving time in the long run.

Many developers write custom test harnesses (e.g., a test `main()` with stubs)
for new code. While helpful initially, these tests often fall into disrepair
after integration. They become incompatible and are discarded, offering a poor
return on investment. Structured test harnesses like CppUTest or Unity require
less effort and provide lasting value.

Debugging by single-stepping through code is slow, non-repeatable, and tedious.
Any code change invalidates previous efforts, requiring you to start over. This
method is error-prone and unsustainable as the codebase grows, leading to missed
bugs and increased future effort.

Some organizations have elaborate, documented unit test processes with reviews
and plans. While this feels rigorous, it is often inefficient. Tests are manual,
repetitive, and boring, leading to shortcuts and bugs. Automation, as in TDD,
provides better documentation and continuous value with less overhead.

You are already investing time in unit testing—whether through ad hoc methods,
custom harnesses, or manual processes. These approaches have high costs and
limited payback. TDD shifts this investment into automated, evolving tests that
run with every change, offering repeated returns and reducing debug time.

TDD may seem slower initially, but it accelerates development by ensuring
quality and reducing bugs. By automating tests, you save time otherwise spent on
debugging and manual re-testing, making TDD a wise long-term investment.

### Write Tests After the Code

Test-Driven Development (TDD) requires writing tests *before* production code,
fundamentally shaping the design process. In contrast, Test-After Development
writes tests *after* the code is complete. While Test-After still provides some
benefits, it misses key advantages that TDD offers. TDD is not just about
testing; it is a design and development discipline that influences the entire
software structure.

TDD leads to better-designed code with improved APIs, more cohesive modules, and
looser coupling because the tests act as the first user of the code. This design
influence is minimal in Test-After Development. Additionally, TDD catches small
mistakes immediately during development, preventing defects from ever reaching
the bug database. Test-After may find some issues, but it allows more errors to
escape detection, leading to future debugging efforts.

With TDD, test failures are immediately linked to the most recent change, making
root cause analysis straightforward. In Test-After Development, failures require
hunting through existing code to find the source, wasting valuable time. TDD
also naturally results in comprehensive and rigorous test coverage tailored to
the code's requirements, whereas Test-After often leads to gaps in coverage and
less effective tests.

### Unit Tests Don’t Find All the Bugs

TDD ensures that each individual unit of code—each "building block", behaves
exactly as intended. While it cannot catch every possible bug, it creates a
reliable foundation by verifying that every line of code meets expectations.
This precision at the unit level is crucial for constructing complex systems
that function correctly.

TDD is not a substitute for other testing types. Integration tests, acceptance
tests, exploratory tests, and load tests are still essential. These higher-level
tests focus on broader issues: integration problems, requirement validation, and
system performance. TDD reduces unit-level defects, allowing these other tests
to uncover more appropriate and complex issues rather than being bogged down by
simple coding errors.

Small errors, like a single typo, can lead to significant and hard-to-find bugs
in complex systems. TDD catches these mistakes immediately during development,
preventing them from evolving into larger issues. While not foolproof, TDD is
highly effective at minimizing wasted effort and ensuring that changes have only
their intended consequences.