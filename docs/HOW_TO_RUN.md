# HOW TO RUN — PicoRV32 SoC Simulation + Debug

## Prerequisites

| Tool | Minimum Version | Install |
|---|---|---|
| Verilator | 4.228+ | `sudo apt install verilator` |
| riscv32-unknown-elf-gcc | 12+ | See [riscv-gnu-toolchain](https://github.com/riscv-collab/riscv-gnu-toolchain) |
| OpenOCD | 0.12+ (RISC-V) | `sudo apt install openocd` or build from [riscv-openocd](https://github.com/riscv-collab/riscv-openocd) |
| GDB | riscv32-unknown-elf-gdb | Ships with the GNU toolchain above |

## 1 — Build Firmware

```bash
cd ~/riscv-soc/firmware
make clean && make
# Produces: firmware.elf, firmware.hex
```

## 2 — Build the Verilator Simulation

```bash
cd ~/riscv-soc/sim
make clean && make sim
```

## 3 — Launch the Simulation

Open **Terminal 1**:

```bash
cd ~/riscv-soc/sim
make run
```

You should see:

```
[RBB] Listening on localhost:9824
[SIM] Reset for 10 cycles ...
[SIM] Reset released. Running ...
```

Leave this running.

## 4 — Connect OpenOCD

Open **Terminal 2**:

```bash
cd ~/riscv-soc/openocd
openocd -f openocd.cfg
```

Expected output:

```
Info : Listening on port 3333 for gdb connections
Info : JTAG tap: picorv32.cpu tap/device found: 0x10005001
```

Leave this running.

## 5 — Load & Debug with GDB

Open **Terminal 3**:

```bash
cd ~/riscv-soc/firmware
riscv32-unknown-elf-gdb firmware.elf
```

Inside GDB:

```gdb
(gdb) target extended-remote :3333
(gdb) load
(gdb) break main
(gdb) continue

# Optional: break inside a running FreeRTOS task
(gdb) break vTaskA
(gdb) continue
```

## 6 — Clean Up

```bash
make -C ~/riscv-soc/sim clean
make -C ~/riscv-soc/firmware clean
```

## Memory Map Reference

| Region | Start | End | Size |
|---|---|---|---|
| Boot ROM | `0x00000000` | `0x000000FF` | 256 B |
| SRAM | `0x00010000` | `0x00013FFF` | 16 KB |
| APB Timer | `0x20001000` | `0x20001FFF` | — |
| GPIO | `0x20000000` | `0x20000FFF` | — |

## IRQ Map

| IRQ | Source | Handler |
|---|---|---|
| IRQ[3] | APB Timer (1 ms tick) | `xPortSysTickHandler()` in `start.S` → `main.c` |

## Troubleshooting

- **OpenOCD can't connect**: Ensure the simulation is running first (Terminal 1) and port 9824 is free.
- **GDB load fails**: Verify `firmware.elf` was built with the correct linker script (SRAM at `0x00010000`).
- **Simulation hangs**: Check that the IRQ wrapper in `start.S` properly clears the timer interrupt via `TIMER_INTCLR`.
