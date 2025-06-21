#include "stm32g0.h"
#include "config.h"
#include <stdio.h>

#include "device.h"


int main(void)
{
    config_drivers();
    uint64_t start_time = ticks_get();

    printf("Init\n");
    //test_setup();

    // PA5
    DevicePtr device;

    const char* name  = "User LED";
	Address addr = {GPIOA, 5};

    device = createDevice(name, &addr);

    turnOnDevice(device);


    while(1)
    {
        //blinky
        if((ticks_get() - start_time) >= 2000)
        {
            toggleDevice(device);
            start_time = ticks_get();
        }
    }
}

