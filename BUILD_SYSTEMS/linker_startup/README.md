# Linker and Startup

### Memory Model

1. Flash Memory:
    - Read-Only
    - Size depends on specific microcontroller
    - Program code is stored here.
    - Contains a vector table, this consists of pointers to
    the various exception handles.

2. SRAM:
    - Read and Write
    - Begins at 0x20000000
    - Size depends on specific microcontroller
    - Variables and Stack are stored here

## Linker Script

- Script given to the linker in order to specify the memory layout
and to initialize the various memory sections used by the firmware.

- The linker script is responsible for making sure various portions
of the firmware are in their proper place and also for associating
meaningful labels with specific regions of memory used by the startup
code.

**The script has 4 features:**

- Memory Layout : available memory types
- Section Definitions: placing specific parts at specific locations
- Options : commands e.g. ENTRY POINT
- Symbols: variables to inject into program at link time

### Memory

In order to allocate program memory, the linker needs to know the types
of memory, their addresses and sizes. We use the `MEMORY` definition to
provide this information

```
MEMORY
{
    name [(attr)] ORIGIN origin, LENGTH = len
}
```

```
MEMORY
{
    FLASH(rx):ORIGIN =0x08000000, LENGTH =512K
    SRAM(rwx):ORIGIN =0x20000000, LENGTH =128K
}
```

### Sections

Code and data are organized into sections. Symbols of the same memory
region are placed in the same s

```
SECTIONS
{

}
```

```
E.g.
SECTIONS
{
    .text:
    {
        *(.text) /*merge all text sections of input files */
    }> FLASH
}
```

The 3 relevant sections:

- **.text** - Placed in the FLASH
- **.data** - Placed in the SRAM
- **.bss**  - Placed in the SRAM

### VMA and LMA

- **LMA:** Load Memory Address, the address at which a section is loaded.

- **VMA:** Virtual Memory Address, the address of a section during execution.

The Linker distinguishes between the VMA and LMA address.

### Load memory

Flash memory:

```
┌────────────────┐
│                │
│                │
│                │
├────────────────┤
│                │
│    .data       │
│                │
├────────────────┤
│                │
│   .rodata      │
│                │
├────────────────┤
│                │
│    .text       │
│                │
├────────────────┤
│  .isr_vector   │
└────────────────┘ 0x0800 0000
```

In startup code, copy .data from `FLASH` to `SRAM`:

```
┌────────────────┐
│                │
│                │
├────────────────┤
│     .bss       │
├────────────────┤
│     .data      │
└────────────────┘ 0x2000 0000
```

### Some Commands

- **ENTRY**: Sets program entry address.

- **MEMORY**: Describes the locations and sizes of the different
memories available.

- **ALIGN**: Inserts padding to align location.

- **SECTIONS**: Used to map input sections to output sections and
describes how to place output sections in memory.

- **KEEP**: Tells linker to keep the specified section even if no
symbols in that section are referenced.

- **AT >**: This is a directive, it tells the linker to load a section's
data to somewhere other than the address it is located at.

### Constants

- The linker considers an integer with:
    - 0 as Octal
    - Ox as hexadecimal

- Suffixes K and M may be used to scale a constant by 1024 or by
1024*1024 respectively

Different ways of writing the same quantity :

- _four_1 = 4K

- _four_2 = 4096;

- _four_3 = 0x1000;

## Startup Code

1. Reset Handler
    - This functions copies the initial values for variables from the
    `FLASH` where the linker places them to the `SRAM`.
    - It also zeros out the uninitialized data portion of the `SRAM`.

2. Interrupt Vector Table

    - This is an array that holds memory address of interrupt handler
    functions
    - In order to allow application code to conveniently redefine the
    various interrupt handlers, every required vector is assigned an
    overideable `_weak` alias to a default function which loops forever.