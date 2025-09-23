#include <stdio.h>
#include "config.h"
#include "driver_systick.h"
#include "driver_uart.h"

int main(void)
 {
    config_drivers();
    config_bsp();

    printf("\nInit board...\n\r");

    //uint64_t start_time = ticks_get();

    while (1)
    {   
    }
}

void USART2_IRQHandler(void)
{
    uint8_t ch;

    if(UART2->SR & UART_SR_RXNE)
    {
        ch = UART2->DR;
        uart2_write_byte(ch);
    }
}