#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "config.h"
#include "driver_systick.h"
#include "driver_uart.h"

#include "led.h"
#include "driver_adc.h"


#define MAX_EVENT_DESC_LEN      32

typedef struct EventNode{
    uint32_t timestamp;                     // Timestamp from RTC
    char description[MAX_EVENT_DESC_LEN];   // Event description
    struct EventNode *next;                 // Pointer to the next node
}EventNode_t;

static EventNode_t *event_list_head = NULL;
static uint32_t get_current_timestamp(void);
void  handle_uart_command(const char * command);

void add_event(const char *description)
{
    // Allocate memory for the new node
    EventNode_t *new_event = (EventNode_t*)malloc(sizeof(EventNode_t));
    if(!new_event)
    {
        printf("Memory allocation failed\n");
        return;
    }

    // populate the new event node
    new_event->timestamp = get_current_timestamp();
    snprintf(new_event->description, MAX_EVENT_DESC_LEN, "%s", description);
    new_event->next = NULL;

    // Insert the new event at the end of the list
    if(!event_list_head)
    {
        event_list_head = new_event;
    }else
    {
        EventNode_t *current = event_list_head;
        while(current->next)
        {
            current = current->next;
        }
        current->next = new_event;
    }
}

void print_event_list(void)
{
    if(!event_list_head)
    {
        printf("No event to display\n");
        return;
    }

    EventNode_t *current = event_list_head;
    printf("Event list: \n");

    while(current)
    {
        printf("Timestamp %lu, Description: %s\n", current->timestamp, current->description);
        current = current->next;
    }
}


/**
 * @brief Remove an event by its timestamp.
 * @param timestamp Timestamp of the event to remove.
 */
void remove_event(uint32_t timestamp)
{
    EventNode_t *current = event_list_head;
    EventNode_t *prev = NULL;

    while(current)
    {
        if(current->timestamp == timestamp)
        {
            if(prev)
            {
                prev->next = current->next;
            }else
            {
                event_list_head = current->next;
            }
            free(current);
            printf("Event with timestamp %lu removed.\n", timestamp);
        }

        prev = current;
        current = current->next;
    }
}

/**
 * @brief Get the current timestamp from the RTC.
 * @return Current timestamp as a 32-bit integer.
 */
static uint32_t get_current_timestamp(void)
{
    return 0;
}

int main(void)
 {
    config_drivers();
    config_bsp();

    adc_start_conversion();
    printf("\nInit board...\n\r");

    //uint64_t start_time = ticks_get();


    while (1)
    {   
        ticks_delay(100);
    }
}


uint8_t received_data;
void USART2_IRQHandler(void)
{
    if(UART2->SR & UART_SR_RXNE)
    {
        received_data = UART2->DR;
    }
}
            

void  handle_uart_command(const char * command)
{
    if(strstr(command, "add_event") == command)
    {
        char description[MAX_EVENT_DESC_LEN];
        sscanf(command, "add_event %s", description);
        add_event(description);
    }
    else if(strcmp(command, "print_events") == 0)
    {
        print_event_list();
    }else if(strstr(command, "remove_event") == command)
    {
        uint32_t timestamp;
        sscanf(command, "remove_event %lu", &timestamp);
        remove_event(timestamp);
    }
    else
    {
        printf("Unknown command: %s\n", command);
    }
}