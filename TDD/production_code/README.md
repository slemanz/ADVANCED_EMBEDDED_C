# Production Code

### Test Doubles Variations

- Test Dummy: Keeps the linker from rejecting your build. A dummy is a simple
stub that is never called.  It is provided to satisfy the complier, linker, or
runtime dependency.

- Test Stub: Returns some value, as directed by the current test case.

- Test spy: Captures the parameters passed from the CUT so the test can verify
that the correct parameters have been passed to the CUT. The spy can also feed
return values to the CUT just like a test stub.

- Mock object: Verifies the functions called, the call order, and the parameters
passed from the CUT to the DOC. It also is programmed to return spe- cific
values to the CUT. The mock object is usually dealing with a situation where
multi- ple calls are made to it, and each call and response are potentially
different.

- Fake object: Provides a partial implementation for the replaced component. The
fake usually has a simplified implementation when compared to the replaced
implementation.

- Exploding fake: Causes the test to fail if it is called.

### Testing Hardware-Dependent Code

Modules like the LightScheduler in home automation systems typically have
transitive dependencies on hardware and operating systems through abstraction
layers. These dependencies make testing difficult because they tie the code to
specific execution environments. The solution involves creating defined
interfaces that all environment access must pass through, allowing test doubles
to intercept and control these interactions.

The test case and test doubles together form a software test fixture that
surrounds the Code Under Test (CUT). The test case acts as the client driving
direct inputs, while test doubles impersonate the Depended Upon Components
(DOCs), monitoring outputs and providing controlled indirect inputs. This
approach allows comprehensive testing without actual hardware or OS
dependencies.

Hardware abstraction layers (HAL) and OS abstraction layers (OSAL) serve dual
purposes: they provide portability between environments and enable testability.
By routing all hardware and OS access through these thin layers, we can
substitute test doubles during testing while maintaining the same interface for
production use.

For the LightScheduler example, we use link-time substitution to completely
eliminate OS and hardware dependencies in the test executable. This technique
replaces entire problem modules with test doubles at link time, creating a clean
testing environment while preserving the module interfaces.

The LightScheduler receives instructions from an AdminConsole to control lights
at specific times. Every minute, it gets pinged through a TimeService callback
(OS abstraction) and commands LightController (hardware abstraction) to turn
lights on/off. By testing the scheduler logic separately from its dependencies
using test doubles, we can verify the core functionality without requiring
actual hardware or real-time OS interactions.

Each component has distinct responsibilities: LightScheduler handles application
logic, LightController manages hardware interactions, and TimeService provides
OS time services. This separation enables effective testing by allowing
independent verification of each layer's functionality through appropriate test
doubles.