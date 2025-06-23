#include "stm32g0.h"
#include "config.h"
#include <stdio.h>

#include "timeSource.h"

int main(void)
{
    config_drivers();
    printf("Init\n");

    long seconds = 0;
    
    while(1)
    {
        timer2_sec_set(2, &seconds);
        GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_5);
    }
}