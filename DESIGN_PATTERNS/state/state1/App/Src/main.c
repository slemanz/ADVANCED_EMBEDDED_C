#include "stm32g0.h"
#include "config.h"
#include <stdio.h>

#include "timeSource.h"

int main(void)
{
    config_drivers();
    printf("Init\n");

    long milliseconds = 0;
    
    while(1)
    {
        systick_millis_set(2500, &milliseconds);
        GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_5);
    }
}