# RISC-V SoC (PicoRV32 + FreeRTOS) — Simulation, Debug, and ASIC Flow

A small RV32IM SoC built around the PicoRV32 core, with a minimal FreeRTOS port and a RISC-V Debug Module (0.13-style) that can be driven by OpenOCD + GDB.

This repo includes:
- RTL for the SoC and peripherals (AXI/APB interconnect, SRAM/boot ROM, UART/GPIO/SPI/timer, debug)
- Firmware (FreeRTOS kernel sources + a PicoRV32-specific port + example apps)
- Verilator simulation with Remote Bitbang (for OpenOCD)
- A lightweight ASIC flow (Yosys + OpenSTA + OpenROAD) and an OpenLane wrapper

## Quick start

### 1) Build firmware

```sh
make firmware
# or, explicitly:
make -C firmware APP=firmware APP_SRC=main.c
```

### 2) Run simulation

- Verilator (recommended for OpenOCD/GDB debug):

```sh
make run
```

- Icarus unit/integration tests:

```sh
make sim
# or: make sim_soc
```

### 3) Debug (OpenOCD + gdb-multiarch)

Terminal 1:
```sh
make run
```

Terminal 2:
```sh
make openocd
```

Terminal 3:
```sh
make gdb
```

More detailed instructions: [docs/HOW_TO_RUN.md](docs/HOW_TO_RUN.md)

## ASIC flow

- Minimal scripted flow: [flow/README.md](flow/README.md)
- OpenLane wrapper: [openlane/README.md](openlane/README.md)

Typical run:
```sh
make pd-flow
```

## Project layout (curated)

```text
rtl/            SoC RTL (core, interconnect, memory, peripherals)
  core/         PicoRV32 + AXI adapters
  asic/         Top-level SoC integration for ASIC-style builds
  peripherals/  UART/GPIO/SPI/timer/debug
  memory/       Boot ROM + SRAM + (macro model)
firmware/       FreeRTOS + PicoRV32 port + example apps/tests
sim/            Verilator simulation (remote-bitbang for OpenOCD)
openocd/        OpenOCD + GDB configuration
flow/           Yosys/OpenSTA/OpenROAD scripts
openlane/       OpenLane design wrapper
constraints/    Timing constraints
docs/           How-to-run documentation
```

## License

- Project license: see [LICENSE](LICENSE)
- Third-party components and their licenses: see [THIRD_PARTY_NOTICES.md](THIRD_PARTY_NOTICES.md)
