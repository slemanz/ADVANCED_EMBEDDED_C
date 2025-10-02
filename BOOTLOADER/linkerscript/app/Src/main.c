#include <stdio.h>
#include "config.h"
#include "led.h"
#include "button.h"
#include "driver_systick.h"
#include "driver_adc.h"
#include "driver_uart.h"

unsigned char __attribute__((section(".custom_ram_block"))) custom_ram_buff[10]; // 10 bytes
unsigned char __attribute__((section(".custom_flash_block"))) custom_flash_buff[10]; // 10 bytes

int main(void)
 {
    config_drivers();
    config_bsp();
    printf("\nInit board...\n\r");

    uint64_t start_time = ticks_get();

    custom_ram_buff[0] = 10;
    (void)custom_ram_buff[0];

    while (1)
    {   
        // blinky
        if((ticks_get() - start_time) >= 500)
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