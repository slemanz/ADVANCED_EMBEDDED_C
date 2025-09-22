#include <stdio.h>
#include "config.h"
#include "driver_systick.h"
#include "driver_gpio.h"

/* Bit Masks for GPIO Configuration */
#define GPIO_MODE_MASK          0x03    // 2 bits for gpio mode (0-3)
#define GPIO_STATE_MASK         0x04    // 1 bit for gpio speed (ON/OFF)
#define GPIO_SPEED_MASK         0x38    // 3 bits for GPIO speed (0-7)

/* GPIO Modes */
#define GPIO_MODE_INPUT         0
#define GPIO_MODE_OUTPUT        1

/* GPIO State */
#define GPIO_OFF                0
#define GPIO_ON                 1

/* GPIO Speed */
#define GPIO_SPEED_LOW          0
#define GPIO_SPEED_MEDIUM       1
#define GPIO_SPEED_HIGH         2

/* LED Configuration (Assuming LED is connected to pin PC13) */
#define LED_PORT                GPIOA
#define LED_PIN                 5


/**
 * @brief  Packs GPIO configuration settings into a single byte.
 * @param  mode: GPIO mode (0-3)
 * @param  state: GPIO state (ON=1, OFF=0)
 * @param  speed: GPIO speed (0-7)
 * @retval Packed 8-bit data representing GPIO settings
 */
uint8_t pack_gpio_settings(uint8_t mode, uint8_t state, uint8_t speed)
{
    return ((mode & 0x03) | ((state & 0x01) << 2) | ((speed & 0x07) << 3));
}


/**
 * @brief  Unpacks GPIO settings from a packed byte.
 * @param  data: Packed GPIO configuration byte
 */
void unpack_gpio_settings(uint8_t data, uint8_t *mode, uint8_t *state, uint8_t *speed)
{
    *mode = (data & GPIO_MODE_MASK);
    *state = (data & GPIO_STATE_MASK) >> 2;
    *speed = (data & GPIO_SPEED_MASK) >> 3;
}


/**
 * @brief  Configures the LED based on bit-packed GPIO settings.
 * @param  packed_data: Packed GPIO settings
 */
void configure_led(uint8_t packed_data)
{
    uint8_t mode, state, speed;
    unpack_gpio_settings(packed_data, &mode, &state, &speed);

    /* Enable GPIO Clock for port C */
    GPIOC_PCLK_EN();

    /* Configure GPIO Mode */
    if(mode == GPIO_MODE_OUTPUT)
    {
        GPIOC->MODER &= ~(3 << (LED_PIN * 2)); // Clear mode bits
        GPIOC->MODER |=  (1 << (LED_PIN * 2)); // Set as output
        printf("LED configured as OUTPUT.\n");
    }else
    {
        GPIOA->MODER &= ~(3 << (LED_PIN * 2)); // Set as input (default)
        printf("LED configured as INPUT.\n");
    }

    /* Configure GPIO Speed */
    GPIOA->OSPEEDR &= ~(3 << (LED_PIN * 2));   // Clear speed bits
    GPIOA->OSPEEDR |= (speed << (LED_PIN * 2)); // Set speed
    printf("LED speed set to level %u.\n", speed);

    /* Set LED State */
    if((state == GPIO_ON) && (mode == GPIO_MODE_OUTPUT))
    {
        GPIOA->ODR |= (1 << LED_PIN);
        printf("LED TURNED ON.\n");
    }else if(mode == GPIO_MODE_OUTPUT)
    {
        GPIOA->ODR &= ~(1 << LED_PIN);
        printf("LED TURNED OFF.\n");
    }
}


/**
 * @brief  Toggles the LED state directly without reconfiguring other GPIO settings.
 * @param  packed_data: Packed GPIO settings
 * @retval Updated packed data with toggled LED state
 */
uint8_t toggle_led(uint8_t packed_data)
{
}


int main(void)
 {
    config_drivers();
    //config_bsp();
    printf("\n");

    /* Pack GPIO Settings for LED (MODE: Output=1, State: ON=1, Speed: Medium=1)*/
    uint8_t led_settings = pack_gpio_settings(GPIO_MODE_OUTPUT, GPIO_ON, GPIO_SPEED_MEDIUM);

    while (1)
    {   
    }
}