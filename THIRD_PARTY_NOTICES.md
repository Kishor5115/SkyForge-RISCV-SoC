# Third-party notices

This repository includes third-party open-source components. Their license terms apply to the corresponding files/directories.

## PicoRV32 (CPU core)

- Location: `rtl/core/picorv32.sv`
- License: ISC-style permissive license (see the header in the file).

## FreeRTOS Kernel

- Location: `firmware/FreeRTOS-Kernel/`
- License: MIT (SPDX: MIT in file headers)
- Upstream: https://github.com/FreeRTOS/FreeRTOS-Kernel

## Notes on PDK/macros/tools

- SKY130 PDK and standard cell libraries are not bundled here; you must obtain them separately.
- SRAM views under `openram/build/` are generated artifacts produced with OpenRAM + SKY130; ensure you comply with the licenses of the tool and the PDK used to generate them.
- Tooling (Verilator, Yosys, OpenSTA, OpenROAD, OpenLane, OpenOCD, GCC) is not redistributed by this repo; install them separately.
