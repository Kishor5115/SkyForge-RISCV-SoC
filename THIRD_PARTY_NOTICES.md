# Third-party notices

This repository includes and/or depends on third-party open-source components. Their
license terms apply to the corresponding files/directories.

## PicoRV32 (CPU core)

- Location: `rtl/core/picorv32.sv`, `rtl/core/picorv32_pcpi.sv`
- License: ISC-style permissive license (see the header in the file).
- Upstream: https://github.com/YosysHQ/picorv32
- Note: `rtl/core/picorv32_pcpi.sv` contains the `picorv32_pcpi_mul` and
  `picorv32_pcpi_div` co-processor modules extracted verbatim from the upstream
  `picorv32.v` to enable the RV32M (hardware multiply/divide) extension.

## FreeRTOS Kernel

- Location: `firmware/FreeRTOS-Kernel/`
- License: MIT (SPDX: MIT in file headers)
- Upstream: https://github.com/FreeRTOS/FreeRTOS-Kernel

## FreeRTOS+CLI (command-line interface)

- Location: `firmware/cli/FreeRTOS_CLI.c`, `firmware/cli/FreeRTOS_CLI.h`
- License: MIT (SPDX: MIT in file headers)
- Upstream: https://github.com/FreeRTOS/FreeRTOS
  (`FreeRTOS-Plus/Source/FreeRTOS-Plus-CLI`)

## OpenRAM-generated SRAM macro views

- Location: `openram/build/sky130_sram_4kbyte_1rw_32x1024_8.*` (GDS, LEF, Liberty, SPICE)
- These are generated artifacts produced with the OpenRAM compiler on the SkyWater
  sky130 PDK.
- OpenRAM: BSD 3-Clause — https://github.com/VLSIDA/OpenRAM
- The generated views inherit the license terms of the OpenRAM compiler and the sky130
  PDK used to produce them; ensure you comply with both.

## SkyWater sky130 PDK (not bundled)

- The sky130A PDK and `sky130_fd_sc_hd` standard-cell library are **not** included in this
  repository; you must obtain them separately (e.g. via the IIC-OSIC-TOOLS container or
  open_pdks).
- License: Apache License 2.0 — https://github.com/google/skywater-pdk

## Tooling (not redistributed by this repository)

The following tools are used by the flow but are not bundled here; install them
separately (the project targets the `hpretl/iic-osic-tools:chipathon26` container, which
provides them):

- **LibreLane** (RTL-to-GDS flow orchestrator) — Apache License 2.0 —
  https://github.com/librelane/librelane
- Yosys, OpenROAD, OpenSTA, Magic, Netgen, KLayout, Verilator, Icarus Verilog, OpenOCD,
  the RISC-V GNU toolchain — each under its own license.
