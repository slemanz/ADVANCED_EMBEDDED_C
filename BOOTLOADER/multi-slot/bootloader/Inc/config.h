#ifndef INC_CONFIG_H_
#define INC_CONFIG_H_

#include "stdint.h"

#define APPLICATION_ADDRESS         0x08008000
#define MSP_VERIFY_MASK			    0x2FFE0000
#define EMPTY_MEM					0xFFFFFFFF

#define LED_PORT        GPIOC
#define LED_PIN         GPIO_PIN_NO_13

#define MEM_CHECKK_V2

void config_drivers(void);
void config_bsp(void);

void jmp_to_default_app(void);

#endif /* INC_CONFIG_H_ */