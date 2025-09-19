#include <stdio.h>
#include "config.h"
#include "led.h"
#include "button.h"
#include "driver_systick.h"
#include "driver_adc.h"

int main(void)
 {
    config_drivers();
    config_bsp();

    printf("\nInit board...\n\r");

    uint32_t adc_value = 0;

    uint64_t start_time = ticks_get();

    while (1)
    {   
        // blinky
        if((ticks_get() - start_time) >= 500)
        {
            led_toggle();
            start_time = ticks_get();
        }

        // blinky 2
        /*
        GPIO_ToggleOutputPin(LED_PORT, LED_PIN);
        ticks_delay(500);
        */

        if(!button_get_state())
        {
            adc_start_conversion();
            adc_value = adc_read();
            printf("Adc: %ld\n", adc_value);
            while(!button_get_state());
        }
    }
}