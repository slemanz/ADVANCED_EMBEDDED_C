# Hardware Adapter Pattern

## Abstract

Useful when the application requires or uses one interface, but the
actual hardware provides another. The pattern creates an element that
convertes between the two interfaces.

## Problem

While hardware that performs similar functions tend to have similar
interfaces, often the information they need and the set of services
differ.

## Pattern Structure

The pattern extends the hardware proxy pattern by adding a hardware
adapter and explicitly showing the interface the client expects the
hardware support.

## Implementation Example

**[main.c](App/Src/main.c)**

- **[pulseOximetrySensor](App/Inc/pulseOximetrySensor.h)**

**Light To frequency:**

- **[LTF_photoDiodeProxy.h](App/Inc/LTF_photoDiodeProxy.h)**
- **[LTF_photoDiodeProxy.c](App/Src/LTF_photoDiodeProxy.c)**
- **[LTF_pulseOximetryAdapter.h](App/Inc/LTF_pulseOximetryAdapter.h)**
- **[LTF_pulseOximetryAdapter.c](App/Src/LTF_pulseOximetryAdapter.c)**

**Transimpedance Amplifier:**

- **[TIA_photoDiodeProxy.h](App/Inc/TIA_photoDiodeProxy.h)**
- **[TIA_photoDiodeProxy.c](App/Src/TIA_photoDiodeProxy.c)**
- **[TIA_pulseOximetryAdapter.h](App/Inc/TIA_pulseOximetryAdapter.h)**
- **[TIA_pulseOximetryAdapter.c](App/Src/TIA_pulseOximetryAdapter.c)**

**Display:**

- **[oximetryDisplay.h](App/Inc/oximetryDisplay.h)**
- **[oximetryDisplay.c](App/Src/oximetryDisplay.c)**