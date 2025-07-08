#ifndef INC_DRIVER_SPI_H_
#define INC_DRIVER_SPI_H_

#include "stm32f411xx.h"

/*
    PA5 - SPI1_SCK
    PA6 - SPI1_MISO
    PA7 - SPI1_MOSI
*/

void spi_init(void);

#endif /* INC_DRIVER_SPI_H_ */