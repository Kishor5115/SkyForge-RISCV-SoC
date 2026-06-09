# FreeRTOS+CLI Integration Report — SkyForge PicoRV32 SoC

This document describes the integration of an interactive **FreeRTOS+CLI**
command-line shell over UART into the SkyForge PicoRV32 RISC-V SoC, the memory
scaling and RTL fixes it required, and how to run and verify it.

---

## 1. Summary

The firmware previously demonstrated FreeRTOS booting two GPIO-blink tasks with
no user interaction. It now hosts an **interactive UART shell** built on
FreeRTOS+CLI, with runtime commands for inspecting and controlling the SoC:

| Command | Description |
|---|---|
| `help` | List all registered commands (built into FreeRTOS+CLI) |
| `ver` | Print the SoC/firmware banner |
| `status` | Uptime (ms), task count, and heap usage (free / min-ever) |
| `memread <addr>` | Read a 32-bit word at a hex address |
| `gpio <hex>` | Drive `GPIO_OUT` with a 32-bit value |

The blink tasks (`vTaskA`/`vTaskB`) continue to run concurrently with the shell,
demonstrating preemptive multitasking alongside interactive I/O.

---

## 2. What was added / changed

### Firmware (`firmware/`)
- **`cli/FreeRTOS_CLI.c`, `cli/FreeRTOS_CLI.h`** — the FreeRTOS+CLI library
  (upstream FreeRTOS-Plus, MIT-licensed), dropped in unmodified.
- **`cli/cli_task.c`** — the interactive task: reads a line from the UART,
  runs it through `FreeRTOS_CLIProcessCommand()` (handling the multi-buffer
  output protocol), and echoes results. Registers the five commands above.
- **`cli/cli.h`** — public `cli_start()` entry point.
- **`FreeRTOSConfig.h`** — added `configCOMMAND_INT_MAX_OUTPUT_SIZE` (256 B,
  the shared static CLI output buffer) and raised `configTOTAL_HEAP_SIZE`
  from 6 KB to 12 KB to host the CLI task stack.
- **`main.c`** — calls `uart_init(14)` (≈115200 baud @ 25 MHz) and `cli_start()`
  before `vTaskStartScheduler()`.
- **`Makefile`** — added `-Icli`, the two CLI source files, and `cli` to VPATH.
- **`linker.ld`** — SRAM region grown to 32 KB; stack top moved to `0x00017FFC`.

> Note: the minimal libc (`libc/libc.c`) already provided `snprintf`/`vsnprintf`,
> so no new formatting code was needed.

### RTL (`rtl/`)
- **32 KB SRAM** — the firmware with the CLI + 12 KB heap exceeds 16 KB, so SRAM
  was scaled from 16 KB to 32 KB:
  - `memory/sram_axi.sv`: `ADDR_WIDTH` 14 → 15; `NUM_BANKS` now derived from
    size (8 × 4 KB banks for the synthesis/OpenRAM path).
  - `asic/soc_core.sv`: SRAM instance `ADDR_WIDTH(15)`, address slices widened
    to `[14:0]`, CPU `STACKADDR` → `0x0001_7FFC`.
  - `interconnect/axi_interconnect.sv`: SRAM decode window widened from
    `[0x10000, 0x14000)` to `[0x10000, 0x18000)`.
- **RV32M enabled (hardware multiply/divide)** — the core was instantiated with
  `ENABLE_MUL` / `ENABLE_DIV` defaulting to 0, i.e. **no M-extension**, even
  though the firmware is built `-march=rv32im` and the project is branded
  RV32IM. The original blink demo never executed a runtime multiply/divide, so
  the gap was latent. The CLI's number formatting (`%u`/`%x` → integer
  division) exposed it: nonzero values printed as `0`.
  - Fix: `asic/soc_core.sv` now sets `ENABLE_MUL(1)` and `ENABLE_DIV(1)`.
  - `core/picorv32_pcpi.sv` (new) restores the `picorv32_pcpi_mul` and
    `picorv32_pcpi_div` PCPI co-processor modules (extracted verbatim from
    upstream YosysHQ/picorv32, ISC-licensed) that the trimmed `picorv32.sv`
    referenced but did not define.

