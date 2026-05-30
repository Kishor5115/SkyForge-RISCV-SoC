# Requirements Document: RISC-V Debug Module dmactive Fix

## Introduction

This document specifies the requirements for fixing the RISC-V Debug Module (DM) to achieve end-to-end OpenOCD/GDB breakpoint functionality on FreeRTOS tasks. The current implementation has a critical bug where the `dmactive` bit in the `dmcontrol` register does not properly latch writes from OpenOCD via the JTAG Debug Transport Module (DTM), preventing the Debug Module from becoming active.

The fix will enable OpenOCD to successfully activate the Debug Module, halt and resume the picorv32 core, access general-purpose registers, and set breakpoints for debugging FreeRTOS applications.

## Glossary

- **Debug_Module (DM)**: The RISC-V Debug Module implementing Debug Spec 0.13, responsible for halting/resuming the CPU core and providing register/memory access
- **JTAG_DTM**: The JTAG Debug Transport Module that implements the IEEE 1149.1 TAP controller and provides the DMI (Debug Module Interface) to communicate with the Debug Module
- **DMI**: Debug Module Interface, a register-based bus protocol for accessing Debug Module registers via JTAG
- **dmcontrol**: Debug Module Control register at DMI address 0x10, containing the dmactive bit and halt/resume control bits
- **dmactive**: Bit 0 of the dmcontrol register; when set to 1, activates the Debug Module; when cleared to 0, resets the Debug Module to its initial state
- **dmstatus**: Debug Module Status register at DMI address 0x11, providing hart status information (halted, running, etc.)
- **OpenOCD**: Open On-Chip Debugger, the external debug tool that communicates with the Debug Module via JTAG
- **picorv32**: The RISC-V CPU core being debugged
- **System_Clock_Domain**: The clock domain running at the system clock frequency (clk_i) where the Debug Module operates
- **JTAG_Clock_Domain**: The clock domain running at the JTAG TCK frequency where the JTAG DTM operates
- **CDC**: Clock Domain Crossing, the mechanism for safely transferring signals between different clock domains
- **Abstract_Command**: A Debug Module command for accessing CPU registers or memory without halting program execution
- **Hart**: Hardware thread, in this context refers to the single picorv32 CPU core

## Requirements

### Requirement 1: dmcontrol Register Write Latching

**User Story:** As a hardware debugger (OpenOCD), I want to write to the dmcontrol register and have the dmactive bit properly latch, so that I can activate the Debug Module and begin debugging operations.

#### Acceptance Criteria

1. WHEN OpenOCD writes 1 to the dmactive bit (bit 0) of dmcontrol register (DMI address 0x10) via JTAG, THEN THE Debug_Module SHALL latch the value and set its internal dmactive state to 1
2. WHEN OpenOCD reads back the dmcontrol register after writing dmactive=1, THEN THE Debug_Module SHALL return dmcontrol with bit 0 set to 1
3. WHEN dmactive transitions from 0 to 1, THEN THE Debug_Module SHALL exit reset state and become operational
4. WHEN OpenOCD writes 0 to the dmactive bit while dmactive is 1, THEN THE Debug_Module SHALL clear its internal dmactive state to 0 and reset all Debug Module state
5. WHEN dmactive is 0, THEN THE Debug_Module SHALL hold all debug control signals (dbg_halt_req, dbg_resume_req, dbg_reg_write, dbg_reg_read) at their inactive/safe values

### Requirement 2: Clock Domain Crossing for DMI Transactions

**User Story:** As a system integrator, I want DMI transactions from the JTAG clock domain to be safely transferred to the system clock domain, so that the Debug Module can reliably process OpenOCD commands without metastability or data corruption.

#### Acceptance Criteria

1. WHEN THE JTAG_DTM receives a DMI write transaction in the JTAG_Clock_Domain, THEN THE System SHALL safely transfer the write address, data, and control signals to the System_Clock_Domain
2. WHEN THE JTAG_DTM receives a DMI read transaction in the JTAG_Clock_Domain, THEN THE System SHALL safely transfer the read address to the System_Clock_Domain and return the read data back to the JTAG_Clock_Domain
3. WHEN a DMI transaction crosses clock domains, THEN THE System SHALL use proper synchronization techniques (multi-stage flip-flops for control signals, handshake protocols for data) to prevent metastability
4. WHEN THE Debug_Module completes a DMI transaction in the System_Clock_Domain, THEN THE System SHALL signal completion back to the JTAG_Clock_Domain via synchronized handshake
5. WHEN multiple DMI transactions are issued in sequence, THEN THE System SHALL process them in order without data corruption or lost transactions

