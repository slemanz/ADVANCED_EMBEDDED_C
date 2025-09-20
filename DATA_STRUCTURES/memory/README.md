# Memory Allocations

**Static Memory Allocation**

- Static memory allocation occurs at compile-time, meaning memory space is
predefined and cannot be changed at runtime.

- The compiler assigns addresses to variables and allocates memory in the.bss
and .data sections of the executable file.

- Memory is allocated once and remains allocated throughout program execution.

- All static variables have fixed memory locations.

- No risk of fragmentation or runtime memory leaks.

- Predictability - Memory allocation is known at compile time, making debugging
easier.

- No fragmentation - Unlike dynamic memory, static allocation does not suffer
from memory fragmentation.

- Faster execution - No overhead from runtime memory allocation functions
(`malloc()`, `free()`).

- Memory inefficiency - Pre-allocated memory may be wasted if not fully utilized.

- Lack of flexibility - Cannot adjust memory size at runtime.

**Dynamic Memory Allocation**

- Dynamic memory allocation occurs at runtime, allowing memory to be allocated
and deallocated as needed.

- This is typically done using malloc(), calloc(), realloc(), and free()
functions from the C standard library.

- Memory is allocated and freed during program execution.

- Uses the heap memory region.

- Enables flexible memory management for varying data sizes.

- Efficient use of RAM - Memory is allocated only when needed.

- Flexible data structures - Enables use of dynamic structures like linked lists
and variable-sized buffers.

- Heap fragmentation - Frequent allocation and deallocation can fragment memory,
reducing available contiguous space

- Unpredictability - Memory allocation success is not guaranteed, and malloc()
may return NULL if RAM is exhausted.

- Performance overhead - Allocating and freeing memory at runtime incurs
computational overhead.

### Static Allocation in Realtime_Systems

Real-time embedded systems operate under strict timing constraints where
deterministic execution is essential.

Static Vs Dynamic:

| Factor                | Static Allocation                         | Dynamic Allocation |
| --- | --- | --- |
| Execution Time        | Deterministic (fixed at compile-time)     | Non-deterministic (depends on heap availability) |
| Memory Fragmentation  | No fragmentation                          | Heap fragmentation can cause allocation failures |
| Overhead              | Zero runtime overhead                     | CPU-intensive allocation/deallocation |
| Reliability           | More predictable behavior                 | Risk of memory leaks, dangling pointers |
| Real-Time Safety      | Ensures WCET (Worst-Case Execution Time)  | Unbounded allocation time disrupts RT execution |

**Downsides of Using Excessive Global and Static Variables**

While global and static variables provide persistent storage throughout program
execution, excessive use can introduce performance, debugging, and
maintainability challenges.

|Problem                    | Impact on Embedded Systems |
| --- | --- |
| Increased Memory Usage    | Every global/static variable consumes SRAM, reducing memory for stack/heap. |
| Reduced Modularity        | Global variables tie functions together, making reuse harder. |
| Data Inconsistency        | If a variable is modified in multiple locations, debugging becomes complex. |
| Race Conditions           | In multi-threaded or interrupt-driven systems, global variables require synchronization. |



