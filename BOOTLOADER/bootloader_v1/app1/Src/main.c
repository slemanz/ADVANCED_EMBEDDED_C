#include <stdio.h>
#include "config.h"
#include "led.h"
#include "button.h"
#include "driver_systick.h"
#include "driver_uart.h"


#define APPLICATION_ADDRESS         0x08008000


typedef void (*func_ptr)(void);

void jmp_to_default_app(void)
{
    uint32_t app_start_address;
    func_ptr jump_to_app;

    printf("Bootloader started...\n");
    ticks_delay(300);

    app_start_address = *(uint32_t*)(APPLICATION_ADDRESS + 4);
    jump_to_app = (func_ptr)app_start_address;

    /* Initialize main stack pointer */
    // implement

    jump_to_app();
}

int main(void)
 {
    config_drivers();
    config_bsp();

    printf("\nInit app...\n\r");

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