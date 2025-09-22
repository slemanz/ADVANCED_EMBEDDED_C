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

}


/**
 * @brief  Unpacks GPIO settings from a packed byte.
 * @param  data: Packed GPIO configuration byte
 */
void unpack_gpio_settings(uint8_t data, uint8_t *mode, uint8_t *state, uint8_t *speed)
{

}


/**
 * @brief  Configures the LED based on bit-packed GPIO settings.
 * @param  packed_data: Packed GPIO settings
 */
void configure_led(uint8_t packed_data)
{

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


    while (1)
    {   
    }
}