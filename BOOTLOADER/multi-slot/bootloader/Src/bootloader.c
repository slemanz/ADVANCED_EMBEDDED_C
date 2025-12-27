#include <stdio.h>
#include "config.h"
#include "led.h"
#include "button.h"
#include "driver_systick.h"
#include "driver_uart.h"





int main(void)
 {
    config_drivers();
    config_bsp();

    printf("\r\nInit bootloader...\r\n");

    uint64_t start_time = ticks_get();
    uint64_t start_time2 = ticks_get();
    uint64_t jump_time = 5000;

    while (1)
    {   
        // blinky
        if((ticks_get() - start_time) >= 500)
        {
            led_toggle();
            start_time = ticks_get();
        }

        if((ticks_get() - start_time2) >= jump_time)
        {
            INTERRUPT_DISABLE();
            jmp_to_default_app();

            jump_time = 900000;
            start_time2 = ticks_get();
        }
    }
}

volatile char g_key = 0;

static void uart_callback(void)
{
    g_key = UART2->DR;

    if(g_key == '1')
    {
        printf("Key pressed: 1\n\r");
    }else
    {
        printf("Key presseder: Other\n\r");
    }
}

void USART2_IRQHandler(void)
{
    if(UART2->SR & UART_SR_RXNE)
    {
        uart_callback();
    }
}