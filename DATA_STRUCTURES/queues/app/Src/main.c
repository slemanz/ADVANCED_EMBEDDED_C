#include <stdio.h>
#include "config.h"
#include "led.h"
#include "button.h"
#include "driver_systick.h"
#include "driver_adc.h"
#include "driver_uart.h"
#include "driver_rtc.h"

#define QUEUE_SIZE     32

/* Structre to represent the queue */
typedef struct {
    uint8_t buffer[QUEUE_SIZE]; // Fixed-size buffer for queue storage
    uint8_t front;              // Index of the first element
    uint8_t rear;               // Index of the next insertion point
    uint8_t length;             // Number of elements currently in the queue
} Queue_t;

/* Queue instance for the UART RX buffer */
static Queue_t uart_rx_queue = {.front = 0, .rear = 0, .length = 0};

int main(void)
 {
    config_drivers();
    config_bsp();

    printf("\nInit board...\n\r");

    uint64_t start_time = ticks_get();

    while (1)
    {   
        // blinky
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