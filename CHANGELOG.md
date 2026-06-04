# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

---

## [Unreleased]

### Added
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
- N/A

### Fixed
- N/A

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
