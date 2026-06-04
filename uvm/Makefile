# =============================================================================
#  uvm/Makefile - Compile + run the RISC-V SoC UVM environment
#
#  Usage:
#    make uart        # compile + run uart_test       (DUT = uart_ctrl_apb)
#    make gpio        # compile + run gpio_test        (DUT = gpio_apb)
#    make timer       # compile + run timer_test       (DUT = timer_apb)
#    make spi         # compile + run spi_test         (DUT = spi_master_apb)
#    make soc_smoke   # compile + run soc_smoke_test   (DUT = soc_top)
#    make soc_stress  # compile + run soc_stress_test  (DUT = soc_top)
#    make all         # run all of the above
#    make cov         # merge coverage and generate a report
#    make lint        # Verilator lint of the APB interface + peripheral RTL
#    make clean
#
#  Simulator selection (commercial UVM simulator required for a full run):
#    make uart SIM=vcs
#    make uart SIM=questa     (default)
#    make uart SIM=xcelium
#
#  UVM library: external open-source uvm-core (override with UVM_HOME=...).
#  See README.md for running with Verilator if no commercial simulator exists.
# =============================================================================

SIM      ?= questa
UVM_HOME ?= /home/kishor/uvm-core/src
RTL_DIR  ?= ../rtl
UVM_DIR  ?= .

# ---- Source groups ----------------------------------------------------------
IF_SRC   = env/apb_if.sv env/soc_if.sv
PKG_SRC  = soc_uvm_pkg.sv
INCDIRS  = +incdir+$(UVM_HOME) +incdir+$(UVM_DIR)

UART_RTL  = $(RTL_DIR)/peripherals/uart/uart_fifo.sv \
            $(RTL_DIR)/peripherals/uart/uart_tx.sv \
            $(RTL_DIR)/peripherals/uart/uart_rx.sv \
            $(RTL_DIR)/peripherals/uart/uart_ctrl_apb.sv