### Simulation (`sim/`)
- **`main.cpp`** — added a pin-level **interactive UART bridge** to the
  Verilator harness:
  - Host `stdin` keystrokes are serialized 8N1 onto the `uart_rx` pin.
  - The `uart_tx` pin is decoded (falling-edge start detect + mid-bit sampling)
    and written to `stdout`.
  - Bit period = `baud_div × 16 = 224` clock cycles, matching `uart_init(14)`.
  - `stdin` is non-blocking (`O_NONBLOCK`, polled every 256 cycles); the
    terminal is put in raw mode (ICANON/ECHO off, ISIG kept so Ctrl-C quits).
  - `SIM_QUIET=1` suppresses the `[SIM]` diagnostic prints for a clean console.

### Tooling (`scripts/`)
- **`verilog_hex_to_memh.py`** — rewritten. `objcopy --verilog-data-width=4`
  emits **word addresses** (`@00004000` ⇒ byte `0x10000`) and 32-bit word
  tokens; the old script treated `@` as a byte address and tokens as single
  bytes, producing a negative size and a 0-byte SRAM image (the CPU then
  executed zeros). The converter now parses word-addressed tokens correctly.

---

## 3. Memory budget

```
firmware.elf:  text 9892   data 20   bss 12824   ≈ 22 KB of 32 KB SRAM
```

`bss` is dominated by the 12 KB FreeRTOS `heap_4` arena (`ucHeap`, in `.bss`).
Task stacks (idle, TaskA, TaskB, CLI) are allocated from that heap. At runtime
`status` reports ~8 KB free heap, leaving comfortable headroom.

---

## 4. How to build and run

```bash
# Build firmware (RV32IM) and the Verilator model
make -C firmware APP=firmware APP_SRC=main.c all
make -C sim sim

# Interactive run — type commands into the terminal
cd sim && ./obj_dir_firmware/Vsoc_top
#   (or, from repo root)
make run
```

Clean console (suppress simulator diagnostics):

```bash
cd sim && SIM_QUIET=1 ./obj_dir_firmware/Vsoc_top
```

Non-interactive smoke test (pipe paced commands; the pacing avoids overrunning
the 8-deep hardware RX FIFO during long command output):

```bash
cd sim
( sleep 4; echo ver; sleep 3; echo status; sleep 4; \
  echo "memread 0x20002000"; sleep 4; echo "gpio 0x000000ff"; \
  sleep 3; echo status; sleep 5; echo help; sleep 6 ) \
  | SIM_QUIET=1 timeout 60 ./obj_dir_firmware/Vsoc_top | tr -d '\r'
```

---

## 5. Verified session

```
=== SkyForge CLI ===
skyforge> ver
SkyForge PicoRV32 SoC (RV32IM)
FreeRTOS+CLI interactive shell
skyforge> status
uptime    : 191 ms
tasks     : 4
heap free : 8096 bytes
heap min  : 8096 bytes
skyforge> memread 0x20002000
[0x20002000] = 0x00000000
skyforge> gpio 0x000000ff
GPIO_OUT <= 0x000000ff
skyforge> status
uptime    : 503 ms          # tick advances → timer IRQ + scheduler healthy
tasks     : 4
heap free : 8096 bytes
skyforge> help
help / ver / status / memread <addr> / gpio <hex>
```

`gpio 0x000000ff` was confirmed to physically drive `GPIO_OUT` to `0x000000FF`
in the RTL, and `vTaskA`/`vTaskB` continued toggling GPIO bits 0/1 throughout.

---

## 6. Notes and follow-ups

- **ASIC impact:** scaling SRAM to 32 KB (8 × 4 KB OpenRAM macros) and enabling
  hardware MUL/DIV both increase area and affect timing. The ASIC
  implementation numbers in the top-level README/ASIC report were generated for
  the previous 16 KB / no-M configuration and should be re-run if a fresh ASIC
  pass is desired.
- **UART RX is polled.** `uart_getc()` busy-polls inside the CLI task. This is
  fine here (preemption keeps the other tasks running), but an interrupt-driven
  RX feeding a FreeRTOS stream buffer would free the CPU; `stream_buffer.c` is
  already compiled in the kernel for a future upgrade.
- **Adding commands** is a few lines: define a `CLI_Command_Definition_t` and a
  callback, then call `FreeRTOS_CLIRegisterCommand()` in `cli_start()`.
