#include "adc_logger.h"
#include "button.h"
#include <stdio.h>

static uint32_t logged_read(ADCLogger_t *self)
{
    uint32_t value = self->wrapped->read();

    if(button_get_state())
    {
        char buffer[50];
        snprintf(buffer, sizeof(buffer), "ADC Value %lu\n", value);
        self->uart_transmit(buffer);
    }

    return value;
}

void ADCLogger_Init(ADCLogger_t *logger, const ADCInterface_t *adc, void (*uart)(const char *))
{
    logger->wrapped = adc;
    logger->uart_transmit = uart;
    logger->interface.read = (uint32_t (*)(void))logged_read;
}