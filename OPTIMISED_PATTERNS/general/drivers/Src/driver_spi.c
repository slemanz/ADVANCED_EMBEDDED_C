#include "driver_spi.h"

void spi_init(void)
{
    /* Config PA5,PA6,PA7*/
    GPIO_Handle_t spiPins;
    spiPins.GPIO_PinConfig.GPIO_PinAltFunMode = GPIO_MODE_ALTFN;
    spiPins.GPIO_PinConfig.GPIO_PinMode = GPIO_PIN_ALTFN_5;
    spiPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    spiPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

    spiPins.pGPIOx = GPIOA;
    spiPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
    GPIO_Init(&spiPins);

    spiPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
    GPIO_Init(&spiPins);

    spiPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_7;
    GPIO_Init(&spiPins);
}