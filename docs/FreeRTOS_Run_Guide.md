# FreeRTOS bring-up on this SoC (step-by-step)

This repo currently does **not** include FreeRTOS sources.
This guide shows a clean, beginner-friendly path to:

1) Fetch the FreeRTOS kernel
2) Add a minimal FreeRTOS app for **RV32I**
3) Build it using this repo’s existing firmware toolchain + linker scripts
4) Run it on your SoC using one of the available boot methods

---

## 0) Know your SoC memory map (important)

From `firmware/lib/inc/common.h`:

- Boot ROM: `0x0000_0000`
- SRAM:     `0x0001_0000` (32 KB)
- UART:     `0x2000_0000`
- Timer:    `0x2000_1000`
- GPIO:     `0x2000_2000`
- SPI:      `0x2000_3000`
- Debug:    `0x2000_4000`
- Flash controller regs / XIP window: `0x4000_0000`

Your existing application linker script places `.text` into SRAM at `0x0001_0000`:

- `firmware/lib/scripts/linker.ld`

That’s great for FreeRTOS.

---

## 1) Install the RISC-V embedded toolchain

You need:

- `riscv64-unknown-elf-gcc`
- `riscv64-unknown-elf-ld`
- `riscv64-unknown-elf-gdb` (optional, for debug)

Check:

```bash
riscv64-unknown-elf-gcc --version
riscv64-unknown-elf-objcopy --version
```

If missing, install a prebuilt toolchain and add it to `PATH`.

---

## 2) Add FreeRTOS kernel sources into the repo

From the repo root:

```bash
mkdir -p third_party
cd third_party

git clone https://github.com/FreeRTOS/FreeRTOS-Kernel.git
```

This gives you:

- `third_party/FreeRTOS-Kernel/`

---

## 3) Choose the simplest FreeRTOS port strategy (RV32I)

Your firmware builds with:

- `-march=rv32i -mabi=ilp32`

FreeRTOS provides a RISC-V GCC port, but which exact port directory you use depends on the kernel version.

### 3.1 What you need (conceptually)

You need these FreeRTOS components:

- Kernel core:
  - `tasks.c`, `queue.c`, `list.c`, `timers.c` (optional), `event_groups.c` (optional)
- Port layer (RISC-V GCC):
  - `port.c`
  - `portASM.S`
  - `portmacro.h`
- Memory allocator:
  - `heap_4.c` (recommended)

### 3.2 What you must provide (for your SoC)

- `FreeRTOSConfig.h`
- A tick interrupt source (use your APB timer at `0x2000_1000`)
- ISR glue that calls `xPortSysTickHandler()` from the timer IRQ

Good news: your repo already has:

- Timer driver: `firmware/drivers/src/timer.c`
- IRQ dispatch + vector entry: `firmware/lib/src/crt0.S` and `firmware/drivers/src/irq.c`

---

## 4) Minimal integration layout (recommended)

Create these folders:

```bash
mkdir -p firmware/third_party/FreeRTOS
mkdir -p firmware/third_party/FreeRTOS/portable
mkdir -p firmware/software/freertos
```

Then **copy** the needed kernel files from `third_party/FreeRTOS-Kernel/` into `firmware/third_party/FreeRTOS/`.

Why copy?

- Your firmware Makefile is simple and doesn’t use recursive make.
- Copying keeps paths stable and avoids long `VPATH` complexity for a first-time integration.

---

## 5) Create FreeRTOSConfig.h (starter)

Create `firmware/third_party/FreeRTOS/FreeRTOSConfig.h` with settings appropriate for 32KB SRAM.

You should start small:

- Minimal task stack sizes
- No MPU
- No fancy features until basic scheduling works

(If you want, I can generate a config file tailored to this SoC once you decide: preemption on/off, tick rate, and whether you want timers/event groups.)

---

## 6) Provide the tick ISR (timer interrupt)

Your IRQ mapping (from RTL + firmware headers):

- Timer IRQ = bit 3

Your firmware uses weak handlers in `firmware/drivers/src/irq.c`.
To hook FreeRTOS tick:

1) Implement `timer_irq_handler()` in your app (this overrides the weak default).
2) In that handler:
   - Clear the timer IRQ
   - Call `xPortSysTickHandler()`

You also need to configure the timer to generate periodic interrupts at `configTICK_RATE_HZ`.

---

## 7) Build system changes

Your current build uses `firmware/Makefile` and builds `firmware/software/main.c` into SRAM using `firmware/lib/scripts/linker.ld`.

Recommended first step:

- Keep the build system as-is.
- Create a new app entry file, e.g. `firmware/software/freertos/main.c`.
- Temporarily switch the firmware Makefile to build that file instead of `software/main.c`.

Commands to build the existing firmware today:

```bash
make -C firmware clean
make -C firmware software
```

You’ll extend it so `make -C firmware freertos` builds your FreeRTOS demo.

---

## 8) How to run FreeRTOS on the SoC

There are 3 practical boot paths. Start with the simplest that matches your current hardware/debug state.

### Option A (recommended for first bring-up): load into SRAM and jump

This requires a debug load mechanism (typically OpenOCD+GDB), which in turn requires a **standard RISC-V Debug Module** in RTL.

Once DM is working, the flow is:

```bash
# Terminal 1
openocd -f interface.cfg -f target.cfg

# Terminal 2
riscv64-unknown-elf-gdb firmware/build/your_freertos.elf
(gdb) target remote :3333
(gdb) monitor reset halt
(gdb) load
(gdb) continue
```

### Option B: boot from flash via your Boot ROM copier

Your boot ROM firmware (`firmware/boot/boot_rom.c`) expects a flash image with:

- Header at flash offset 0:
  - word0: magic `0x52534356` ("RSCV")
  - word1: `app_size`
  - word2: `entry_addr` (typically `0x00010000`)
  - word3: checksum (whatever your boot ROM expects)
- Payload starting at offset `0x10`

Then boot ROM copies payload into SRAM at `0x00010000` and jumps.

This is good long-term, but you need a reliable way to program external flash.

### Option C: run from simulation

If you’re still early in bring-up, running the SoC in simulation is often the fastest way to validate FreeRTOS scheduling + tick.

---

## 9) First FreeRTOS “hello world” test

A minimal test should:

- Initialize UART
- Create two tasks that print periodically
- Confirm the scheduler runs and tick interrupts are firing

Expected UART output pattern:

- Task A prints every 500ms
- Task B prints every 1000ms

If only one line prints and then it hangs, typical causes are:

- Tick interrupt not firing
- Stack overflow
- Wrong critical section implementation in the port layer

---

## 10) What I need from you to make this fully precise

To make this guide 100% copy/paste for *your* setup, I need 3 details:

1) Which board are you running on (FPGA dev board? custom PCB?)
2) Which JTAG adapter you have (FTDI / CMSIS-DAP / J-Link / other)
3) What clock frequency the timer sees (100 MHz in comments today?)

With that, I can:

- Add a ready-to-build FreeRTOS demo app + `FreeRTOSConfig.h`
- Add a `freertos` target to `firmware/Makefile`
- Provide exact timer reload values for `configTICK_RATE_HZ`

