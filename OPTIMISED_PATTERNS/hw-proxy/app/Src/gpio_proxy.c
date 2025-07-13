#include <stdio.h>
#include "gpio_proxy.h"
#include "stm32f411xx.h"

/*
 * initialize a specific GPIO pin
 */

void secure_gpio_out_init(uint32_t pin)
{
    RCC->AHB1ENR |= (1U << 0); // Enable clock for GPIO 

    // Set output mode
    GPIOA->MODER &= ~(3U << (pin*2));
    GPIOA->MODER |=  (1U << (pin*2));

    GPIOA->BSRR = (1U << (pin + 16)); // ensure pin starts low (Defaul OFF)
}

void secure_gpio_in_init(uint32_t pin)
{
    RCC->AHB1ENR |= (1U << 0); // Enable clock for GPIO 
    GPIOA->MODER &= ~(3U << (pin*2));  // Set input mode
    GPIOA->BSRR = (1U << (pin + 16)); // ensure pin starts low (Defaul OFF)
}


/*
 * Real GPIO Driver Functions
 */

void real_gpio_set_pin(uint32_t pin)
{
    GPIOA->BSRR = (1U << pin);
    printf("Pin %lu is set\n", pin);
}

void real_gpio_clear_pin(uint32_t pin)
{
    GPIOA->BSRR = (1U << (pin + 16));
    printf("Pin %lu is cleared\n", pin);
}

uint8_t real_gpio_read_pin(uint32_t pin)
{
    return (GPIOA->IDR & (1U << pin)) ? 1 : 0; // read gpio state
}

