#include "hbirdv2.h"
#include "hbirdv2_i2c.h"

int32_t i2c_setup(I2C_TypeDef *i2c, int prescaler, int enable) {

    if (__RARELY(i2c == NULL)) {
        return -1;
    }

    i2c->PRE = prescaler;
    i2c->CTR = enable;

    return 0;
}

int32_t i2c_get_ack(I2C_TypeDef *i2c) {

    if (__RARELY(i2c == NULL)) {
        return -1;
    }

    while ((i2c->STATUS & I2C_STATUS_TIP) == 0); // need TIP go to 1
    while ((i2c->STATUS & I2C_STATUS_TIP) != 0); // and then go back to 0
    return !(i2c->STATUS & I2C_STATUS_RXACK); // invert since signal is active low
}

int32_t i2c_send_data(I2C_TypeDef *i2c, int value) {

    if (__RARELY(i2c == NULL)) {
        return -1;
    }

    i2c->TX = value;

    return 0;
}

int32_t i2c_send_command(I2C_TypeDef *i2c, int value) {

    if (__RARELY(i2c == NULL)) {
        return -1;
    }

    i2c->CMD = value;

    return 0;
}

int32_t i2c_get_status(I2C_TypeDef *i2c) {

    if (__RARELY(i2c == NULL)) {
        return -1;
    }

    return i2c->STATUS;
}

int32_t i2c_get_data(I2C_TypeDef *i2c) {

    if (__RARELY(i2c == NULL)) {
        return -1;
    }

    return i2c->RX;
}

int32_t i2c_busy(I2C_TypeDef *i2c) {

    if (__RARELY(i2c == NULL)) {
        return -1;
    }

    return ((i2c->STATUS & I2C_STATUS_BUSY) == I2C_STATUS_BUSY);
}
