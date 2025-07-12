#ifndef DRIVER_UART_H_
#define DRIVER_UART_H_

#include <stdint.h>
#include "stm32f411xx.h"

// UART Control Macros
#define UART_CR1_TE         (1U << 3)    // Transmitter enable
#define UART_CR1_UE         (1U << 13)   // UART enable
#define UART_SR_TXE         (1U << 7)    // Transmit data register empty flag

// System Clock Configuration
#define SYS_FREQ            16000000     // 16 MHz System Clock
#define APB1_CLK            SYS_FREQ     // UART Peripheral Clock

// UART Word Length
#define UART_WORDLENGTH_8B (0U << 12)
#define UART_WORDLENGTH_9B (1U << 12)

// UART Parity
#define UART_PARITY_NONE (0U << 10)

#define UART_PARITY_EVEN (0U << 9)
#define UART_PARITY_ODD  (1U << 9)

// UART Mode
#define UART_MODE_TX     (1U << 3)
#define UART_MODE_RX     (1U << 2)
#define UART_MODE_TX_RX  ((1U << 3) | (1U << 2))

/**
 * @brief UART builder structure
 */
typedef struct
{
    uint32_t BaudRate;
    uint32_t WordLength;
    uint32_t StopBits;
    uint32_t Parity;
    uint32_t Mode;
}UART_Builder_t;

/**
 * @brief Initializes a UART_Builder_t structure with default values.
 * @return Initialized UART_Builder_t object.
 */
UART_Builder_t uart_builder_init(void);




/*
 * OLD IMPLEMENTATION
 */

void uart2_init(void);
void uart2_init_pins(void);
void uart2_write_byte(uint8_t data);

#endif