#include <stdio.h>
#include "config.h"
#include "led.h"
#include "button.h"
#include "driver_systick.h"
#include "driver_adc.h"
#include "driver_uart.h"
#include "driver_rtc.h"

/* Configuration patameters */

#define MEMORY_POOL_SIZE        10  // Number of memory pools
#define MEMORY_BLOCK_SIZE       32  // Size of each memory block in bytes
#define ALIGNMENT               4   // Align memory blocks to 4-byte boundaries

/* Memory Pool Data Structure */
typedef struct MemBlock
{
    struct MemBlock *next;      // Pointer to the next free block
}MemBlock_t;

typedef struct{
    uint8_t pool[MEMORY_POOL_SIZE][MEMORY_BLOCK_SIZE];    // Pre-allocated memory
    MemBlock_t *freelist;               // Linked list of free block
}MemoryPool_t;


int main(void)
 {
    config_drivers();
    config_bsp();

    printf("\nInit board...\n\r");


    while (1)
    {   
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