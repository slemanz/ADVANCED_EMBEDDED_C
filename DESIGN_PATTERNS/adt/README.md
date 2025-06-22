# Abstract Data Type (ADT)

Is a conceptual model that defines a set of operations and behaviors
for a data structure, without specifying how these operations are
implemented or how data is organized in memory.

> ADT only mentions what operations are to be performed but not how these operations will be implemented.

## Implementation

In .h file, create a pointer to some struct:

```C
typedef struct Device* DevicePtr;
```

And in .c file create the struct:

```C
struct Device{
    const char *name;
    Address address;
    deviceID_t uuid;
};
```

## Implementation Example

[main.c](App/Src/main.c)
[device.h](App/Inc/device.h)
[device.c](App/Src/device.c)