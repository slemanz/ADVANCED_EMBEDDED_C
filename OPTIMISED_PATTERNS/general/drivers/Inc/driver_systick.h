#ifndef DRIVER_SYSTICK_H_
#define DRIVER_SYSTICK_H_

#include "stm32f411xx.h"

#define TICK_HZ                 1000U
#define SYSTICK_TIM_CLK			HSI_CLOCK

uint64_t ticks_get(void);
void systick_init(uint32_t tick_hz);

#endif