# Third-party notices

This repository includes third-party open-source components. Their license terms apply to the corresponding files/directories.

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

## Notes on PDK/macros/tools

- SKY130 PDK and standard cell libraries are not bundled here; you must obtain them separately.
- SRAM views under `openram/build/` are generated artifacts produced with OpenRAM + SKY130; ensure you comply with the licenses of the tool and the PDK used to generate them.
- Tooling (Verilator, Yosys, OpenSTA, OpenROAD, OpenLane, OpenOCD, GCC) is not redistributed by this repo; install them separately.
