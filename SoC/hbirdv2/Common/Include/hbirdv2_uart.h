// See LICENSE for license details.

#ifndef _HBIRDV2_UART_H
#define _HBIRDV2_UART_H

#ifdef __cplusplus
 extern "C" {
#endif

typedef enum uart_stop_bit {
    UART_STOP_BIT_1 = 0,
    UART_STOP_BIT_2 = 1
} UART_STOP_BIT;

int32_t uart_init(UART_TypeDef *uart, uint32_t baudrate);
int32_t uart_config_stopbit(UART_TypeDef *uart, UART_STOP_BIT stopbit);
int32_t uart_write(UART_TypeDef *uart, uint8_t val);
uint8_t uart_read(UART_TypeDef *uart);
int32_t uart_set_tx_watermark(UART_TypeDef *uart, uint32_t watermark);
int32_t uart_enable_txint(UART_TypeDef *uart);
int32_t uart_disable_txint(UART_TypeDef *uart);
int32_t uart_set_rx_watermark(UART_TypeDef *uart, uint32_t watermark);
int32_t uart_enable_rxint(UART_TypeDef *uart);
int32_t uart_disable_rxint(UART_TypeDef *uart);

#ifdef __cplusplus
}
#endif
#endif /* _HBIRDV2_UART_H */
