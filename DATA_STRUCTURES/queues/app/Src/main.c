#include <stdio.h>
#include <stdbool.h>
#include "config.h"
#include "led.h"
#include "button.h"
#include "driver_systick.h"
#include "driver_adc.h"
#include "driver_uart.h"

#define MAX_TASKS           10

/* Task function pointer */
typedef void (*TaskFunction)(void);

/* Task structure */
typedef struct
{
    uint8_t priority; // priority of the task (lower value means higher priority)
    TaskFunction task;
}Task_t;

static Task_t task_queue[MAX_TASKS];
static uint8_t task_count = 0;


void add_task(TaskFunction task, uint8_t priority);
void execute_tasks(void);

//example tasks
void task_led_toggle(void);
void task_read_adc(void);
void task_send_data(void);


typedef uint32_t task_profiler;
task_profiler task1_profiler, task2_profiler, task3_profiler;

int main(void)
 {
    config_drivers();
    config_bsp();

    adc_start_conversion();

    printf("\nInit board...\n\r");

    uint64_t start_time = ticks_get();

    while (1)
    {   
        if((ticks_get() - start_time) >= 1000)
        {
            printf("Adc value: %lu\n", adc_read());
            start_time = ticks_get();
        }
    }
}


void add_task(TaskFunction task, uint8_t priority)
{
    if(task_count >= MAX_TASKS)
    {
        printf("Task queue is full\n");
        return;
    }

    /* Insert the task into the queue based on priority */
    uint8_t i = task_count;
    while(i > 0 && task_queue[i-1].priority > priority)
    {
        task_queue[i] =  task_queue[i  -1];
		i--;
    }

    task_queue[i].task =  task;
	task_queue[i].priority =  priority;
	task_count++;
}


uint8_t received_data = 0;
void USART2_IRQHandler(void)
{
    if(UART2->SR & UART_SR_RXNE)
    {
        received_data = UART2->DR;
    }
}