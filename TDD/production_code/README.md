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