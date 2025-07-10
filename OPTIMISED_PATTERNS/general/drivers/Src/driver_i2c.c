#include "stm32f411xx.h"
#include "driver_i2c.h"
#include "driver_gpio.h"

void i2c1_init(void)
{
    GPIO_Handle_t i2cPins;
    i2cPins.pGPIOx = GPIOB;
    i2cPins.GPIO_PinConfig.GPIO_PinNumber       = GPIO_PIN_NO_8;
    i2cPins.GPIO_PinConfig.GPIO_PinMode         = GPIO_MODE_ALTFN;
    i2cPins.GPIO_PinConfig.GPIO_PinAltFunMode   = GPIO_PIN_ALTFN_4;
    i2cPins.GPIO_PinConfig.GPIO_PinPuPdControl  = GPIO_PIN_PU;
    i2cPins.GPIO_PinConfig.GPIO_PinOPType       = GPIO_OP_TYPE_OD;
    i2cPins.GPIO_PinConfig.GPIO_PinSpeed        = GPIO_SPEED_FAST;
    GPIO_Init(&i2cPins);

    i2cPins.GPIO_PinConfig.GPIO_PinNumber       = GPIO_PIN_NO_9;
    GPIO_Init(&i2cPins);

	I2C1_PCLK_EN(); /*Enable clock access to I2C1*/
	I2C1->CR1 |= (1U<<15); /*Enter reset mode*/
	I2C1->CR1 &=~(1U<<15); /*Come out of reset mode*/

	/*Set the peripheral clock*/
	I2C1->CR2 = (1U<<4); // 16Mhz
	I2C1->CCR =	I2C_100KHZ; /*Set I2C to standard mode, 100kH clock*/
	I2C1->TRISE = SD_MOD_MAX_RISE_TIME; /*Set rise time*/

	I2C1->CR1 |=(1U<<0); /*Enable I2C module*/
}