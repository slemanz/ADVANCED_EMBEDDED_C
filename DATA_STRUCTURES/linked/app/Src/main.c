#include <stdio.h>
#include "config.h"
#include "driver_systick.h"
#include "driver_uart.h"

#include "led.h"
#include "driver_adc.h"

#define COMMAND_QUEUE_SIZE      32  // Maximum number of commands that can be stored

// Enumeration for the different kinds of commands
typedef enum{
    COMMAND_LED_ON = 1, // Turn the LED on
    COMMAND_LED_OFF,    // Turn the LED off
    COMMAND_READ_ADC    // Read the ADC value
}CommandType_t;

// Struct representing the command.
typedef struct{
    CommandType_t command_type;     // type of command
    uint32_t data;                  // command data
}Command_t;

// Structure to represent a node in the linked list
typedef struct node
{
    Command_t command;  // Command to be performed
    struct node *next;  // poiner to next node in the list
}Node_t;

// Structure representing the linked list of commands
typedef struct{
    Node_t *head;
}LinkedList_t;

static LinkedList_t command_queue;

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