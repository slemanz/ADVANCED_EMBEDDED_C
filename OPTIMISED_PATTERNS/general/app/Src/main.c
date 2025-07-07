#include "config.h"
#include "stm32f411xx.h"
#include <stdio.h>

int main(void)
 {
    config_drivers();

    printf("\nInit board...\n\r");

    float n1 = 10.0, n2 = 7.0;
    float result = n1/n2;
    printf("%.2f/%.2f = %.5f\n", n1, n2, result);

    //uint64_t start_time = ticks_get();

    while (1)
    {   
        // blinky
        /*
        if((ticks_get() - start_time) >= 500)
        {
            GPIO_ToggleOutputPin(LED_PORT, LED_PIN);
            start_time = ticks_get();
        }*/

        // blinky 2
        GPIO_ToggleOutputPin(LED_PORT, LED_PIN);
        ticks_delay(500);
    }
}