#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>

/* ═════════════════════════════════════════════════════════════════
 *  SoC Peripheral Base Addresses
 *  (Must match axi_interconnect.sv + apb_interconnect.sv)
 * ═════════════════════════════════════════════════════════════════ */

#define UART_BASE        0x20000000u
#define TIMER_BASE       0x20001000u
#define GPIO_BASE        0x20002000u
#define SPI_BASE         0x20003000u
#define DEBUG_BASE       0x20004000u
#define FLASH_BASE       0x40000000u   /* flash controller registers (0x40000000-0x4000FFFF) */
#define FLASH_XIP_BASE   0x40010000u   /* flash XIP memory window (cached), maps to flash offset 0x10000 */
#define SRAM_BASE        0x00010000u
#define BOOTROM_BASE     0x00000000u

/* ═════════════════════════════════════════════════════════════════
 *  MMIO Helper Macros
 * ═════════════════════════════════════════════════════════════════ */

#define REG32(addr)      (*(volatile uint32_t *)(addr))

static inline void mmio_write(uintptr_t addr, uint32_t value) {
    REG32(addr) = value;
}

static inline uint32_t mmio_read(uintptr_t addr) {
    return REG32(addr);
}

#endif /* COMMON_H */
