//See LICENSE for license details

#ifndef _HBIRDV2_I2C_H
#define _HBIRDV2_I2C_H

#ifdef __cplusplus
 extern "C" {
#endif

/* register offsets */
//all registers are 32 bits width
#define I2C_REG_PRE             0x00
#define I2C_REG_CTR             0x04
#define I2C_REG_RX              0x08
#define I2C_REG_STATUS          0x0C
#define I2C_REG_TX              0x10
#define I2C_REG_CMD             0x14


#define I2C_START               (1 << 7)
#define I2C_STOP                (1 << 6)
#define I2C_READ                (1 << 5)
#define I2C_WRITE               (1 << 4)
#define I2C_CLR_INT             (1 << 0)

#define I2C_START_READ          0xA0
#define I2C_STOP_READ           0x60
#define I2C_START_WRITE         0x90
#define I2C_STOP_WRITE          0x50

#define I2C_CTR_EN              (1 << 7) // enable only
#define I2C_CTR_INTEN           (1 << 6) // interrupt enable only
#define I2C_CTR_EN_INTEN        0xC0     // enable i2c and interrupts

#define I2C_STATUS_RXACK        (1 << 7)
#define I2C_STATUS_BUSY         (1 << 6)
#define I2C_STATUS_AL           (1 << 5)
#define I2C_STATUS_TIP          (1 << 1)
#define I2C_STATUS_IF           (1 << 0)


int32_t i2c_setup(I2C_TypeDef *i2c, int prescaler, int enable); 
int32_t i2c_get_ack(I2C_TypeDef *i2c); 
int32_t i2c_send_data(I2C_TypeDef *i2c, int value); 
int32_t i2c_send_command(I2C_TypeDef *i2c, int value); 
int32_t i2c_get_status(I2C_TypeDef *i2c); 
int32_t i2c_get_data(I2C_TypeDef *i2c); 
int32_t i2c_busy(I2C_TypeDef *i2c); 


#ifdef __cplusplus
}
#endif
#endif /* _HBIRDV2_I2C_H */
