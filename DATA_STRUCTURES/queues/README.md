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