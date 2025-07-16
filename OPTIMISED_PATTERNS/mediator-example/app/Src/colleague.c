#include "colleague.h"
#include "led.h"
#include "button.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void colleagueSendEvent(Colleague_t *colleague, const char *event)
{
    if(colleague && colleague->mediator && colleague->mediator->vtable && colleague->mediator->vtable->notify)
    {
        colleague->mediator->vtable->notify(colleague->mediator, event);
    }
}

/* Light specific behavior */
void lightPerformAction(Colleague_t *colleague, const char *action)
{
    if(strcmp(action, "turn off") == 0)
    {
        printf("Ligth: turning off.\n");
        led_on();
    }else if(strcmp(action, "dim"))
    {
        printf("Light dimming lights.\n");
        led_off();
    }else
    {
        printf("Light: Unknown action '%s'.\n", action);
    }
}

Light_t* light_create(Mediator_t* mediator) {
    Light_t* light = (Light_t*)malloc(sizeof(Light_t));
    if (light) {
        light->base.mediator = mediator;
        light->base.sendEvent = colleagueSendEvent;
        light->base.performAction = lightPerformAction;
    }
    return light;
}

/* Thermostat specific behavior */

/* Security system specific behavior */