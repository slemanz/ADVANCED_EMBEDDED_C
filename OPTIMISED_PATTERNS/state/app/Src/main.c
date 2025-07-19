#include "config.h"
#include <stdio.h>
#include "driver_systick.h"
#include "led.h"
#include "button.h"

typedef void (*StateHandler)(void);

void yellowStateHandler(void);
void greenStateHandler(void);
void redStateHandler(void);
void runStateMachine(void);

StateHandler currentState = redStateHandler;

int main(void)
 {
    config_drivers();
    config_bsp();

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

void runStateHandler(void)
{

}

void setNextState(StateHandler nextState)
{

}

void yellowStateHandler(void)
{
    printf("Yellow Light: prepare to stop\n");

    // transition to red after delay
    setNextState(redStateHandler);
}

void greenStateHandler(void)
{
    printf("Green light: Vehicle can proced!\n");

    // transition to yellow after delay
    setNextState(yellowStateHandler);
}

void redStateHandler(void)
{
    printf("Red Light: stop vehicle\n");

    // Transition to green after delay
    setNextState(greenStateHandler);
}