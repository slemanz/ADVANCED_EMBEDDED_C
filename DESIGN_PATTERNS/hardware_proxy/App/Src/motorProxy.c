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

    printf("%s, %ld, %p\n", __func__, *me->motorAddr, me->motorAddr);
}

void motorProxy_disable(motorProxy *const me)
{
    if(!me->motorData)
    {
        return;
    }

    (*(volatile uint32_t *)(*me->motorAddr)) &= ~1;

    printf("%s, %ld, %p\n", __func__, *me->motorAddr, me->motorAddr);
}

void motorProxy_configure(motorProxy *const me, uint32_t length, volatile uint32_t *location, uint32_t *motorData)
{
    me->rotaryArmLength = length;
    me->motorAddr = location;
    me->motorData = motorData;

    printf("%s, %ld, %p\n", __func__, *me->motorAddr, me->motorAddr);
}

Direction_e motorProxy_accessMotorDirection(motorProxy *const me)
{
    return NO_DIRECTION;
}