#ifndef INC_ACTUATOR_H_
#define INC_ACTUATOR_H_

// Define the actuator colleague object

#include "mediator.h"

typedef struct
{
    Mediator_t *mediator;
    int sensorValue;
}Actuator_t;

#endif /* INC_ACTUATOR_H_ */