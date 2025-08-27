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