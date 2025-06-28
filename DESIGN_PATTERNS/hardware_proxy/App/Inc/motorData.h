#ifndef INC_MOTOR_DATA_H_
#define INC_MOTOR_DATA_H_

#include "motor.h"

typedef struct motorData motorData;

struct motorData{
    unsigned char on_off;
    Direction_e direction;
    unsigned int speed;
    unsigned char errorStatus;
    unsigned char noPowerError;
    unsigned char noTorqueError;
    unsigned char BITError;
    unsigned char overTemperatureError;
    unsigned char reserverdError1;
    unsigned char reserverdError2;
    unsigned char unknownError;
};

#endif /* INC_MOTOR_DATA_H_ */