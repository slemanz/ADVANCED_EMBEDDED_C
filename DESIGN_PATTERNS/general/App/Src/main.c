#include "stm32g0.h"
#include "config.h"
#include <stdio.h>


int main(void)
{
    config_drivers();
    printf("Init\n");

    uint64_t start_time = ticks_get();


    while(1)
    {
        if((ticks_get() - start_time) >= 200)
        {
            GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_5);
            start_time = ticks_get();
        }
    }
}

