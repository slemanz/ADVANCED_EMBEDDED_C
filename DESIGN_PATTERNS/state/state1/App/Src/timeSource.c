#include "timeSource.h"
#include "stm32g0.h"
#include <stdio.h>

/* Configure TIM2 to wrap around at 1 hz*/
// 16 000 000 / 1 600 = 10 000 -> PSC
// 10 000 / 10 000 = 1 -> ARR
void timer2_sec_set(int max_sec, long *current_count)
{
    /* 1. Enable clock access to tim2 */
    RCC->APBENR1 |= (1U << 0);

    /* 2. Scale clock to 1 Hz*/
    TIM2->PSC = 1600 - 1;
    TIM2->ARR = 10000 - 1;

    /* 3. Clear timer counter */
    TIM2->CNT = 0;

    /* 4. enable tim2*/
    TIM2->CR1 = (1U << 0);


    long seconds = 0;
    for(int i = 0; i < max_sec; i++)
    {
        while(!(TIM2->SR & 1)); // wait for UIF set
        seconds++;
        *current_count = seconds;
        printf("Elapsed time: %ld\n", seconds);
        
        // clear UIF
        TIM2->SR &= ~(1U << 0);
    }
}


void timer2_sec_reset(void)
{
    TIM2->CR1 = 0;
}

void systick_millis_set(int max_millis, long *current_count);
void systick_millis_reset(void);