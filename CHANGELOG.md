# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

---

## [Unreleased]

### Added
- **Interactive FreeRTOS+CLI shell over UART** (`firmware/cli/`): commands
  `help`, `ver`, `status`, `memread <addr>`, `gpio <hex>`
- Interactive UART bridge in the Verilator harness (`sim/main.cpp`): host
  stdin → `uart_rx`, `uart_tx` → stdout, with non-blocking I/O and raw-mode
  terminal; `SIM_QUIET=1` for a clean console
- `rtl/core/picorv32_pcpi.sv`: RV32M PCPI multiply/divide co-processor modules
- `docs/FREERTOS_CLI_INTEGRATION.md`: integration report
- Full UVM-1.2 verification environment for APB peripheral subsystem
- FreeRTOS 10.x port for PicoRV32 (context switch, CSR init, timer tick)
- OpenLane ASIC flow targeting SkyWater sky130B PDK at 50 MHz
- OpenRAM-generated 4 KB SRAM macro with Liberty and LEF views
- RISC-V Debug Module 0.13 with JTAG tap and Remote-Bitbang support
- Verilator simulation harness with OpenOCD/GDB integration
- Icarus Verilog unit testbenches for all APB peripherals
- AXI4-Lite 2-master interconnect (CPU + Debug System Bus Access)
- APB peripherals: UART, GPIO (32-bit), SPI master, timer

### Changed
- SRAM scaled from 16 KB to 32 KB (linker, `sram_axi.sv`, interconnect decode,
  `soc_core.sv`) to host the CLI and a larger FreeRTOS heap (12 KB)
- FreeRTOS heap raised from 6 KB to 12 KB

### Fixed
- **Enabled the RV32M extension in hardware** (`ENABLE_MUL`/`ENABLE_DIV` in
  `soc_core.sv`): the core was instantiated without M despite the RV32IM
  firmware/branding, so runtime multiply/divide (e.g. CLI number formatting)
  produced garbage
- Rewrote `scripts/verilog_hex_to_memh.py` to correctly parse objcopy
  `--verilog-data-width=4` word-addressed output (previously produced an empty
  SRAM image, leaving the CPU executing zeros)

---

## [0.1.0] — 2026-06-04

### Added
- Initial open-source release
- PicoRV32 (RV32IM) CPU with AXI4-Lite master interface
- 16 KB SRAM and 256 B Boot ROM
- Top-level `soc_top.sv` integrating all subsystems
- `firmware/` with FreeRTOS demo, peripheral drivers, and linker scripts
- `sim/` Verilator harness and `tb/` Icarus testbenches
- `uvm/` verification environment
- `openlane/` and `flow/` ASIC implementation flow
- `openram/` SRAM macro generation scripts
- MIT License
