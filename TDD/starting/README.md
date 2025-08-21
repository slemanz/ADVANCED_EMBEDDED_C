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

### **The Three-File Convention for Every Module:**

To consistently apply these concepts, follow this structure for each module you create:

| File Type | Purpose | Contains |
| --- | --- | --- |
| **Header (.h)** | **Public Interface** | Function prototypes. For ADTs, a `typedef` for a pointer to a hidden struct. |
| **Source (.c)** | **Private Implementation** | The full code for all functions, private `static` helpers, and the actual definition of hidden data structs. |
| **Test (.c or .cpp)** | **Verification** | All test cases for the module, separate from production code. |
