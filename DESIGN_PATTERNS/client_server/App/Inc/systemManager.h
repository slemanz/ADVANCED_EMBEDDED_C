#ifndef INC_SYSTEMMANAGER_H_
#define INC_SYSTEMMANAGER_H_

#include "ECG_Module.h"
#include "TMDQueue.h"
#include "histogramDisplay.h"
#include "ECGPkg.h"

typedef struct systemManager systemManager;

struct systemManager
{
    struct ECG_Module itsECG_Module;
    struct histogramDisplay itsHistogramDisplay;
    struct TMDQueue itsTMDQueue;
};

systemManager *systemManager_create(void);
void systemManager_init(systemManager *const me);
struct histogramDisplay *systemManager_getItsHistogramDisplay(systemManager *const me);
struct TMDQueue *systemManager_getItsTMDQueue(systemManager *const me);
void systemManager_destroy(systemManager *const me);

#endif /* INC_SYSTEMMANAGER_H_ */