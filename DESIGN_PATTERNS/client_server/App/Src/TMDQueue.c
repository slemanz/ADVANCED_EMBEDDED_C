#include "TMDQueue.h"
#include <stdlib.h>
#include <stdio.h>

static uint32_t TMDQueue_getNextIndext(TMDQueue *const me, uint32_t index)
{
    return (index + 1)%QUEUE_SIZE;
}

TMDQueue *TMDQueue_create(TMDQueue *const me)
{
    TMDQueue *me = (TMDQueue*)malloc(sizeof(TMDQueue));

    if(me != NULL)
    {
        // init queue
    }

    return me;
}

void TMDQueue_init(TMDQueue *const me)
{
    me->head = 0;
    me->size = 0;
}

void TMDQueue_insert(TMDQueue *const me, const timeMarkedData tmd)
{
    printf("Inserting at: %d TimeInterval #: %d\n", me->head, tmd.timeInterval);
    me->buffer[me->head] = tmd;
    me->head = TMDQueue_getNextIndext(me, me->head);

}

uint8_t TMDQueue_isEmpty(TMDQueue *const me);
timeMarkedData TMDQueue_remove(TMDQueue *const me, uint32_t index);
uint32_t TMDQueue_getBuffer(TMDQueue *const me);

void TMDQueue_cleanUp(TMDQueue *const me);
void TMDQueue_destroy(TMDQueue *const me);