#include "config.h"
#include <stdio.h>
#include "driver_systick.h"
#include "driver_uart.h"
#include "led.h"
#include "button.h"

#define UART_SINGLETON_ENABLE

// printf retarget
extern int __io_putchar(int ch)
{
#ifdef UART_SINGLETON_ENABLE
    UART_Singleton_t *uart = uart_get_instance();

	if(uart && uart->is_initialized)
	{
	    uart_write(uart, ch);
	}
	return ch;
#else
    uart2_write_byte((uint8_t)ch);
    return ch;
#endif

}

int main(void)
 {
    config_drivers();
    config_bsp();

#ifdef UART_SINGLETON_ENABLE
    UART_Singleton_t *uart = uart_get_instance();
#else
    uart2_init();
#endif


    printf("\nInit board...\n\r");

#ifdef UART_SINGLETON_ENABLE
    if(uart->is_initialized)
    {
        printf("Working\n");
    }
#endif




    uint64_t start_time = ticks_get();
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