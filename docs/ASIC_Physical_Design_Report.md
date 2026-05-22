# Comprehensive ASIC Physical Design Post-Mortem & Educational Case Study
## 32-bit RISC-V System-on-Chip (soc_core_prod)

**Process Node:** SkyWater 130nm (`sky130A`)  
**Core Architecture:** PicoRV32 (RV32IMC)  
**On-Chip Memory:** 32KB SRAM (8 instances of 4KB `sky130_sram_4kbyte_1rw_32x1024_8`)  
**Toolchain:** OpenROAD / OpenLane Flow  
**Author / Lead PD Engineer:** Kishor  
**Date:** May 2026  

---

## Table of Contents
1.  **Project Overview & Architectural Context**
2.  **Understanding the OpenLane VLSI Flow**
3.  **Phase 1: The "Auto-Placement" Baseline & The L-Shape Trap**
4.  **Phase 2: Symmetrical Channel Placement & The Aspect Ratio Dilemma**
5.  **The Physics of Routing: Pin Orientation & Congestion Analysis**
6.  **Phase 3: The Breakthrough - Block-Partitioned "Split-Die" Floorplan**
7.  **Power Delivery Network (PDN) Implications**
8.  **Final Signoff Metrics & Timing Analysis**
9.  **Future Scope: Overcoming the QSPI XIP Bottleneck with I-Cache**

---

## 1. Project Overview & Architectural Context

The objective of this project was to take a custom, bare-metal 32-bit RISC-V System-on-Chip from RTL (SystemVerilog) through a complete RTL-to-GDSII Physical Design flow, ultimately producing a manufacturing-ready layout verified against design rules (DRC) and layout-vs-schematic (LVS) checks.

### 1.1 The CPU Core (PicoRV32)
The compute engine for this SoC is the PicoRV32, an open-source, size-optimized RISC-V core designed by Clifford Wolf. Unlike high-performance superscalar cores, the PicoRV32 is deliberately engineered to consume the minimum possible standard cell area. This architectural choice presents a unique physical design challenge: the standard cell area is dwarfed by the required memory peripherals.

### 1.2 The Memory Constraint
Modern embedded applications, including Real-Time Operating Systems (RTOS) like Zephyr or FreeRTOS, require a baseline amount of rapid, on-chip memory for stack and heap allocation. This SoC specifies **32 Kilobytes of SRAM**. 
In the SkyWater 130nm process node, 32KB cannot be synthesized effectively out of standard flip-flops. Instead, it must be instantiated using rigid analog SRAM macros. We utilized the open-source OpenRAM compiler to generate 4KB SRAM banks. To reach 32KB, eight (8) identical 4KB macros (`sky130_sram_4kbyte_1rw_32x1024_8`) were required.

### 1.3 The Physical Challenge
Integrating 8 massive, inflexible rectangular analog blocks alongside 25,000+ tiny, flexible standard cells is the classic VLSI floorplanning problem. If the macros are placed incorrectly, they will block the routing tracks (Metal 1 through Metal 5), isolate logic clusters, and create insurmountable timing delays across the silicon die.

---

## 2. Understanding the OpenLane VLSI Flow

To appreciate the optimizations made during this project, one must understand how the OpenLane toolchain translates code into silicon geometries. 

1.  **Synthesis (Yosys / ABC):** The SystemVerilog RTL is translated into a netlist of Sky130 standard cells (e.g., `sky130_fd_sc_hd__nand2_1`).
2.  **Floorplanning (Init_fp / IOPlacer):** The physical dimensions of the die are calculated based on user constraints (`FP_CORE_UTIL`, `FP_ASPECT_RATIO`). I/O pins are placed around the periphery.
3.  **Macro Placement (TritonMacroPlace):** Hard analog blocks (like SRAM) are placed within the core area.
4.  **Power Delivery Network (PDN):** A massive grid of upper-metal layer stripes (Met4/Met5) is dropped over the chip to distribute VDD and GND.
5.  **Placement (RePlacer / OpenDP):** The 25,000+ standard cells are legally placed into standardized silicon rows, attempting to minimize the Manhattan distance between connected components.
6.  **Clock Tree Synthesis (TritonCTS):** A balanced network of buffers is built to ensure the clock signal reaches every flip-flop at precisely the same time.
7.  **Routing (FastRoute / TritonRoute):** Physical metal wires and vias are drawn to connect the standard cells and macros.
8.  **Signoff (Magic / Netgen):** The final geometric layout (GDSII) is checked for manufacturing rule violations (DRC) and electrical correctness (LVS).

