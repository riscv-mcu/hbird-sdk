#include "hbirdv2.h"
#include "hbirdv2_spi.h"


int32_t spi_setup_cmd_addr(SPI_TypeDef *spi, uint32_t cmd, uint32_t cmdlen, uint32_t addr, uint32_t addrlen) {

    if (__RARELY(spi == NULL)) {
        return -1;
    }

    int cmd_reg;
    cmd_reg = cmd << (32 - cmdlen);

    spi->SPICMD = cmd_reg;
    spi->SPIADR = addr;
    spi->SPILEN = (cmdlen & 0x3F) | ((addrlen << 8) & 0x3F00);

    return 0;
}

int32_t spi_setup_clk(SPI_TypeDef *spi, uint8_t clkdiv) {

    if (__RARELY(spi == NULL)) {
        return -1;
    }

    spi->CLKDIV = clkdiv;
    
    return 0;
}

int32_t spi_setup_dummy(SPI_TypeDef *spi, uint16_t dummy_rd, uint16_t dummy_wr) {

    if (__RARELY(spi == NULL)) {
        return -1;
    }

    spi->SPIDUM = ((dummy_wr << 16) & 0xFFFF0000) | (dummy_rd & 0xFFFF);
    
    return 0;
}

int32_t spi_set_datalen(SPI_TypeDef *spi, uint32_t datalen) {

    if (__RARELY(spi == NULL)) {
        return -1;
    }

    volatile int old_len;
    old_len = spi->SPILEN;
    old_len = ((datalen << 16) & 0xFFFF0000) | (old_len & 0xFFFF);
    spi->SPILEN = old_len;
    
    return 0;
}

int32_t spi_start_transaction(SPI_TypeDef *spi, uint32_t trans_type, uint32_t csnum) {

    if (__RARELY(spi == NULL)) {
        return -1;
    }

    spi->STATUS = ((1 << (csnum + 8)) & 0xF00) | ((1 << trans_type) & 0xFF);

    return 0;
}

int32_t spi_get_status(SPI_TypeDef *spi) {

    if (__RARELY(spi == NULL)) {
        return -1;
    }

    return spi->STATUS;
}

int32_t spi_write_fifo(SPI_TypeDef *spi, uint32_t *data, uint32_t datalen) {

    if (__RARELY(spi == NULL)) {
        return -1;
    }

    volatile int num_words, i;

    num_words = (datalen >> 5) & 0x7FF;

    if ( (datalen & 0x1F) != 0)
        num_words++;

    for (i = 0; i < num_words; i++) {
        while ((((spi->STATUS) >> 24) & 0xFF) >= 8);
        spi->TXFIFO = data[i];
    }

    return 0;
}

int32_t spi_read_fifo(SPI_TypeDef *spi, uint32_t *data, uint32_t datalen) {

    if (__RARELY(spi == NULL)) {
        return -1;
    }    

    volatile int num_words, i;

    num_words = (datalen >> 5) & 0x7FF;

    if ( (datalen & 0x1F) != 0)
        num_words++;

    for (i = 0; i < num_words; i++) {
        while ((((spi->STATUS) >> 16) & 0xFF) == 0);
        data[i] = spi->RXFIFO;
    }
    
    return 0;
}

int32_t spi_enable_interrupt(SPI_TypeDef *spi) {

    if (__RARELY(spi == NULL)) {
        return -1;
    }

    spi->INTCFG |= 0x80000000;
    return 0;
}

int32_t spi_disable_interrupt(SPI_TypeDef *spi) {

    if (__RARELY(spi == NULL)) {
        return -1;
    }

    spi->INTCFG &= 0x7FFFFFFF;
    return 0;
}

int32_t spi_set_tx_th(SPI_TypeDef *spi, uint8_t th) {

    if (__RARELY(spi == NULL)) {
        return -1;
    }

    if(th > 31) {
       th = 31;
    }

    spi->INTCFG &= 0xFFFFFFE0;
    spi->INTCFG |= th;

    return 0;
}

int32_t spi_set_rx_th(SPI_TypeDef *spi, uint8_t th) {

    if (__RARELY(spi == NULL)) {
        return -1;
    }

    if(th > 31) {
       th = 31;
    }

    spi->INTCFG &= 0xFFFFE0FF;
    spi->INTCFG |= (th << 8);

    return 0;
}

int32_t spi_get_int_status(SPI_TypeDef *spi) {

    if (__RARELY(spi == NULL)) {
        return -1;
    }

    return spi->INTSTA;
}
