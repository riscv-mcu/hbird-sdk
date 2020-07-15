// See LICENSE for license details.
#include <stdio.h>
#include "hbird_sdk_hal.h"

#define BTN1_GPIO_OFS           30
#define BTN2_GPIO_OFS           31
#define PLIC_BTN1_INT           (8+BTN1_GPIO_OFS)
#define PLIC_BTN2_INT           (8+BTN2_GPIO_OFS)

// plic btn1 interrupt handler
void plic_btn1_handler(void)
{
    printf("Enter Button 1 interrupt\n");
    gpio_clear_interrupt(GPIO, SOC_BUTTON_1_GPIO_OFS, GPIO_INT_RISE);
    gpio_toggle(GPIO, SOC_LED_BLUE_GPIO_MASK);
}

// plic btn2 interrupt handler
void plic_btn2_handler(void)
{
    printf("Enter Button 2 interrupt\n");
    gpio_clear_interrupt(GPIO, SOC_BUTTON_2_GPIO_OFS, GPIO_INT_RISE);
    gpio_toggle(GPIO, SOC_LED_GREEN_GPIO_MASK);
}

void board_gpio_init(void)
{
    gpio_enable_input(GPIO, SOC_BUTTON_GPIO_MASK);
    gpio_set_pue(GPIO, SOC_BUTTON_GPIO_MASK, GPIO_BIT_ALL_ONE);

    gpio_enable_output(GPIO, SOC_LED_GPIO_MASK);
    gpio_write(GPIO, SOC_LED_GPIO_MASK, GPIO_BIT_ALL_ZERO);
    // Initialize the button as rising interrupt enabled
    gpio_enable_interrupt(GPIO, SOC_BUTTON_GPIO_MASK, GPIO_INT_RISE);
}

int main(int argc, char **argv)
{
    int32_t returnCode;

    board_gpio_init();

    // inital plic int0 interrupt
    returnCode = PLIC_Register_IRQ(PLIC_BTN1_INT, 1, plic_btn1_handler);

    // inital plic int1 interrupt
    returnCode = PLIC_Register_IRQ(PLIC_BTN2_INT, 2, plic_btn2_handler);

    // Enable interrupts in general.
    __enable_irq();

    // Wait button 1 and button 2 pressed to trigger interrupt
    while (1);
    return 0;
}
