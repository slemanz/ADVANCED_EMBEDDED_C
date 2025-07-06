#ifndef DRIVER_UART_H_
#define DRIVER_UART_H_

#include "stm32f411xx.h"


void uart2_init(void);
void uart2_write_byte(uint8_t data);
void uart2_init_pins(void);

#endif