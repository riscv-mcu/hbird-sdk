// See LICENSE for license details.

#ifndef _HBIRDV2_SPI_H
#define _HBIRDV2_SPI_H

#ifdef __cplusplus
 extern "C" {
#endif

#define SPI_CMD_RD      0
#define SPI_CMD_WR      1
#define SPI_CMD_QRD     2
#define SPI_CMD_QWR     3
#define SPI_CMD_SWRST   4

#define SPI_CSN0        0
#define SPI_CSN1        1
#define SPI_CSN2        2
#define SPI_CSN3        3

int32_t spi_setup_cmd_addr(SPI_TypeDef *spi, int cmd, int cmdlen, int addr, int addrlen);
int32_t spi_setup_dummy(SPI_TypeDef *spi, int dummy_rd, int dummy_wr);
int32_t spi_setup_clk(SPI_TypeDef *spi, int clkdiv);
int32_t spi_set_datalen(SPI_TypeDef *spi, int datalen);
int32_t spi_start_transaction(SPI_TypeDef *spi, int trans_type, int csnum);
int32_t spi_get_status(SPI_TypeDef *spi);
int32_t spi_write_fifo(SPI_TypeDef *spi, int *data, int datalen);
int32_t spi_read_fifo(SPI_TypeDef *spi, int *data, int datalen);
int32_t spi_enable_interrupt(SPI_TypeDef *spi);
int32_t spi_disable_interrupt(SPI_TypeDef *spi);
int32_t spi_get_int_status(SPI_TypeDef *spi);
int32_t spi_set_tx_th(SPI_TypeDef *spi, uint8_t th);
int32_t spi_set_rx_th(SPI_TypeDef *spi, uint8_t th);

#ifdef __cplusplus
}
#endif
#endif /* _HBIRDV2_SPI_H */