### Requirement 3: Debug Module Reset Behavior

**User Story:** As a hardware debugger, I want the Debug Module to properly reset when dmactive is cleared, so that I can return the debug system to a known state and recover from error conditions.

#### Acceptance Criteria

1. WHEN dmactive transitions from 1 to 0, THEN THE Debug_Module SHALL clear all pending abstract commands and set cmderr to 0
2. WHEN dmactive transitions from 1 to 0, THEN THE Debug_Module SHALL clear haltreq and resumereq control bits
3. WHEN dmactive is 0, THEN THE Debug_Module SHALL not assert dbg_halt_req or dbg_resume_req to the CPU core
4. WHEN dmactive transitions from 0 to 1, THEN THE Debug_Module SHALL initialize to a clean state with no pending operations
5. WHEN THE System is reset (resetn=0), THEN THE Debug_Module SHALL initialize with dmactive=0

### Requirement 4: Hart Halt and Resume Control

**User Story:** As a hardware debugger, I want to halt and resume the CPU core via the Debug Module, so that I can inspect program state and single-step through code.

#### Acceptance Criteria

1. WHEN dmactive is 1 AND OpenOCD writes haltreq=1 to dmcontrol, THEN THE Debug_Module SHALL assert dbg_halt_req to the picorv32 core
2. WHEN THE picorv32 core halts in response to dbg_halt_req, THEN THE Debug_Module SHALL observe dbg_halted=1 and reflect this in dmstatus register
3. WHEN dmactive is 1 AND OpenOCD writes resumereq=1 to dmcontrol, THEN THE Debug_Module SHALL assert dbg_resume_req to the picorv32 core for one clock cycle
4. WHEN THE picorv32 core resumes execution, THEN THE Debug_Module SHALL observe dbg_halted=0 and reflect this in dmstatus register
5. WHEN dmactive is 0, THEN THE Debug_Module SHALL not respond to haltreq or resumereq writes

### Requirement 5: Abstract Command Execution for Register Access

**User Story:** As a hardware debugger, I want to read and write CPU general-purpose registers via abstract commands, so that I can inspect and modify program state during debugging.

#### Acceptance Criteria

1. WHEN dmactive is 1 AND the hart is halted AND OpenOCD writes an Access Register command to the command register (DMI address 0x17), THEN THE Debug_Module SHALL execute the register access
2. WHEN an Access Register read command is executed, THEN THE Debug_Module SHALL read the specified register from the picorv32 core via dbg_reg_read and dbg_reg_addr, and store the result in data0 register (DMI address 0x04)
3. WHEN an Access Register write command is executed, THEN THE Debug_Module SHALL write the value from data0 register to the specified register in the picorv32 core via dbg_reg_write, dbg_reg_addr, and dbg_reg_wdata
4. WHEN an abstract command is attempted while the hart is not halted, THEN THE Debug_Module SHALL set cmderr to 0x010 (halt/resume error) in abstractcs register (DMI address 0x16)
5. WHEN dmactive is 0, THEN THE Debug_Module SHALL not execute abstract commands

### Requirement 6: Debug Module Status Reporting

**User Story:** As a hardware debugger, I want to read accurate status information from the Debug Module, so that I can determine the current state of the hart and debug system.

#### Acceptance Criteria

1. WHEN OpenOCD reads dmstatus register (DMI address 0x11), THEN THE Debug_Module SHALL return accurate hart status including allhalted, anyhalted, allrunning, anyrunning bits based on dbg_halted signal
2. WHEN THE hart is halted (dbg_halted=1), THEN THE dmstatus register SHALL report allhalted=1, anyhalted=1, allrunning=0, anyrunning=0
3. WHEN THE hart is running (dbg_halted=0), THEN THE dmstatus register SHALL report allhalted=0, anyhalted=0, allrunning=1, anyrunning=1
4. WHEN OpenOCD reads dmstatus, THEN THE Debug_Module SHALL report version=2 (indicating Debug Spec 0.13 compliance)
5. WHEN dmactive is 0, THEN THE dmstatus register SHALL still be readable and report the hart as running

### Requirement 7: System Bus Access for Memory Operations

