#include "driver_adc.h"

uint32_t getSpO2(void)
{
    uint32_t volt;
    volt = (adc_read(0))/(4095)*3.3;
    return volt;
}

uint32_t getPulse(void)
{
    uint32_t volt;
    volt = (adc_read(0))/(4095)*3.3;
    return volt;
}