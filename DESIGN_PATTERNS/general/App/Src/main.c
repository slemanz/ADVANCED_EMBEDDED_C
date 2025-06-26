#include "stm32g0.h"
#include "config.h"
#include <stdio.h>

void btn_update(void);

int main(void)
{
    config_drivers();
    printf("Init\n");

    uint64_t start_time = ticks_get();

    printf("TS_CAL1 = %d\n", MMIO16(TS_CAL1_BASEADDR));
    printf("TS_CAL2 = %d\n", MMIO16(TS_CAL2_BASEADDR));
    printf("ADC TEMP = %d\n\n\n", adc_read(12));

    float test = adc_read_temperature();
    printf("Temperature: %.2f C\n", test);

    while(1)
    {
        btn_update();

        if((ticks_get() - start_time) >= 500)
        {
            GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_5);
            start_time = ticks_get();
        }
    }
}

uint8_t btnState = 0, btnStateOld = 1;
uint16_t adc_value = 0;

void btn_update(void)
{

    btnState = GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NO_13);
    if(btnState && (btnStateOld != btnState))
    {
        adc_value = adc_read(0);
        printf("Adc value: %d\n", adc_value);
        btnStateOld = btnState;
    }else if(btnStateOld != btnState)
    {
        btnStateOld = btnState;
    }
}

