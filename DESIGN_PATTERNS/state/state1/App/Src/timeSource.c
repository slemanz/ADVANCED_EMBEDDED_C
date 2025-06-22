#include "timeSource.h"
#include "stm32g0.h"

/* Configure TIM2 to wrap around at 1 hz*/
// 16 000 000 / 1600 = 10000 -> PSC
// 10 000 / 10 000 = 1 -> ARR
void timer2_sec_set(int max_sec, long *current_count)
{
    /* 1. Enable clock access to tim2 */
    RCC->APBENR1 |= (1u << 0);

    /* 2. Scale clock to 1 Hz*/

    /* 3. Clear timer counter */

    /* 4. enable tim2*/
}


void timer2_sec_reset(void);

void systick_millis_set(int max_millis, long *current_count);
void systick_millis_reset(void);