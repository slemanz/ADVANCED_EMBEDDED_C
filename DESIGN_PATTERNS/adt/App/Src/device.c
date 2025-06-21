#include "device.h"
#include "driver_uart.h"

#include <stdio.h>
#include <stdlib.h>

typedef uint32_t deviceID_t;

struct Device{
    const char *name;
    Address address;
    deviceID_t uuid;
};

uint32_t noOfdevices = 0;

DevicePtr createDevice(const char *name, const Address *address)
{
    DevicePtr device = (DevicePtr)calloc(sizeof(DevicePtr), sizeof(DevicePtr));

    if(device)
    {
        device->name = name;
        noOfdevices++;
        device->address.Port = address->Port;
        device->address.Pin = address->Pin;
        device->uuid = noOfdevices;

        /* Enable clock access to device Port */
        switch((int)device->address.Port)
        {
            case (int)GPIOA: RCC->IOPENR |= GPIOA_EN; break;
            case (int)GPIOB: RCC->IOPENR |= GPIOB_EN; break;
            case (int)GPIOC: RCC->IOPENR |= GPIOC_EN; break;

        }

    }else
    {
        printf("Low memory, cannot create device\n");
    }

}