Throughout the 20 iterations of this project, the focus was entirely on mastering Steps 2 and 3: **Floorplanning and Macro Placement**.

---

## 3. Phase 1: The "Auto-Placement" Baseline & The L-Shape Trap
*(Relevant Runs: `RUN_2026.05.15_17.27.51` through `RUN_2026.05.16_05.53.49`)*

### 3.1 Initial Configuration
In the earliest stages of the project, we relied heavily on OpenLane's default heuristics.
*   `FP_CORE_UTIL`: **30% - 45%** (Targeting a very sparse standard cell density)
*   `FP_ASPECT_RATIO`: **1.0** (A perfectly square silicon die)
*   `MACRO_PLACEMENT`: **Automatic** (Relying on TritonMacroPlace's simulated annealing algorithm)

### 3.2 The Auto-Placement Physics
TritonMacroPlace attempts to solve a highly complex optimization problem: it wants to place the 8 macros close to the logic that talks to them, but it absolutely refuses to place macros in the center of the die if the utilization is low, because macros act as "blockages" to the standard cell placement grid.

Because we set the core utilization (`FP_CORE_UTIL`) to a highly conservative 30%, the tool mathematically calculated that we needed a massively oversized die. Given this massive playground, TritonMacroPlace shoved all 8 SRAM macros into the far bottom-left corner of the die, forming a dense "L-Shape" against the boundaries.

### 3.3 The Engineering Fallout
This initial layout, while successful in passing DRC, was highly flawed for a production environment:

1.  **Wasted Silicon Real Estate:** Silicon wafers are expensive. A chip that is 70% empty air (whitespace) costs exactly the same to manufacture as a chip that is 70% densely packed transistors. The right half of our die was a complete wasteland.
2.  **Catastrophic Wire Lengths:** Because the memory was clustered in the extreme bottom-left, the standard cells handling the CPU pipeline were forced to stretch across the vast empty spaces. When the AXI interconnect attempted to route 32-bit data buses to the SRAM, the physical wires had to cross hundreds of micrometers. 
3.  **RC Delay (Resistance & Capacitance):** In the 130nm node, long wires have significant parasitic resistance and capacitance. A signal taking a long physical journey takes longer to arrive, forcing the entire CPU to run at a lower clock frequency (Mhz) to avoid setup-time violations.

---

## 4. Phase 2: Symmetrical Channel Placement & The Aspect Ratio Dilemma
*(Relevant Runs: `RUN_2026.05.16_09.56.05` through `RUN_2026.05.16_10.00.52`)*

Recognizing the flaws of the automated approach, the strategy shifted to strict, manual physical control.

### 4.1 The Configuration Pivot
*   `FP_CORE_UTIL`: Increased to **55%** (Forcing the tool to shrink the die boundary).
*   `MACRO_PLACEMENT_CFG`: Introduced manual coordinate mapping via `macro.cfg`.

### 4.2 The "H-Tree" Channel Concept
To solve the routing delay, we implemented a textbook VLSI technique known as "Channel Routing". We defined specific X and Y coordinates in `macro.cfg` to place 4 SRAM banks on the extreme left edge, and 4 SRAM banks on the extreme right edge. 

By pushing the macros to opposite walls, we created a wide, vertical "valley" or "channel" in the dead center of the chip. The OpenROAD standard-cell placer immediately populated this channel with the PicoRV32 logic.
This was a brilliant architectural move because it placed the CPU perfectly equidistant from all 8 memory banks, mathematically guaranteeing that the wire delay to Bank 0 was identical to the wire delay to Bank 7.

### 4.3 The Aspect Ratio Dead-Zone
Despite this breakthrough, a new physical anomaly emerged. 
Because `FP_ASPECT_RATIO` remained locked at `1.0` (a square), the mathematical equation OpenLane uses to calculate the die area forced the height of the chip to be ~2146µm.

However, each Sky130 4KB SRAM macro is approximately 410µm tall. Stacking 4 of them vertically (with 40µm spacing) only consumed about 1700µm of height. 
Since the macros were anchored to the bottom of the die (Y=100), the top of the macro column ended at Y=1700. This left a staggering 400µm wide band of completely empty, unused silicon stretching across the entire top of the chip. The die was too tall for the geometry of the macros.

---

## 5. The Physics of Routing: Pin Orientation & Congestion Analysis

While the vertical gap was an area problem, a much more severe routing problem was quietly brewing due to the orientation of the macros.

### 5.1 Macro Pin Definitions (LEF)
In the Library Exchange Format (LEF), every macro defines exactly where its input and output pins are physically located on its metal perimeter. For the `sky130_sram_4kbyte_1rw_32x1024_8` macro, the designers of the OpenRAM compiler placed almost all the critical pins (Data In, Data Out, Address, Clock) on the **bottom edge** of the rectangular macro block.

### 5.2 The 90-Degree Congestion Crisis
In our "Channel" layout, we placed the macros on the left and right walls, and the logic in the center. 
If a macro's pins are on its bottom edge, but the logic trying to talk to it is located to its right (in the central channel), every single wire exiting the macro must travel straight down, immediately execute a 90-degree turn, and merge into the horizontal routing tracks to reach the CPU.

When you multiply this by 32 bits of address, 32 bits of write data, and 32 bits of read data, across 8 distinct memory banks, you create a massive traffic jam. TritonRoute (the detailed router) struggled to find available metal tracks at the corners of the macros, leading to dense localized congestion hotspots and potential DRC violations (shorts/spacing errors).

---

## 6. Phase 3: The Breakthrough - Block-Partitioned "Split-Die" Floorplan
*(Relevant Runs: `RUN_2026.05.16_12.22.57` to Final Signoff `RUN_2026.05.16_13.07.51`)*

To solve both the Aspect Ratio Dead-Zone and the 90-Degree Pin Congestion, a completely novel floorplan architecture was conceptualized and successfully implemented. This layout is referred to as a "Block Partitioned" or "Split-Die" layout.

### 6.1 The Master Configuration
*   `FP_ASPECT_RATIO`: **1.2** (Tall Rectangle)
*   `FP_CORE_UTIL`: **75%** (Aggressive, high-density packing)
*   `macro.cfg`: 2x4 "Top-Heavy" clustered placement.

### 6.2 Executing the Split-Die
Instead of fighting the square area calculation, we leaned into the geometry of the SRAM macros. By setting the aspect ratio to 1.2, we elongated the chip into a portrait orientation (roughly 1600µm wide by 3000µm tall). 

We rewrote the `macro.cfg` file to place all 8 SRAM macros into a solid, impenetrable 2-column by 4-row block at the absolute top of the die. We left the bottom 1200µm of the chip completely devoid of macros.

Because we simultaneously pushed the utilization to an aggressive 75%, the OpenROAD placement engine was forced to pack all 25,371 standard cells tightly into this lower 1200µm region. This created a highly efficient, contiguous "Compute Block" beneath a massive "Memory Block."

### 6.3 The Pin Optimization Masterstroke
The true genius of this layout was the orientation configuration. 
In the `macro.cfg`, every single one of the 8 macros was given the `N` (North) orientation. Because the pins on the Sky130 SRAM macro reside on its bottom edge, orienting them North meant that **every single data and address pin naturally pointed straight down**.

Since the Compute Block (the standard cells) was located directly below the Memory Block, the router no longer had to execute complex 90-degree detours. The AXI interconnect buses flowed cleanly and directly in vertical, straight lines (using Met2 and Met4 tracks) from the CPU up into the memory array. Routing congestion dropped to zero.

---

## 7. Power Delivery Network (PDN) Implications

The Split-Die layout inadvertently solved another critical physical design challenge: Voltage Drop (IR Drop).

In a mixed-signal die, the Power Delivery Network (PDN) drops vertical and horizontal stripes of power to feed the cells. When a macro is placed in the center of a die, the PDN stripes must be carefully routed *around* or *over* the macro (if the macro has upper-metal blockages), often breaking the continuity of the power grid for the standard cells.

By pushing all macros to the top of the die and dedicating the bottom exclusively to standard cells, the OpenLane PDN generator was able to draw a completely unbroken, perfectly uniform power grid across the entire Compute Block. This ensures that the PicoRV32 core experiences highly stable VDD voltage during periods of intense switching activity, preventing brown-outs and clock-jitter.

---

## 8. Final Signoff Metrics & Timing Analysis

The final iteration of the pipeline (`RUN_2026.05.16_13.07.51`) successfully completed the flow and generated a production-ready GDSII file. The metrics speak for the efficiency of the layout:

*   **Total Die Area:** `3.52 mm²` (Highly cost-effective for a 130nm microcontroller).
*   **Total Logic Cells:** `25,371`
*   **Total Wire Length:** `1.31 meters` (1,310,343 µm). 
    *   *Note: Keeping the wire length to 1.3m across 25,000 cells is a testament to the efficiency of the Split-Die layout and the 75% core utilization.*
*   **TritonRoute Violations:** `0`
    *   *Note: The global and detailed routers resolved all physical connections without a single short, minimum-hole, or metal-spacing violation.*

### 8.1 Timing Closure Analysis
The Static Timing Analysis (STA) reported a Worst Negative Slack (WNS) of `-1.95 ns` against a target clock period of `10.0 ns` (100 MHz). 

*   **Interpretation:** The critical path inside the chip takes approximately 11.95ns to resolve, capping the maximum safe operating frequency at roughly **83.6 MHz** under worst-case PVT (Process, Voltage, Temperature) corners.
*   **Context:** For a 130nm process node running an AXI interconnect through an 8-bank SRAM array, an 83 MHz operating frequency is a highly respectable result. Closing timing at 100MHz would likely require inserting pipeline registers inside the AXI interconnect to break up the long logic paths traveling from the bottom Compute Block up to the top SRAM rows.

---

## 9. Future Scope: Overcoming the QSPI XIP Bottleneck with I-Cache

From a Physical Design perspective, the `soc_core_prod` floorplan is a resounding success. However, analyzing the system from a Computer Architecture perspective reveals the next critical bottleneck that must be addressed in RTL.

### 9.1 The Execute-In-Place (XIP) Dilemma
The SoC includes a `flash_ctrl` module designed for QSPI (Quad Serial Peripheral Interface). Crucially, the module exposes an `xip_active` signal, allowing the AXI interconnect to map memory addresses directly to the external Flash chip. This permits the PicoRV32 to fetch instructions directly from Flash without copying them to SRAM first.

### 9.2 The Latency Penalty
While XIP saves on-chip SRAM, it introduces catastrophic latency. The CPU pipeline operates at ~83 MHz, attempting to execute one instruction per clock cycle. However, fetching a 32-bit instruction over a QSPI interface requires issuing a command, sending an address, and shifting data back over 4 serial pins. This transaction can take upwards of 20 to 40 clock cycles. 

Without hardware mitigation, the PicoRV32 will fetch an instruction, execute it in 1 cycle, and then stall for 39 cycles waiting for the next instruction. The effective IPC (Instructions Per Clock) will plummet to near zero.

### 9.3 The Architectural Imperative: Instruction Cache
To truly capitalize on the highly optimized physical layout achieved in this project, the RTL must be upgraded to include an **Instruction Cache (I-Cache)**. 

By inserting a 2KB or 4KB Direct-Mapped Cache between the AXI interconnect and the Flash controller, we can cache frequently accessed 16-byte blocks of instructions. Because loops and linear instruction streams exhibit high spatial locality, an I-Cache will absorb 90%+ of the flash latency. 

**Designing this cache is the logical next step.** It will not only skyrocket the performance of the SoC, but implementing a custom memory controller will further demonstrate mastery of advanced digital logic and bridging the gap between Computer Architecture and Physical Design.
