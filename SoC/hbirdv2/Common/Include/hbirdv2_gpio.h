// See LICENSE for license details.
#ifndef _HBIRDV2_GPIO_H
#define _HBIRDV2_GPIO_H

#ifdef __cplusplus
 extern "C" {
#endif

typedef enum gpio_int_type {
    GPIO_INT_RISE = 0,
    GPIO_INT_FALL = 1,
    GPIO_INT_HIGH = 2,
    GPIO_INT_LOW = 3
} GPIO_INT_TYPE;

int32_t gpio_iof_config(GPIO_TypeDef *gpio, uint32_t mask);
int32_t gpio_enable_output(GPIO_TypeDef *gpio, uint32_t mask);
int32_t gpio_enable_input(GPIO_TypeDef *gpio, uint32_t mask);
int32_t gpio_write(GPIO_TypeDef *gpio, uint32_t mask, uint32_t value);
int32_t gpio_toggle(GPIO_TypeDef *gpio, uint32_t mask);
int32_t gpio_read(GPIO_TypeDef *gpio, uint32_t mask);
int32_t gpio_enable_interrupt(GPIO_TypeDef *gpio, uint32_t mask, GPIO_INT_TYPE type);
int32_t gpio_disable_interrupt(GPIO_TypeDef *gpio, uint32_t mask);
int32_t gpio_clear_interrupt(GPIO_TypeDef *gpio);

#ifdef __cplusplus
}
#endif
#endif /* _HBIRDV2_GPIO_H */
