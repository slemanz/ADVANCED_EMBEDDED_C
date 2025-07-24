# CMSIS

CMSIS stands for **Cortex Microcontroller Software Interface Standard**.

CMSIS compliant software development tools and middleware stacks
are allowed to carry the CMSIS logo.

### Intro

- CMSIS is a vendor-independent hardware abstraction layer for
microcontrollers that are based on Arm Cortex processors.

- CMSIS defines generic tool interfaces and enables consistent
device support

- CMSIS provides simple software interfaces to the processor and the
peripherals.

### Aim

- The aim of CMSIS is to improve software portability and reusability
across different microcontrollers and toolchains.

- It allows software from different sources to integrate seamlessly together.

- CMSIS simplifies software reuse, reduces the learning curve for microcontroller
developers.

### Components

- **CMSIS(M):** For all Cortex-M and SecurCore processors. Provides standardized
API for configuring the Cortex-M processor core and peripherals. Also standardizes
the naming of the device peripheral registers. Includes intrinsic functions for
Cortex-M4/M7/M33/M35P SIMD instructions.

- **Driver:** Provides generic peripheral driver interfaces for middleware.
Connects microcontroller peripherals with middleware that implements for example
communication stacks, file systems, or graphic user interfaces.

- **DSP:** For all Cortex-M processors. DSP library collection with over 60
functions for various data types. Implementations optimized for the SIMD instruction
set are available.

- **RTOS v1:** Common API for real-time operating systems along with a reference
implementation based on RTX.

- **PACK:** Describes a delivery mechanism for software components, device parameters,
and evaluation board support. It simplifies software re-use and product life-cycle
management (PLM). 

- **DAP:** Defines the interface protocol for a hardware debug unit that sits between
the host PC and the debug access port (DAP) of the microcontroller. This allows any
software toolchain that supports CMSIS DAP to connect to any hardware debug unit that
also supports _CMSIS DAP_.

**And others...**