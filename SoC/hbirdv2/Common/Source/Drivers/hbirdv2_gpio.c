#include "hbirdv2.h"
#include "hbirdv2_gpio.h"

int32_t gpio_iof_config(GPIO_TypeDef *gpio, uint32_t mask)
{
    if (__RARELY(gpio == NULL)) {
        return -1;
    }
    gpio->IOFCFG |= mask;

    return 0;
}


int32_t gpio_enable_output(GPIO_TypeDef *gpio, uint32_t mask)
{
    if (__RARELY(gpio == NULL)) {
        return -1;
    }
    gpio->PADDIR |= mask;
    return 0;
}

int32_t gpio_enable_input(GPIO_TypeDef *gpio, uint32_t mask)
{
    if (__RARELY(gpio == NULL)) {
        return -1;
    }
    gpio->PADDIR &= ~mask;
    return 0;
}

int32_t gpio_write(GPIO_TypeDef *gpio, uint32_t mask, uint32_t value)
{
    if (__RARELY(gpio == NULL)) {
        return -1;
    }
    // If value != 0, mean set gpio pin high, otherwise set pin low
    if (value) {
        gpio->PADOUT |= (mask);
    } else {
        gpio->PADOUT &= ~(mask);
    }
    return 0;
}

int32_t gpio_toggle(GPIO_TypeDef *gpio, uint32_t mask)
{
    if (__RARELY(gpio == NULL)) {
        return -1;
    }
    gpio->PADOUT = (mask ^ gpio->PADOUT);
    return 0;
}


int32_t gpio_read(GPIO_TypeDef *gpio, uint32_t mask)
{
    if (__RARELY(gpio == NULL)) {
        return -1;
    }
    return gpio->PADIN & mask;
}


int32_t gpio_enable_interrupt(GPIO_TypeDef *gpio, uint32_t mask, GPIO_INT_TYPE type)
{
    if (__RARELY(gpio == NULL)) {
        return -1;
    }

    gpio->INTEN |= mask;

    switch (type) {
        case GPIO_INT_RISE:
            gpio->INTTYPE0 &= ~(mask);
            gpio->INTTYPE1 |= mask;
            break;
        case GPIO_INT_FALL:
            gpio->INTTYPE0 |= mask;
            gpio->INTTYPE1 |= mask;
            break;
        case GPIO_INT_HIGH:
            gpio->INTTYPE0 &= ~(mask);
            gpio->INTTYPE1 &= ~(mask);
            break;
        case GPIO_INT_LOW:
            gpio->INTTYPE0 |= mask;
            gpio->INTTYPE1 &= ~(mask);
            break;
        default:
            break;
    }
    return 0;
}

int32_t gpio_disable_interrupt(GPIO_TypeDef *gpio, uint32_t mask)
{
    if (__RARELY(gpio == NULL)) {
        return -1;
    }
    
    gpio->INTEN &= ~mask;

    return 0;
}

int32_t gpio_clear_interrupt(GPIO_TypeDef *gpio)
{
    if (__RARELY(gpio == NULL)) {
        return -1;
    }
     

    return gpio->INTSTATUS;
}

