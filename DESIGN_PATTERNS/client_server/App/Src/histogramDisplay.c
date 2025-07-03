#include "histogramDisplay.h"
#include "TMDQueue.h"
#include <stdlib.h>
#include <stdio.h>

histogramDisplay *histogramDisplay_create(void)
{
    histogramDisplay *me = (histogramDisplay*)malloc(sizeof(histogramDisplay));

    if(me != NULL)
    {
        histogramDisplay_init(me);
    }

    return me;
}

void histogramDisplay_init(histogramDisplay *const me)
{
    me->index = 0;
    me->itsTMDQueue = NULL;
}

void histogramDisplay_getValue(histogramDisplay *const me)
{
    timeMarkedData tmd;
    tmd = TMDQueue_remove(me->itsTMDQueue, me->index);
    printf("Histogram index is: %ld TimeInterval: %ld DataValue: %ld\n", me->index, tmd.timeInterval, tmd.timeInterval);
    me->index = TMDQueue_getNextIndext(me, me->index);
}

void histogramDisplay_update(histogramDisplay *const me);
void histogramDisplay_setItsTMDQueue(histogramDisplay *const me, struct TMDQueue *pTMDQueue);

void histogramDisplay_destroy(histogramDisplay *const me);