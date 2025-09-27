# Queues

These structures enable efficient data storage, retrieval, and processing in
constrained environments such as microcontrollers.

### Linear Queue

- A linear queue is a First-In-First-Out (FIFO) data structure in which elements
are inserted at one end (rear) and removed from the other (front).

- Once an element is removed, its position is not reused, leading to wasted
memory over time.

### Applications in Embedded Systems

- UART Receive Buffers - Storing received data before processing.
- Task Scheduling in Embedded RTOS - Managing task execution in FIFO order.
- Data Logging Buffers - Storing sensor readings before transmission.

### Performance Limitations

- Memory Inefficiency: Once front moves forward, unused memory remains inaccessible.
- Fixed Capacity: Linear queues cannot dynamically grow without reallocating memory.

### Circular Queues

- A circular queue is an optimized version of the linear queue where the rear
wraps around when it reaches the end, allowing memory reuse.

- The elements are arranged as if they were placed on a circle, rather than a
straight line

- This circular arrangement allows you to reuse the space at the beginning of
the allocated memory once the rear reaches the end.

**Why Circular Queues are Ideal for Embedded Systems?**

1. **Memory Efficiency:**
    - Fixed Size: You preallocate a fixed-size buffer, eliminating the overhead
    of dynamic memory allocation (which can be slow and problematic in embedded
    environments).
    - Reusing Memory: The circular nature allows you to reuse the allocated
    buffer, avoiding memory fragmentation and wasteful memory usage.

2. **Real-Time Capabilities:**
    - Deterministic Performance: The consistent time taken to enqueue and
    dequeue elements makes circular queues highly predictable, which is vital
    for real-time systems.
    - Avoiding Blocking: They prevent unbounded growth, which can lead to
    unpredictable delays or memory exhaustion in resource-constrained
    environments.

3. **Synchronization:**
    - Simple to Manage: The straightforward implementation makes them easier to
    manage with concurrency primitives like semaphores or mutexes.
    - Inter-Process Communication (IPC): Circular queues can facilitate data
    exchange between different tasks or modules in an embedded system.

### Key Properties

Front and Rear Pointers: Instead of physically moving elements, we track the
beginning and end of the queue using two pointers (or indices)

- Front: Points to the location of the first element in the queue (the next to
be dequeued).
- Rear: Points to the next available location where a new element can be
enqueued.
- Modulo Arithmetic (The Circle): The magic of a circular queue comes from using
the modulo operator (%) to wrap the indices around when they reach the end of
the array.  If an index i has reached the last position, the next index becomes
(i + 1) % capacity.

- Empty and Full Conditions:
    - Empty: The queue is empty when front equals rear.
    - Full: A full condition requires a slightly more complex approach since
    front and rear could potentially be equal both when the queue is empty and
    when it is full.

### Key Operations

**Enqueue (Add):**
- Check if the queue is full. If it is, the operation fails (or you could handle
the overflow condition in an application-specific way).
- Place the new element at the location pointed to by the rear pointer.
- Update the rear pointer: `rear = (rear + 1) % capacity`.

**Dequeue (Remove):**
- Check if the queue is empty. If it is, the operation fails.
- Read the element from the location pointed to by the front pointer.
- Update the front pointer: `front = (front + 1) % capacity.`