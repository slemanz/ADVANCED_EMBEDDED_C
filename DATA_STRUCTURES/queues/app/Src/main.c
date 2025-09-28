#include <stdio.h>
#include <stdbool.h>
#include "config.h"
#include "led.h"
#include "button.h"
#include "driver_systick.h"
#include "driver_adc.h"
#include "driver_uart.h"

#define QUEUE_SIZE          32
#define ADC_BUFFER_SIZE     64

/* Structure to represent the queue */
typedef struct{
    uint8_t buffer[QUEUE_SIZE]; // Fixed-size buffer for queue storage
    volatile uint8_t head;      // Index of the first element
    volatile uint8_t tail;      // Index of the next insertion point
}Queue_t;

/* Queue instance for UART Rx buffer */
static Queue_t uart_rx_queue = {.head = 0, .tail = 0};

/* Structure to represent the adc queue */
typedef struct{
    uint8_t buffer[ADC_BUFFER_SIZE];    // Fixed-size buffer for adc samples
    volatile uint8_t head;              // Index of the first element
    volatile uint8_t tail;              // Index of the next insertion point
}ADC_Queue_t;

/* Queue instance for ADC buffer */
static ADC_Queue_t adc_data_queue = {.head  = 0, .tail = 0};

/* Declare enum for possible commands to perform */
typedef enum
{
    COMMAND_LED_ON,
    COMMAND_LED_OFF,
    COMMAND_READ_ADC
}CommandType_t;

/* Structure for a single command */
typedef struct 
{
    CommandType_t command_type;
    uint64_t time;
}Command_t;

/* Structure to represent the command queue */
typedef struct
{
    uint8_t buffer[QUEUE_SIZE];     // Fixed-size buffer for adc samples
    volatile uint8_t head;          // Index of the first element
    volatile uint8_t tail;          // Index of the next insertion point
}CommandQueue_t;



int main(void)
 {
    config_drivers();
    config_bsp();

    printf("\nInit board...\n\r");

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

uint8_t received_data = 0;
void USART2_IRQHandler(void)
{
    if(UART2->SR & UART_SR_RXNE)
    {
        received_data = UART2->DR;
    }
}
