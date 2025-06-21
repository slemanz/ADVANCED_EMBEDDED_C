#ifndef INC_DEVICE_H_
#define INC_DEVICE_H_

#include "address.h"
#include <stdbool.h>

typedef bool State_t;

/* Pointer to an incomplete type */
/* This hides implementation details */
typedef struct Device* DevicePtr;

DevicePtr createDevice(const char *name, const Address *address);

void turnOnDevice(DevicePtr device);
void turnOffDevice(DevicePtr device);
void toggleDevice(DevicePtr device);

State_t readDevice(DevicePtr device);
void destroyDevice(DevicePtr device);
void displayDeviceInfo(DevicePtr device);

#endif /* INC_DEVICE_H_ */