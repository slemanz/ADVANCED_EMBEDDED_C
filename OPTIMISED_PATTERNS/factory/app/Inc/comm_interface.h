#ifndef INC_COMM_INTERFACE_H_
#define INC_COMM_INTERFACE_H_

#include <stdint.h>
#include <stddef.h>

typedef enum
{
    PROTOCOL_UART,
    PROTOCOL_I2C,
    PROTOCOL_SPI
}CommProtocol_e;

typedef struct
{
    void (*init)(void);
    void (*send)(uint8_t *data, uint32_t len);
    void (*receive)(uint8_t *buffer, uint32_t len);
    void (*deinit)(void);
}CommProtocol_t;

#endif /* INC_COMM_INTERFACE_H_ */