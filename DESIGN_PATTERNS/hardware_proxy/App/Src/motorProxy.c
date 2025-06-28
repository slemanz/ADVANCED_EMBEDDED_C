#include "motorProxy.h"
#include <stdio.h>

static uint32_t marshal(const motorData mData);

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

static uint32_t marshal(const motorData mData)
{
    uint32_t deviceCmd = 0;

    if(mData.on_off) deviceCmd |= (1 << 0);

    if(mData.direction == FORWARD)
    {
        deviceCmd |= (2 << 1);
    }else if(mData.direction == REVERSE)
    {
        deviceCmd |= (1 << 1);
    }

    if(mData.speed < 32) deviceCmd |= (mData.speed << 3); // 5 bits

    if(mData.errorStatus)           deviceCmd |= (1 << 8);
    if(mData.noPowerError)          deviceCmd |= (1 << 9);
    if(mData.noTorqueError)         deviceCmd |= (1 << 10);
    if(mData.BITError)              deviceCmd |= (1 << 11);
    if(mData.overTemperatureError)  deviceCmd |= (1 << 12);
    if(mData.reserverdError1)       deviceCmd |= (1 << 13);
    if(mData.reserverdError2)       deviceCmd |= (1 << 14);
    if(mData.unknownError)          deviceCmd |= (1 << 15);

    return deviceCmd;
}