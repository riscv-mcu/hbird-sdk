#include "hbirdv2.h"
#include "hbirdv2_uart.h"

int32_t uart_init(UART_TypeDef *uart, uint32_t baudrate)
{
    if (__RARELY(uart == NULL)) {
        return -1;
    }

    unsigned int uart_div = SystemCoreClock / baudrate - 1;
    uart->LCR = 0x83;
    uart->DLM = (uart_div >> 8) & 0xFF;
    uart->DLL = uart_div        & 0xFF;
    uart->FCR = 0xA7;
    uart->LCR = 0x03;


    return 0;
}

int32_t uart_config_stopbit(UART_TypeDef *uart, UART_STOP_BIT stopbit)
{
    if (__RARELY(uart == NULL)) {
        return -1;
    }
    return 0;
}

int32_t uart_write(UART_TypeDef *uart, uint8_t val)
{
    if (__RARELY(uart == NULL)) {
        return -1;
    }
#ifndef SIMULATION_XLSPIKE
    while ((uart->LSR & 0x20) == 0);
#endif
    uart->THR = val;
    return 0;
}

uint8_t uart_read(UART_TypeDef *uart)
{
    uint32_t reg;
    if (__RARELY(uart == NULL)) {
        return -1;
    }
    do {
        reg = uart->RBR;
    }
    while ((uart->LSR & 0x1) != 0x1);
    return (uint8_t)(reg & 0xFF);
}

int32_t uart_set_tx_watermark(UART_TypeDef *uart, uint32_t watermark)
{
    if (__RARELY(uart == NULL)) {
        return -1;
    }
    return 0;
}

int32_t uart_enable_txint(UART_TypeDef *uart)
{
    if (__RARELY(uart == NULL)) {
        return -1;
    }
    return 0;
}

int32_t uart_disable_txint(UART_TypeDef *uart)
{
    if (__RARELY(uart == NULL)) {
        return -1;
    }
    return 0;
}

int32_t uart_set_rx_watermark(UART_TypeDef *uart, uint32_t watermark)
{
    if (__RARELY(uart == NULL)) {
        return -1;
    }
    return 0;
}

int32_t uart_enable_rxint(UART_TypeDef *uart)
{
    if (__RARELY(uart == NULL)) {
        return -1;
    }
    return 0;
}

int32_t uart_disable_rxint(UART_TypeDef *uart)
{
    if (__RARELY(uart == NULL)) {
        return -1;
    }
    return 0;
}
