#ifndef INC_GPIO_PROXY_H_
#define INC_GPIO_PROXY_H_

#include <stdint.h>

// Proxy interface for GPIO
typedef struct{
    void    (*pin_set)(uint32_t pin);
    void    (*pin_clear)(uint32_t pin);
    uint8_t (*pin_read)(uint32_t pin);
}GPIO_Proxy_t;


// Secure GPIO Proxy Structure
typedef struct{
    GPIO_Proxy_t *real_gpio;
    uint32_t pins_allowed; /* Premitted pins */
}SecureGPIO_Proxy_t;

#endif /* INC_GPIO_PROXY_H_ */