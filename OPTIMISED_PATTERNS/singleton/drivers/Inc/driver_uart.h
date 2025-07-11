#ifndef DRIVER_UART_H_
#define DRIVER_UART_H_

#include "stm32f411xx.h"

#define UART_CR1_TE					(1U<<3)
#define UART_CR1_UE					(1U<<13)
#define UART_SR_TXE					(1U<<7)

typedef struct 
{
    UART_RegDef_t *uart_handle;
    uint8_t is_initialized;
}UART_Singleton_t;


void uart2_init(void);
void uart2_init_pins(void);
void uart2_write_byte(uint8_t data);

#endif