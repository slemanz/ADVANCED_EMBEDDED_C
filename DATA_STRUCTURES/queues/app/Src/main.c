#include <stdio.h>
#include <stdbool.h>
#include "config.h"
#include "led.h"
#include "button.h"
#include "driver_systick.h"
#include "driver_adc.h"
#include "driver_uart.h"

int main(void)
 {
    config_drivers();
    config_bsp();

    adc_start_conversion();

    printf("\nInit board...\n\r");

    uint64_t start_time = ticks_get();

    while (1)
    {   
        if((ticks_get() - start_time) >= 1000)
        {
            printf("Adc value: %lu\n", adc_read());
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
    }
}