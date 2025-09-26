#include "driver_uart.h"
#include "driver_gpio.h"
#include "driver_interrupt.h"
#include <stddef.h>

static uint16_t compute_uart_div(uint32_t PeriphClk, uint32_t BaudRate);

static uint16_t compute_uart_div(uint32_t PeriphClk, uint32_t BaudRate)
{
    return ((PeriphClk + (BaudRate/2U))/BaudRate);
}

/* Memory Pool Configuration */
#define POOL_BLOCK_SIZE         64  // Size of each memory block in bytes
#define POOL_NUM_BLOCKS         10  // Number of memory pools

/*** Memory Pool Data Structure ***/
typedef struct mem_block
{
    struct  mem_block *next_block; // pointer to the next free block
}mem_block_t;

typedef struct{
    uint8_t pool[POOL_NUM_BLOCKS][POOL_BLOCK_SIZE]; // Memory pool array
    mem_block_t *free_list;
}memory_pool_t;


static memory_pool_t uart_memory_pool;

/**
 * @brief Initializes the memory pool by linking all blocks into a free list
 */
void MemoryPool_Init(void)
{
    uart_memory_pool.free_list = (mem_block_t*)uart_memory_pool.pool;

    // List all blocks together in a free list
    for(int i = 0; i < POOL_NUM_BLOCKS - 1; i++)
    {
        ((mem_block_t*)uart_memory_pool.pool[i])->next_block = (mem_block_t*)uart_memory_pool.pool[i+1];
    }

    ((mem_block_t*)uart_memory_pool.pool[POOL_NUM_BLOCKS - 1])->next_block = NULL;
}

/**
 * @brief Allocates a block of memory from the memory pool
 * @retval Pointer to allocated block, or NULL if poolis exhausted
 */
void *MemoryPool_Allocate(void)
{
    if(uart_memory_pool.free_list == NULL)
    {
        return NULL;
    }

    mem_block_t *allocated_block = uart_memory_pool.free_list;  // Taking first block
    uart_memory_pool.free_list = allocated_block->next_block;   // Move free list pointer

    return (void *)allocated_block;
}


void uart2_init(void)
{
    uart2_init_pins();
    UART2_PCLK_EN();

    // no flow control (default reset)
    uint32_t temp = ((UART_CR1_TE) | (UART_CR1_RE)); // tx and rx enable
    temp |= (UART_CR1_RXNEIE);
    UART2->CR1 = temp; 
    UART2->BRR = compute_uart_div(16000000, 115200); // baurate

    interrupt_config(38, ENABLE); // enable usart2 interrupt

    UART2->CR1 |= UART_CR1_UE;// enable uart periph
}

void uart2_write_byte(uint8_t data)
{
	while(!(UART2->SR & UART_SR_TXE));
    UART2->DR = data;
}

void uart2_init_pins(void)
{
    GPIO_Handle_t UartPin;

    UartPin.pGPIOx = GPIOA;
    UartPin.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
    UartPin.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_2;
    UartPin.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    UartPin.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    UartPin.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    UartPin.GPIO_PinConfig.GPIO_PinAltFunMode = PA2_ALTFN_UART2_TX;

    GPIO_Init(&UartPin);

    UartPin.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_3;
    GPIO_Init(&UartPin);
}