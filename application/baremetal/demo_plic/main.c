// See LICENSE for license details.
#include <stdio.h>
#include "hbird_sdk_hal.h"

#ifdef SOC_HBIRD
#ifdef BOARD_HBIRD_EVAL
  #define BTN1_GPIO_OFS           30
  #define BTN2_GPIO_OFS           31
  #define PLIC_BTN1_INT           (8+BTN1_GPIO_OFS)
  #define PLIC_BTN2_INT           (8+BTN2_GPIO_OFS)
#endif
#endif


#ifdef SOC_HBIRD
#ifdef BOARD_HBIRD_EVAL
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
#endif
#endif

#ifdef SOC_HBIRDV2
#if (defined BOARD_DDR200T) || (defined BOARD_MCU200T)
// plic btn interrupt handler
void plic_btn_handler(void)
{
    int mask;

    printf("Enter PLIC GPIOA Interrupt\n");
    mask = gpio_clear_interrupt(GPIOA);
    switch (mask) {
        case SOC_BUTTON_U_GPIO_MASK:
            printf("Cause: Button U \n");
            gpio_toggle(GPIOA, SOC_LED_0_GPIO_MASK);
            printf("LED 0 Toggled \n");
            break;
        case SOC_BUTTON_D_GPIO_MASK:
            printf("Cause: Button D \n");
            gpio_toggle(GPIOA, SOC_LED_1_GPIO_MASK);
            printf("LED 1 Toggled \n");
            break;
        case SOC_BUTTON_L_GPIO_MASK:
            printf("Cause: Button L \n");
            gpio_toggle(GPIOA, SOC_LED_2_GPIO_MASK);
            printf("LED 2 Toggled \n");
            break;
        case SOC_BUTTON_R_GPIO_MASK:
            printf("Cause: Button R \n");
            gpio_toggle(GPIOA, SOC_LED_3_GPIO_MASK);
            printf("LED 3 Toggled \n");
            break;
        case SOC_BUTTON_C_GPIO_MASK:
            printf("Cause: Button C \n");
            gpio_toggle(GPIOA, SOC_LED_4_GPIO_MASK);
            printf("LED 4 Toggled \n");
            break;
        default:
            break;
    }
}

#endif
#endif


void board_gpio_init(void)
{

#ifdef SOC_HBIRD
#ifdef BOARD_HBIRD_EVAL
    gpio_enable_input(GPIO, SOC_BUTTON_GPIO_MASK);
    gpio_set_pue(GPIO, SOC_BUTTON_GPIO_MASK, GPIO_BIT_ALL_ONE);

    gpio_enable_output(GPIO, SOC_LED_GPIO_MASK);
    gpio_write(GPIO, SOC_LED_GPIO_MASK, GPIO_BIT_ALL_ZERO);
    // Initialize the button as rising interrupt enabled
    gpio_enable_interrupt(GPIO, SOC_BUTTON_GPIO_MASK, GPIO_INT_RISE);
#endif
#endif

#ifdef SOC_HBIRDV2
#if (defined BOARD_DDR200T) || (defined BOARD_MCU200T)
    gpio_enable_input(GPIOA, SOC_BUTTON_GPIO_MASK);
    gpio_enable_output(GPIOA, SOC_LED_GPIO_MASK);

    gpio_write(GPIOA, SOC_LED_GPIO_MASK, GPIO_BIT_ALL_ZERO);

    // Initialize the button as rising interrupt enabled
    gpio_enable_interrupt(GPIOA, SOC_BUTTON_GPIO_MASK, GPIO_INT_RISE);
#endif
#endif


}

int main(int argc, char **argv)
{
    int32_t returnCode;

    board_gpio_init();

#ifdef SOC_HBIRD
#ifdef BOARD_HBIRD_EVAL
    // inital plic int0 interrupt
    returnCode = PLIC_Register_IRQ(PLIC_BTN1_INT, 1, plic_btn1_handler);
    // inital plic int1 interrupt
    returnCode = PLIC_Register_IRQ(PLIC_BTN2_INT, 2, plic_btn2_handler);
#endif
#endif

#ifdef SOC_HBIRDV2
#if (defined BOARD_DDR200T) || (defined BOARD_MCU200T)
    // inital plic GPIOA interrupt
    returnCode = PLIC_Register_IRQ(PLIC_GPIOA_IRQn, 1, plic_btn_handler);
#endif
#endif

    // Enable interrupts in general.
    __enable_irq();

    printf("Wait for Interrupt \n");
    // Wait button 1 and button 2 pressed to trigger interrupt
    while (1);
    return 0;
}
