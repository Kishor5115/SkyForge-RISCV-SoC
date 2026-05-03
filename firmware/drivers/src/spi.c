#include "spi.h"

void spi_init(uint16_t div) {
    mmio_write(SPI_BASE + SPI_SCKDIV, div);
    mmio_write(SPI_BASE + SPI_CSDEF, 0xF); // CS idle high
    mmio_write(SPI_BASE + SPI_CSMODE, 0);  // Auto CS
    mmio_write(SPI_BASE + SPI_FMT, 0x00080008u); // 8-bit, MSB
    mmio_write(SPI_BASE + SPI_CTRL, 1);    // Enable
}

void spi_set_cs(uint32_t id) {
    mmio_write(SPI_BASE + SPI_CSID, id);
}

uint32_t spi_transfer(uint32_t data) {
    mmio_write(SPI_BASE + SPI_TXDATA, data);
    uint32_t rx;
    do {
        rx = mmio_read(SPI_BASE + SPI_RXDATA);
    } while (rx & (1u << 31)); // Wait for valid
    return rx & 0xFF;
}
