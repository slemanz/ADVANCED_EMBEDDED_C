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