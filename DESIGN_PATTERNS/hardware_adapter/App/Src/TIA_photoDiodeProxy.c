#include "driver_adc.h"

uint32_t getSpO2(void)
{
    return (uint32_t)adc_read(9);
}

uint32_t getPulse(void)
{
    return (uint32_t)adc_read(9);
}