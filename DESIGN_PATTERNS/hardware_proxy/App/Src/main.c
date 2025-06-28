#include "stm32g0.h"
#include "config.h"
#include <stdio.h>

int main(void)
{
    config_drivers();
    printf("Init\n");

    while(1)
    {
    }
}