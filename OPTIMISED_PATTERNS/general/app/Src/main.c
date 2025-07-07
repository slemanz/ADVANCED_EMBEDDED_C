#include "stm32f411xx.h"
#include <stdio.h>

uint64_t ticks = 0;

// Define led
#define LED_PORT        GPIOC
#define LED_PIN         GPIO_PIN_NO_13

uint64_t get_ticks(void)
{
    return ticks;
}

void SysTick_Handler(void)
{
    ticks++;
}

// printf retarget
extern int __io_putchar(int ch)
{
    uart2_write_byte((uint8_t)ch);
    return ch;

}

void gpio_setup(void)
{
    // Set GPIOA pin 3 as output
    GPIO_Handle_t GpioLed;
	GpioLed.pGPIOx = LED_PORT;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = LED_PIN;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
	GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

    GPIO_Init(&GpioLed);
    GPIO_WriteToOutputPin(LED_PORT, LED_PIN, GPIO_PIN_SET);
}


int main(void)
 {
    fpu_enable();
    gpio_setup();
    uart2_init();
    systick_init(1000);

    uint64_t start_time = get_ticks();
    printf("Hello world\n\r");

    float n1 = 10.0;
    float n2 = 7.0;
    float result = n1/n2;
    printf("%.2f/%.2f = %.5f\n", n1, n2, result);

    while (1)
    {   
        // blinky
        if((get_ticks() - start_time) >= 500)
        {
            GPIO_ToggleOutputPin(LED_PORT, LED_PIN);
            start_time = get_ticks();
        }
    }
}