// See LICENSE for license details.
#include <stdio.h>
#include "hbird_sdk_soc.h"


#define HIGHER_INTLEVEL         2
#define LOWER_INTLEVEL          1


// plic int0 interrupt handler
void plic_int0_handler(void)
{

}

// plic int1 interrupt handler
void plic_int1_handler(void)
{

}

int main(int argc, char **argv)
{
    int32_t returnCode;

    // inital plic int0 interrupt
    returnCode = PLIC_Register_IRQ(PLIC_INT0_IRQn, 1, plic_int0_handler);

    // inital plic int1 interrupt
    returnCode = PLIC_Register_IRQ(PLIC_INT1_IRQn, 1, plic_int1_handler);

    // Enable interrupts in general.
    __enable_irq();

    // Wait for timer interrupt and software interrupt
    // triggered periodly
    while (1);
    return 0;
}
