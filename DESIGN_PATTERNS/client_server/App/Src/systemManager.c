#include "systemManager.h"
#include <stdlib.h>
#include <stdio.h>

systemManager *systemManager_create(void)
{
    systemManager *me = (systemManager *)malloc(sizeof(systemManager));
    if(me != NULL)
    {
        systemManager_init(me);
    }

    return me;
}

void systemManager_init(systemManager *const me)
{
    ECG_Module_init(&(me->itsECG_Module));
    histogramDisplay_init(&(me->itsHistogramDisplay));
    TMDQueue_init(&(me->itsTMDQueue));
    ECG_Module_setItsTMDQueue(&(me->itsECG_Module), &(me->itsTMDQueue));
    histogramDisplay_setItsTMDQueue(&(me->itsHistogramDisplay), &(me->itsTMDQueue));
}

struct histogramDisplay *systemManager_getItsHistogramDisplay(systemManager *const me)
{
    return (struct histogramDisplay *)&(me->itsHistogramDisplay);
}

struct TMDQueue *systemManager_getItsTMDQueue(systemManager *const me)
{
    return (struct TMDQueue *)&(me->itsTMDQueue);
}

void systemManager_destroy(systemManager *const me)
{
    free(me);
}