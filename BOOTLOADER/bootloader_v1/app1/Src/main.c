#include <stdio.h>
#include "config_app.h"
#include "led.h"
#include "button.h"
#include "driver_systick.h"
#include "driver_uart.h"

int main(void)
 {
    config_drivers();
    config_bsp();

    printf("\nInit app (1)...\n\r");

    uint64_t start_time = ticks_get();

    while (1)
    {   
        // blinky
        if((ticks_get() - start_time) >= 1000)
        {
            led_toggle();
            start_time = ticks_get();
        }
    }
}

uint8_t received_data = 0;
void USART2_IRQHandler(void)
{
    if(UART2->SR & UART_SR_RXNE)
    {
        received_data = UART2->DR;
        uart2_write_byte(received_data);
    }
}