GPIO_RTL  = $(RTL_DIR)/peripherals/gpio/gpio_apb.sv
TIMER_RTL = $(RTL_DIR)/peripherals/timer/timer_apb.sv
SPI_RTL   = $(RTL_DIR)/peripherals/spi/spi_master_apb.sv
SOC_RTL   = $(RTL_DIR)/core/*.sv $(RTL_DIR)/memory/*.sv \
            $(RTL_DIR)/interconnect/*.sv $(RTL_DIR)/peripherals/*/*.sv \
            $(RTL_DIR)/asic/*.sv $(RTL_DIR)/soc_top.sv

.PHONY: all uart gpio timer spi soc_smoke soc_stress run cov lint clean help

all: uart gpio timer spi soc_smoke soc_stress
	@echo "==== All UVM tests completed ===="

# ---- Per-test entry points (delegate to the generic 'run' recipe) -----------
uart:       ; @$(MAKE) run TOP=tb_uart     TESTNAME=uart_test       TB=tb/tb_uart.sv     RTL="$(UART_RTL)"
gpio:       ; @$(MAKE) run TOP=tb_gpio     TESTNAME=gpio_test       TB=tb/tb_gpio.sv     RTL="$(GPIO_RTL)"
timer:      ; @$(MAKE) run TOP=tb_timer    TESTNAME=timer_test      TB=tb/tb_timer.sv    RTL="$(TIMER_RTL)"
spi:        ; @$(MAKE) run TOP=tb_spi      TESTNAME=spi_test        TB=tb/tb_spi.sv      RTL="$(SPI_RTL)"
soc_smoke:  ; @$(MAKE) run TOP=tb_soc_top  TESTNAME=soc_smoke_test  TB=tb/tb_soc_top.sv  RTL="$(SOC_RTL)"
soc_stress: ; @$(MAKE) run TOP=tb_soc_top  TESTNAME=soc_stress_test TB=tb/tb_soc_top.sv  RTL="$(SOC_RTL)"

# =============================================================================
#  Generic compile + run, dispatched by $(SIM)
#  Required vars: TOP, TESTNAME, TB, RTL
# =============================================================================
WORK := work_$(TOP)
PLUS := +UVM_TESTNAME=$(TESTNAME) +UVM_NO_RELNOTES

ifeq ($(SIM),vcs)
run:
	vcs -full64 -sverilog -timescale=1ns/1ps $(INCDIRS) \
	    -debug_access+all -cm line+cond+fsm+tgl \
	    $(UVM_HOME)/uvm_pkg.sv $(RTL) $(IF_SRC) $(PKG_SRC) $(TB) \
	    -top $(TOP) -o simv_$(TOP)
	./simv_$(TOP) $(PLUS) -cm line+cond+fsm+tgl -cm_name $(TESTNAME) -l $(TESTNAME).log

else ifeq ($(SIM),xcelium)
run:
	xrun -64bit -sv -timescale 1ns/1ps -uvmhome CDNS-1.2 $(INCDIRS) \
	     -coverage all -covtest $(TESTNAME) \
	     $(RTL) $(IF_SRC) $(PKG_SRC) $(TB) \
	     -top $(TOP) $(PLUS) -l $(TESTNAME).log

else ifeq ($(SIM),questa)
run:
	vlib $(WORK)
	vlog -sv -work $(WORK) -timescale 1ns/1ps $(INCDIRS) \
	     $(UVM_HOME)/uvm_pkg.sv $(RTL) $(IF_SRC) $(PKG_SRC) $(TB)
	vsim -c -work $(WORK) $(TOP) $(PLUS) \
	     -coverage -do "coverage save -onexit $(TESTNAME).ucdb; run -all; quit" \
	     -l $(TESTNAME).log

else
run:
	@echo "Unknown SIM='$(SIM)'. Use SIM=vcs | questa | xcelium."
	@exit 2
endif

# =============================================================================
#  Coverage merge / report
# =============================================================================
cov:
ifeq ($(SIM),vcs)
	urg -dir *.vdb -report cov_report
else ifeq ($(SIM),xcelium)
	imc -execcmd "merge cov_work/*/* -out merged; report -summary -out cov_report"
else ifeq ($(SIM),questa)
	vcover merge merged.ucdb *.ucdb
	vcover report -html -htmldir cov_report merged.ucdb
else
	@echo "Set SIM to vcs|questa|xcelium for coverage."
endif
	@echo "Coverage report written to cov_report/"

# =============================================================================
#  Verilator lint (structural check of the peripheral RTL DUTs).
#  Does NOT run UVM. Note: Verilator cannot parse the clocking-block modports
#  in apb_if.sv, so only the DUTs are linted here; the UVM/interface code is
#  meant for a commercial simulator (VCS/Questa/Xcelium).
# =============================================================================
LINTFLAGS = --lint-only -Wno-fatal -Wno-WIDTH -Wno-UNUSED -Wno-DECLFILENAME -I$(RTL_DIR)
lint:
	verilator $(LINTFLAGS) $(UART_RTL)  --top-module uart_ctrl_apb
	verilator $(LINTFLAGS) $(GPIO_RTL)  --top-module gpio_apb
	verilator $(LINTFLAGS) $(TIMER_RTL) --top-module timer_apb
	verilator $(LINTFLAGS) $(SPI_RTL)   --top-module spi_master_apb
	@echo "Verilator lint OK (peripheral DUTs)"

clean:
	rm -rf work_* simv_* csrc *.vdb *.ucdb merged* cov_report \
	       *.log *.key *.vcd *.fsdb transcript xcelium.d xrun.* INCA_libs \
	       ucli.key vc_hdrs.h obj_dir
	@echo "Clean done"

help:
	@grep -E '^[a-zA-Z_]+:' $(MAKEFILE_LIST) | sed 's/:.*//' | sort -u
