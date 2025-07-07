#include "driver_systick.h"

uint64_t ticks = 0;


void systick_init(uint32_t tick_hz)
{
    uint32_t count_value = SYSTICK_TIM_CLK/tick_hz;

    // clear the value of SVR (value reload)
    SYSTICK->LOAD &= ~(0x00FFFFFFFF);
    
    // load the value
    SYSTICK->LOAD |= count_value;

    // setting and enable
    SYSTICK->CTRL |= (1 << 1);
    SYSTICK->CTRL |= (1 << 2);

    SYSTICK->CTRL |= (1 << 0);
}

uint64_t ticks_get(void)
{
    return ticks;
}

void SysTick_Handler(void)
{
    ticks++;
}