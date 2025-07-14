#include "config.h"
#include <stdio.h>
#include "driver_systick.h"

int main(void)
 {
    config_drivers();

    printf("\nInit board...\n\r");

    uint64_t start_time = ticks_get();

    while (1)
    {   
        if((ticks_get() - start_time) >= 500)
        {
            start_time = ticks_get();
        }
    }
}