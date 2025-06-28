#include "device.h"
#include <stdio.h>
#include <stdlib.h>

struct Device
{
    const char *name;
    gpioStrategy deviceStrategy;
};


devicePtr device_create(const char *name, gpioStrategy deviceStrategy)
{
    return NULL;
}

void device_change(devicePtr device, gpioStrategy newDeviceStrategy)
{

}

void device_set(devicePtr device, int device_num)
{

}

void device_destroy(devicePtr device)
{

}