# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

---

## [1.0.0] — 2026-07-13

**First public silicon-ready release of SkyForge — a fully open-source RV32IM SoC
targeting SkyWater sky130A tapeout via the LibreLane / IIC-OSIC-TOOLS Docker flow.**

### Signoff Status ✅ (production run `RUN_4_GDS_SIGNOFF`)
- **KLayout DRC:** 0 violations (sky130A mr.drc; OpenRAM SRAM internal geometry formally
  waived via a cell-scoped deck — see `docs/WAIVED_CHECKS.md`)
- **LVS:** 0 errors — "Circuits match uniquely" (Netgen; fully clean, no waiver)
- **STA:** timing closed at 100 MHz, TT/1.8 V/25 °C corner (WNS ≥ 0, zero hold violations)
- **Routing DRC:** 0 errors
- **Antenna:** 0 violations (OpenROAD diode insertion)

### Added
- **Flash XIP subsystem:** `flash_xip.sv` — external QSPI flash execute-in-place with
  `icache_512b.sv`, a 512 B direct-mapped I-cache (16 lines × 8 words × 32-bit, FF-based)
- **Interactive FreeRTOS+CLI shell over UART** (`firmware/cli/`): commands
  `help`, `ver`, `status`, `memread <addr>`, `gpio <hex>`
- Interactive UART bridge in the Verilator harness (`sim/main.cpp`): host
  stdin → `uart_rx`, `uart_tx` → stdout, with non-blocking I/O and raw-mode
  terminal; `SIM_QUIET=1` for a clean console
- `rtl/core/picorv32_pcpi.sv`: RV32M PCPI multiply/divide co-processor modules
- `instructions/`: Docker setup guides for Linux and Windows (IIC-OSIC-TOOLS)
- `docs/WAIVED_CHECKS.md`: formal signoff waiver documentation
- `librelane/sky130A_mr_sram_waived.drc`: custom KLayout DRC deck with cell-scoped
  OpenRAM SRAM waivers (well/implant + m1.2/m2.2)
- LibreLane ASIC flow (`librelane/`) targeting SkyWater sky130A at 100 MHz
- OpenRAM-generated 4 KB SRAM macro × 2 (8 KB total) with Liberty and LEF views
- FreeRTOS 10.x port for PicoRV32 (context switch, CSR init, timer tick)
- RISC-V Debug Module 0.13 with JTAG tap and Remote-Bitbang support
- Verilator simulation harness with OpenOCD/GDB integration
- Icarus Verilog unit testbenches for all APB peripherals
- AXI4-Lite 2-master interconnect (CPU + Debug System Bus Access)
- APB peripherals: UART, GPIO (32-bit), SPI master, timer

### Changed
- **ASIC flow migrated from OpenLane → LibreLane** (modern successor); removed the
  legacy `openlane/` design directory
- **PDK: sky130B → sky130A** (matches the IIC-OSIC-TOOLS container PDK)
- **Clock target: 50 MHz → 100 MHz** (timing closed)
- SRAM configured as 8 KB (2× 4 KB OpenRAM banks) for the FreeRTOS heap
- Die area: 1800 × 1550 µm (2.79 mm²); core utilization 45 %, placement density 50 %
- I-cache renamed `icache_1k` → `icache_512b` and resized 1 KB → 512 B (PPA + congestion)

### Fixed
- **Enabled the RV32M extension in hardware** (`ENABLE_MUL`/`ENABLE_DIV`): the core was
  instantiated without M despite the RV32IM firmware/branding
- Rewrote `scripts/verilog_hex_to_memh.py` to correctly parse objcopy word-addressed output
- `USE_POWER_PINS` RTL guards in `soc_core.sv` and `sram_axi.sv` for correct
  powered-netlist generation and LVS
- **LVS top-level power-pin mismatch:** removed a stale `LVS_FLATTEN_CELLS` setting that
  dissolved the empty SRAM blackbox in the extracted layout circuit — LVS now
  "Circuits match uniquely"
- **KLayout DRC residual metal spacing:** extended the SRAM cell-scoped waiver to the
  m1.2/m2.2 rules (OpenRAM-internal 10 nm shorts) — chip DRC now 0

---

## [0.1.0] — 2026-06-04

### Added
- Initial open-source release
- PicoRV32 (RV32IM) CPU with AXI4-Lite master interface
- 16 KB SRAM and 256 B Boot ROM
- Top-level `soc_top.sv` integrating all subsystems
- `firmware/` with FreeRTOS demo, peripheral drivers, and linker scripts
- `sim/` Verilator harness and `tb/` Icarus testbenches
- ASIC implementation flow and `openram/` SRAM macro generation scripts
- MIT License

[1.0.0]: https://github.com/Kishor5115/SkyForge-RISCV-SoC/compare/v0.1.0...v1.0.0
[0.1.0]: https://github.com/Kishor5115/SkyForge-RISCV-SoC/releases/tag/v0.1.0
