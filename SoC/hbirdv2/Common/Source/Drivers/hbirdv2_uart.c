#include "hbirdv2.h"
#include "hbirdv2_uart.h"

int32_t uart_init(UART_TypeDef *uart, uint32_t baudrate)
{
    if (__RARELY(uart == NULL)) {
        return -1;
    }

    unsigned int uart_div = SystemCoreClock / baudrate - 1;
    uart->LCR = 0x80;
    uart->DLM = (uart_div >> 8) & 0xFF;
    uart->DLL = uart_div        & 0xFF;
    uart->FCR = 0xC6;
    uart->LCR = 0x03;

    return 0;
}

int32_t uart_config_stopbit(UART_TypeDef *uart, UART_STOP_BIT stopbit)
{
    if (__RARELY(uart == NULL)) {
        return -1;
    }

    uart->LCR &= 0xFFFFFFFB;
    uart->LCR |= (stopbit << 2);

    return 0;
}

int32_t uart_enable_paritybit(UART_TypeDef *uart)
{
    if (__RARELY(uart == NULL)) {
        return -1;
    }

    uart->LCR |= 0x8;

    return 0;
}

int32_t uart_disable_paritybit(UART_TypeDef *uart)
{
    if (__RARELY(uart == NULL)) {
        return -1;
    }

    uart->LCR &= 0xFFFFFFF7;

    return 0;
}

int32_t uart_set_parity(UART_TypeDef *uart, UART_PARITY_BIT paritybit)
{
    if (__RARELY(uart == NULL)) {
        return -1;
    }

    uart->LCR &= 0xFFFFFFCF;
    uart->LCR |= (paritybit << 4);

    return 0;
}

int32_t uart_write(UART_TypeDef *uart, uint8_t val)
{
    if (__RARELY(uart == NULL)) {
        return -1;
    }
#ifndef SIMULATION_SPIKE
#ifndef SIMULATION_XLSPIKE
    while ((uart->LSR & 0x20) == 0);
#endif
    uart->THR = val;
#else
    extern void htif_putc(char ch);
    htif_putc(val);
#endif
    return 0;
}

uint8_t uart_read(UART_TypeDef *uart)
{
    uint32_t reg;
    if (__RARELY(uart == NULL)) {
        return -1;
    }
    
    while ((uart->LSR & 0x1) == 0);
    reg = uart->RBR;
    
    return (uint8_t)(reg & 0xFF);
}


int32_t uart_enable_tx_empt_int(UART_TypeDef *uart)
{
    if (__RARELY(uart == NULL)) {
        return -1;
    }

    uart->IER |= 0x2;
    return 0;
}

int32_t uart_disable_tx_empt_int(UART_TypeDef *uart)
{
    if (__RARELY(uart == NULL)) {
        return -1;
    }

    uart->IER &= 0xFFFFFFFD;
    return 0;
}

int32_t uart_set_rx_th(UART_TypeDef *uart, uint8_t th)
{
    if (__RARELY(uart == NULL)) {
        return -1;
    }

    if(th > 3) {
       th = 3;
    }

    uart->FCR &= 0xFFFFFF3F;
    uart->FCR |= (th << 6);
    return 0;
}

int32_t uart_enable_rx_th_int(UART_TypeDef *uart)
{
    if (__RARELY(uart == NULL)) {
        return -1;
    }

    uart->IER |= 0x1;
    return 0;
}

int32_t uart_disable_rx_th_int(UART_TypeDef *uart)
{
    if (__RARELY(uart == NULL)) {
        return -1;
    }

    uart->IER &= 0xFFFFFFFE;
    return 0;
}

int32_t uart_enable_rx_err_int(UART_TypeDef *uart)
{
    if (__RARELY(uart == NULL)) {
        return -1;
    }

    uart->IER |= 0x4;
    return 0;
}

int32_t uart_disable_rx_err_int(UART_TypeDef *uart)
{
    if (__RARELY(uart == NULL)) {
        return -1;
    }

    uart->IER &= 0xFFFFFFFB;
    return 0;
}

int32_t uart_get_int_status(UART_TypeDef *uart)
{

    if (__RARELY(uart == NULL)) {
        return -1;
    }

    return uart->IIR;
}

int32_t uart_get_status(UART_TypeDef *uart)
{

    if (__RARELY(uart == NULL)) {
        return -1;
    }

    return uart->LSR;
}


