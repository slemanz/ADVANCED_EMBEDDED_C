# Hardware Proxy Pattern

## Abstract

The Hardware Proxy Pattern uses a class (or struct) to encapsulate
all access to a hardware device, regardless of its physical interface.

## Problem

If every client accesses a hardware device directly, problems due to
hardware changes are exacerbated. If the bit enconding, memory address, 
or connection technology changes, then every client must be tracked down
and modified.

## Pattern Structure

There may be many clients but a single Hardware Proxy per device being
controlled. The proxy contains both pubilc functions and private encapsulate
functions and data.

## Implementation Example

**[main.c](App/Src/main.c)**

- **[motor.h](App/Inc/motor.h)**
- **[motorData.h](App/Inc/motorData.h)**
- **[motorProxy.h](App/Inc/motorProxy.h)**
- **[motorProxy.c](App/Src/motorProxy.c)**
