#ifndef SPI_H
#define SPI_H

#include "common.h"

/* SPI Register Offsets */
#define SPI_SCKDIV     0x00u
#define SPI_CSID       0x08u
#define SPI_CSDEF      0x0Cu
#define SPI_CSMODE     0x10u
#define SPI_FMT        0x14u
#define SPI_TXDATA     0x18u
#define SPI_RXDATA     0x1Cu
#define SPI_CTRL       0x34u

void spi_init(uint16_t div);
void spi_set_cs(uint32_t id);
uint32_t spi_transfer(uint32_t data);

#endif /* SPI_H */
