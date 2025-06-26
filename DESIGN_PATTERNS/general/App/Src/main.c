#include "stm32g0.h"
#include "config.h"
#include <stdio.h>

void btn_update(void);

int main(void)
{
    config_drivers();
    printf("Init\n");

    uint64_t start_time = ticks_get();

    while(1)
    {
        btn_update();

        if((ticks_get() - start_time) >= 10000)
        {
            printf("Working\n");
            start_time = ticks_get();
        }
    }
}

uint8_t btnState = 0, btnStateOld = 0;

void btn_update(void)
{
    btnState = GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NO_13);
    if(btnState && (btnStateOld != btnState))
    {
        GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_5, GPIO_PIN_RESET);
        btnStateOld = btnState;
    }else if(btnStateOld != btnState)
    {
        GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_5, GPIO_PIN_SET);
        btnStateOld = btnState;
    }
}