**User Story:** As a hardware debugger, I want to read and write system memory via the Debug Module's System Bus Access (SBA) interface, so that I can inspect and modify memory contents without halting the CPU.

#### Acceptance Criteria

1. WHEN dmactive is 1 AND OpenOCD writes to sbaddress0 register (DMI address 0x39) with sbreadonaddr=1, THEN THE Debug_Module SHALL initiate an AXI read transaction to the specified address
2. WHEN dmactive is 1 AND OpenOCD writes to sbdata0 register (DMI address 0x3C), THEN THE Debug_Module SHALL initiate an AXI write transaction to the address in sbaddress0
3. WHEN a System Bus Access transaction completes successfully, THEN THE Debug_Module SHALL update sbdata0 with read data (for reads) and clear the busy bit in sbcs register (DMI address 0x38)
4. WHEN a System Bus Access transaction fails, THEN THE Debug_Module SHALL set the appropriate error code in sberror field of sbcs register
5. WHEN dmactive is 0, THEN THE Debug_Module SHALL not initiate System Bus Access transactions

### Requirement 8: OpenOCD Integration and Breakpoint Support

**User Story:** As a firmware developer, I want to use OpenOCD and GDB to set breakpoints in my FreeRTOS application and inspect task state, so that I can debug multi-threaded embedded software.

#### Acceptance Criteria

1. WHEN OpenOCD connects to the JTAG interface and reads the IDCODE, THEN THE JTAG_DTM SHALL return a valid IDCODE value
2. WHEN OpenOCD attempts to activate the Debug Module by writing dmactive=1, THEN THE Debug_Module SHALL become active and OpenOCD SHALL successfully read back dmactive=1
3. WHEN OpenOCD halts the core and reads general-purpose registers, THEN THE Debug_Module SHALL return accurate register values via abstract commands
4. WHEN GDB sets a software breakpoint (EBREAK instruction) in FreeRTOS task code, THEN THE picorv32 core SHALL halt at the breakpoint and THE Debug_Module SHALL report the halted state
5. WHEN GDB continues execution after a breakpoint, THEN THE Debug_Module SHALL resume the core and FreeRTOS SHALL continue normal operation

### Requirement 9: Minimal Debug Module Register Set

**User Story:** As a system implementer, I want the Debug Module to implement the minimal required register set from Debug Spec 0.13, so that OpenOCD can successfully communicate with the debug system.

#### Acceptance Criteria

1. THE Debug_Module SHALL implement dmcontrol register (DMI address 0x10) with dmactive, haltreq, resumereq, and hartreset bits
2. THE Debug_Module SHALL implement dmstatus register (DMI address 0x11) with version, allhalted, anyhalted, allrunning, anyrunning, and allresumeack bits
3. THE Debug_Module SHALL implement hartinfo register (DMI address 0x12) reporting the hart's debug capabilities
4. THE Debug_Module SHALL implement abstractcs register (DMI address 0x16) with busy, cmderr, and datacount fields
5. THE Debug_Module SHALL implement command register (DMI address 0x17) for issuing abstract commands
6. THE Debug_Module SHALL implement data0 register (DMI address 0x04) for abstract command data transfer
7. THE Debug_Module SHALL implement sbcs register (DMI address 0x38) for System Bus Access control
8. THE Debug_Module SHALL implement sbaddress0 register (DMI address 0x39) for System Bus Access addressing
9. THE Debug_Module SHALL implement sbdata0 register (DMI address 0x3C) for System Bus Access data transfer

### Requirement 10: Bitband Operation Support

**User Story:** As a firmware developer, I want bitband operations to work correctly during debug sessions, so that I can debug code that uses atomic bit manipulation.

#### Acceptance Criteria

1. WHEN THE Debug_Module performs System Bus Access to bitband alias addresses, THEN THE System SHALL correctly translate and execute the bitband operation
2. WHEN THE picorv32 core is halted and GDB inspects bitband memory regions, THEN THE Debug_Module SHALL return accurate bit values
3. WHEN THE Debug_Module writes to bitband alias addresses via System Bus Access, THEN THE System SHALL atomically modify the corresponding bit in the bitband region
4. WHEN FreeRTOS uses bitband operations for synchronization primitives, THEN THE operations SHALL function correctly during debug sessions
5. WHEN THE Debug_Module is active (dmactive=1), THEN bitband operations SHALL maintain their atomic behavior

