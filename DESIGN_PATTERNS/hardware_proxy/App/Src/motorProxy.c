#include "motorProxy.h"
#include <stdio.h>

motorProxy* motorProxy_create(const char *name)
{
    motorProxy *me = (motorProxy *)malloc(sizeof(motorProxy));
    if(me)
    {
        motorProxy_init(me, name);
    }

    return me;
}

void motorProxy_destroy(motorProxy *const me)
{
    if(me)
    {
        motorProxy_cleanUp(me);
    }

    free(me);
}

void motorProxy_init(motorProxy *const me, const char *name)
{
    me->motorAddr = NULL;
    me->name = name;
}

void motorProxy_cleanUp(motorProxy *const me)
{

}

void motorProxy_enable(motorProxy *const me)
{
    if(!me->motorData)
    {
        return;
    }

    (*(volatile uint32_t *)(*me->motorAddr)) |= 1;

    printf("%s, %d, %p\n", __func__, *me->motorAddr, me->motorAddr);
}

void motorProxy_disable(motorProxy *const me)
{
    if(!me->motorData)
    {
        return;
    }

    (*(volatile uint32_t *)(*me->motorAddr)) &= ~1;

    printf("%s, %d, %p\n", __func__, *me->motorAddr, me->motorAddr);
}