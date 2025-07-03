#ifndef INC_TMDQUEUE_H_
#define INC_TMDQUEUE_H_

#include "ECGPkg.h"
#include "timeMarkedData.h"

typedef struct TMDQueue TMDQueue;

struct TDMQueue{
    uint32_t head;
    uint32_t size_t;

    timeMarkedData buffer[QUEUE_SIZE];
};

TMDQueue *TMDQueue_create(TMDQueue *const me);

void TMDQueue_init(TMDQueue *const me);
void TMDQueue_insert(TMDQueue *const me, const timeMarkedData tmd);
uint8_t TMDQueue_isEmpty(TMDQueue *const me);
timeMarkedData TMDQueue_remove(TMDQueue *const me, uint32_t index);
uint32_t TMDQueue_getBuffer(TMDQueue *const me);

void TMDQueue_cleanUp(TMDQueue *const me);
void TMDQueue_destroy(TMDQueue *const me);

#endif /* INC_TMDQUEUE_H_ */