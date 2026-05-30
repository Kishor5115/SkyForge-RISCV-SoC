`timescale 1ns / 1ps

// soc_top bring-up testbench.
//
// Verifies basic SoC bring-up: it boots the integration firmware from BootROM
// and watches APB writes to the UART TX register for firmware PASS/FAIL
// markers. Unlike tb/soc_top_tb.sv it performs no JTAG sequencing, so it is a
// fast smoke test for the integrated SoC.
//
// Waveform dumping is OFF by default (keeps runs fast and avoids huge VCDs).
// Enable it with either:
//   - plusarg:  vvp soc_top_bringup_tb.vvp +vcd
//   - macro:    iverilog -DSOC_TB_VCD ...

module soc_top_bringup_tb;

    parameter         MEM_INIT_FILE      = "sim/integration_test.hex";
    parameter integer BOOTROM_ADDR_WIDTH = 13;
    parameter integer TIMEOUT_NS         = 50_000_000;

    logic        clk, rst_n;
    logic        uart_tx, uart_rx;
    logic [31:0] gpio_in, gpio_out, gpio_oe;
    logic        spi_sclk, spi_mosi, spi_miso;
    logic [3:0]  spi_cs_n;
    logic        flash_sclk, flash_cs_n, flash_mosi, flash_miso;
    logic        jtag_tck, jtag_tms, jtag_tdi, jtag_tdo;
    logic        trap;

    soc_top #(
        .MEM_INIT_FILE      (MEM_INIT_FILE),
        .BOOTROM_ADDR_WIDTH (BOOTROM_ADDR_WIDTH),
        .PROGADDR_IRQ       (32'h0000_0010)   // IRQ vector lives in BootROM
    ) dut (
        .clk(clk), .rst_n(rst_n),
        .uart_tx(uart_tx), .uart_rx(uart_rx),
        .gpio_in(gpio_in), .gpio_out(gpio_out), .gpio_oe(gpio_oe),
        .spi_sclk(spi_sclk), .spi_mosi(spi_mosi), .spi_miso(spi_miso), .spi_cs_n(spi_cs_n),
        .flash_sclk(flash_sclk), .flash_cs_n(flash_cs_n), .flash_mosi(flash_mosi), .flash_miso(flash_miso),
        .jtag_tck(jtag_tck), .jtag_tms(jtag_tms), .jtag_tdi(jtag_tdi), .jtag_tdo(jtag_tdo),
        .trap(trap)
    );

    // Idle tie-offs / simple loopbacks so the SoC does not stall.
    assign gpio_in    = gpio_out;
    assign spi_miso   = spi_mosi;
    assign flash_miso = 1'b1;
    assign uart_rx    = 1'b1;
    initial begin jtag_tck = 0; jtag_tms = 1; jtag_tdi = 0; end

    // 100 MHz clock, async reset released after 50 ns.
    initial clk = 0;
    always #5 clk = ~clk;
    initial begin rst_n = 0; #50 rst_n = 1; end

    // UART TX monitor: peek the SoC core APB UART writes and reassemble bytes.
    localparam int PASS_LEN = 19;          // "---FIRMWARE_PASS---"
    localparam int FAIL_LEN = 15;          // "---TEST_FAIL---"
    logic [8*PASS_LEN-1:0] win = '0;
    logic                  seen_uart = 0;

    always @(posedge clk) begin
        if (dut.u_soc_core.psel_uart && dut.u_soc_core.penable_uart
            && dut.u_soc_core.pready_uart) begin
            if (!seen_uart) begin
                seen_uart <= 1'b1;
                $display("[TB] First UART APB %0s addr=0x%08X",
                         dut.u_soc_core.pwrite_uart ? "WRITE" : "READ",
                         dut.u_soc_core.paddr_uart);
            end
            if (dut.u_soc_core.pwrite_uart && dut.u_soc_core.paddr_uart[7:0] == 8'h00) begin
                $write("%c", dut.u_soc_core.pwdata_uart[7:0]);
                $fflush();
                win = {win[8*(PASS_LEN-1)-1:0], dut.u_soc_core.pwdata_uart[7:0]};
                if (win == "---FIRMWARE_PASS---") begin
                    $display("\n[TB] PASS: firmware bring-up complete.");
                    $finish;
                end
                if (win[8*FAIL_LEN-1:0] == "---TEST_FAIL---")
                    $fatal(1, "[TB] FAIL: firmware reported failure.");
            end
        end
    end

    // A CPU trap during bring-up means a bad image or bad memory map.
    always @(posedge clk) if (trap) $fatal(1, "[TB] FAIL: CPU trap asserted.");

    // Post-reset diagnostics if the firmware never reaches the UART.
    initial begin
        wait (rst_n == 1'b1);
        #2000;
        if (!seen_uart) begin
            $display("[TB][DIAG] No UART APB traffic yet after reset.");
            $display("[TB][DIAG] dbg_cpu_pc = 0x%08X", dut.u_soc_core.dbg_cpu_pc);
            $display("[TB][DIAG] BootROM[0] = 0x%08X", dut.u_soc_core.u_bootrom.rom[0]);
        end
    end

    // Optional waveform dump.
    initial begin
`ifdef SOC_TB_VCD
        $dumpfile("sim/soc_top_bringup.vcd"); $dumpvars(0, soc_top_bringup_tb);
`else
        if ($test$plusargs("vcd")) begin
            $dumpfile("sim/soc_top_bringup.vcd");
            $dumpvars(0, soc_top_bringup_tb);
        end
`endif
    end

    initial begin
        #(TIMEOUT_NS);
        $fatal(1, "[TB] FAIL: simulation timeout.");
    end

endmodule
