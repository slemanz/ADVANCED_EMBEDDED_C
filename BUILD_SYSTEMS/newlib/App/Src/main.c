#include <stdio.h>
#include "config.h"
#include "driver_gpio.h"

int main(void)
{
    config_drivers();

    while(1)
    {
        GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_5);
        for(uint32_t i = 0; i < 1000000; i++);
    }
}