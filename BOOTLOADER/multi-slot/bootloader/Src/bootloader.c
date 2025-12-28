#include <stdio.h>
#include "config.h"
#include "led.h"
#include "button.h"
#include "simple-timer.h"

#include "driver_uart.h"

int main(void)
 {
    config_drivers();
    config_bsp();

    printf("\r\nInit bootloader...\r\n");

    simple_timer_t timer_blink;
    simple_timer_t timer_jump;
    
    simple_timer_setup(&timer_blink, 100, true);
    simple_timer_setup(&timer_jump, 4700, false);

    while (1)
    {   
        if(simple_timer_has_elapsed(&timer_blink))
        {
            led_toggle();
        }

        if(simple_timer_has_elapsed(&timer_jump))
        {
            INTERRUPT_DISABLE();
            jmp_to_default_app();

            simple_timer_setup(&timer_blink, 500, true);
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
        printf("Key pressed: Other\n\r");
    }
}

void USART2_IRQHandler(void)
{
    if(UART2->SR & UART_SR_RXNE)
    {
        uart_callback();
    }
}