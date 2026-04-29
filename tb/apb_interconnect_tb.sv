/*
 * APB Interconnect Testbench
 *
 * Self-checking testbench for the APB address decoder/mux.
 * Tests:
 *   1. UART address decode  (0x20000xxx → psel_uart)
 *   2. Timer address decode (0x20001xxx → psel_timer)
 *   3. GPIO address decode  (0x20002xxx → psel_gpio)
 *   4. Invalid address      → pslverr, pready stays high
 *   5. Response mux         (correct prdata from selected slave)
 *   6. Signal broadcasting  (penable, pwrite, paddr, pwdata to all slaves)
 */

`timescale 1ns / 1ps

module apb_interconnect_tb;

    //==========================================================================
    // Signals
    //==========================================================================
    logic        clk;
    logic        resetn;

    // Master-side (from bridge)
    logic        psel_i;
    logic        penable_i;
    logic        pwrite_i;
    logic [31:0] paddr_i;
    logic [31:0] pwdata_i;
    logic [3:0]  pstrb_i;
    logic [2:0]  pprot_i;
    logic [31:0] prdata_o;
    logic        pready_o;
    logic        pslverr_o;

    // UART slave-side
    logic        psel_uart, penable_uart, pwrite_uart, pready_uart, pslverr_uart;
    logic [31:0] paddr_uart, pwdata_uart, prdata_uart;
    logic [3:0]  pstrb_uart;
    logic [2:0]  pprot_uart;

    // Timer slave-side
    logic        psel_timer, penable_timer, pwrite_timer, pready_timer, pslverr_timer;
    logic [31:0] paddr_timer, pwdata_timer, prdata_timer;
    logic [3:0]  pstrb_timer;
    logic [2:0]  pprot_timer;

    // GPIO slave-side
    logic        psel_gpio, penable_gpio, pwrite_gpio, pready_gpio, pslverr_gpio;
    logic [31:0] paddr_gpio, pwdata_gpio, prdata_gpio;
    logic [3:0]  pstrb_gpio;
    logic [2:0]  pprot_gpio;

    // SPI slave-side
    logic        psel_spi, penable_spi, pwrite_spi, pready_spi, pslverr_spi;
    logic [31:0] paddr_spi, pwdata_spi, prdata_spi;
    logic [3:0]  pstrb_spi;
    logic [2:0]  pprot_spi;

    // Debug slave-side
    logic        psel_debug, penable_debug, pwrite_debug, pready_debug, pslverr_debug;
    logic [31:0] paddr_debug, pwdata_debug, prdata_debug;
    logic [3:0]  pstrb_debug;
    logic [2:0]  pprot_debug;

    // Test counters
    integer pass_count = 0;
    integer fail_count = 0;

    //==========================================================================
    // DUT
    //==========================================================================
    apb_interconnect u_dut (
        .clk(clk),
        .resetn(resetn),
        .psel_i(psel_i),
        .penable_i(penable_i),
        .pwrite_i(pwrite_i),
        .paddr_i(paddr_i),
        .pwdata_i(pwdata_i),
        .pstrb_i(pstrb_i),
        .pprot_i(pprot_i),
        .prdata_o(prdata_o),
        .pready_o(pready_o),
        .pslverr_o(pslverr_o),

        .psel_uart(psel_uart),
        .penable_uart(penable_uart),
        .pwrite_uart(pwrite_uart),
        .paddr_uart(paddr_uart),
        .pwdata_uart(pwdata_uart),
        .pstrb_uart(pstrb_uart),
        .pprot_uart(pprot_uart),
        .prdata_uart(prdata_uart),
        .pready_uart(pready_uart),
        .pslverr_uart(pslverr_uart),

        .psel_timer(psel_timer),
        .penable_timer(penable_timer),
        .pwrite_timer(pwrite_timer),
        .paddr_timer(paddr_timer),
        .pwdata_timer(pwdata_timer),
        .pstrb_timer(pstrb_timer),
        .pprot_timer(pprot_timer),
        .prdata_timer(prdata_timer),
        .pready_timer(pready_timer),
        .pslverr_timer(pslverr_timer),

        .psel_gpio(psel_gpio),
        .penable_gpio(penable_gpio),
        .pwrite_gpio(pwrite_gpio),
        .paddr_gpio(paddr_gpio),
        .pwdata_gpio(pwdata_gpio),
        .pstrb_gpio(pstrb_gpio),
        .pprot_gpio(pprot_gpio),
        .prdata_gpio(prdata_gpio),
        .pready_gpio(pready_gpio),
        .pslverr_gpio(pslverr_gpio),

        .psel_spi(psel_spi),
        .penable_spi(penable_spi),
        .pwrite_spi(pwrite_spi),
        .paddr_spi(paddr_spi),
        .pwdata_spi(pwdata_spi),
        .pstrb_spi(pstrb_spi),
        .pprot_spi(pprot_spi),
        .prdata_spi(prdata_spi),
        .pready_spi(pready_spi),
        .pslverr_spi(pslverr_spi),

        .psel_debug(psel_debug),
        .penable_debug(penable_debug),
        .pwrite_debug(pwrite_debug),
        .paddr_debug(paddr_debug),
        .pwdata_debug(pwdata_debug),
        .pstrb_debug(pstrb_debug),
        .pprot_debug(pprot_debug),
        .prdata_debug(prdata_debug),
        .pready_debug(pready_debug),
        .pslverr_debug(pslverr_debug)
    );

    //==========================================================================
    // Clock generation — 100 MHz
    //==========================================================================
    initial begin
        clk = 1'b0;
        forever #5 clk = ~clk;
    end

    // Stub slave responses (simulate peripherals responding)
    assign prdata_uart  = 32'hA001_DAA1;
    assign pready_uart  = 1'b1;
    assign pslverr_uart = 1'b0;

    assign prdata_timer = 32'hB002_DAA2;
    assign pready_timer = 1'b1;
    assign pslverr_timer = 1'b0;

    assign prdata_gpio  = 32'hC003_DAA3;
    assign pready_gpio  = 1'b1;
    assign pslverr_gpio = 1'b0;

    assign prdata_spi   = 32'hD004_DAA4;
    assign pready_spi   = 1'b1;
    assign pslverr_spi  = 1'b0;

    assign prdata_debug  = 32'hE005_DAA5;
    assign pready_debug  = 1'b1;
    assign pslverr_debug = 1'b0;

    // Check helper
    task check;
        input [31:0] expected;
        input [31:0] actual;
        input [255:0] msg;
        begin
            if (actual === expected) begin
                $display("[PASS] %0s = 0x%08h", msg, actual);
                pass_count = pass_count + 1;
            end else begin
                $display("[FAIL] %0s expected 0x%08h, got 0x%08h", msg, expected, actual);
                fail_count = fail_count + 1;
            end
        end
    endtask

    task check_bit;
        input expected;
        input actual;
        input [255:0] msg;
        begin
            if (actual === expected) begin
                $display("[PASS] %0s = %0b", msg, actual);
                pass_count = pass_count + 1;
            end else begin
                $display("[FAIL] %0s expected %0b, got %0b", msg, expected, actual);
                fail_count = fail_count + 1;
            end
        end
    endtask

    //==========================================================================
    // Main test sequence
    //==========================================================================
    initial begin
        $dumpfile("sim/apb_interconnect_tb.vcd");
        $dumpvars(0, apb_interconnect_tb);

        // Initialize
        psel_i    = 0; penable_i = 0; pwrite_i = 0;
        paddr_i   = 0; pwdata_i  = 0; pstrb_i  = 0; pprot_i = 0;
        resetn    = 0;
        #100;
        resetn    = 1;
        @(posedge clk);

        $display("");
        $display("========================================");
        $display("  APB Interconnect Testbench");
        $display("========================================");
        $display("");

        //----------------------------------------------------------------------
        // TEST 1: UART address decode
        //----------------------------------------------------------------------
        $display("--- Test 1: UART address decode ---");
        psel_i  = 1'b1;
        paddr_i = 32'h2000_0000;
        #1;
        check_bit(1'b1, psel_uart,  "psel_uart for UART addr");
        check_bit(1'b0, psel_timer, "psel_timer for UART addr");
        check_bit(1'b0, psel_gpio,  "psel_gpio for UART addr");
        check(32'hA001_DAA1, prdata_o, "prdata_o mux to UART");
        psel_i = 1'b0;
        @(posedge clk);

        // UART upper boundary
        psel_i  = 1'b1;
        paddr_i = 32'h2000_0FFC;
        #1;
        check_bit(1'b1, psel_uart, "psel_uart for UART upper bound");
        psel_i = 1'b0;
        @(posedge clk);

        //----------------------------------------------------------------------
        // TEST 2: Timer address decode
        //----------------------------------------------------------------------
        $display("");
        $display("--- Test 2: Timer address decode ---");
        psel_i  = 1'b1;
        paddr_i = 32'h2000_1000;
        #1;
        check_bit(1'b0, psel_uart,  "psel_uart for Timer addr");
        check_bit(1'b1, psel_timer, "psel_timer for Timer addr");
        check_bit(1'b0, psel_gpio,  "psel_gpio for Timer addr");
        check(32'hB002_DAA2, prdata_o, "prdata_o mux to Timer");
        psel_i = 1'b0;
        @(posedge clk);

        //----------------------------------------------------------------------
        // TEST 3: GPIO address decode
        //----------------------------------------------------------------------
        $display("");
        $display("--- Test 3: GPIO address decode ---");
        psel_i  = 1'b1;
        paddr_i = 32'h2000_2004;
        #1;
        check_bit(1'b0, psel_uart,  "psel_uart for GPIO addr");
        check_bit(1'b0, psel_timer, "psel_timer for GPIO addr");
        check_bit(1'b1, psel_gpio,  "psel_gpio for GPIO addr");
        check(32'hC003_DAA3, prdata_o, "prdata_o mux to GPIO");
        psel_i = 1'b0;
        @(posedge clk);

        //----------------------------------------------------------------------
        // TEST 4: Invalid address → pslverr
        //----------------------------------------------------------------------
        $display("");
        $display("--- Test 4: Invalid address (decode error) ---");
        psel_i  = 1'b1;
        paddr_i = 32'h2000_F000;  // Outside all peripheral ranges
        #1;
        check_bit(1'b0, psel_uart,  "psel_uart for invalid addr");
        check_bit(1'b0, psel_timer, "psel_timer for invalid addr");
        check_bit(1'b0, psel_gpio,  "psel_gpio for invalid addr");
        check_bit(1'b1, pslverr_o,  "pslverr for invalid addr");
        check_bit(1'b1, pready_o,   "pready for invalid addr (no hang)");
        psel_i = 1'b0;
        @(posedge clk);

        //----------------------------------------------------------------------
        // TEST 5: Signal broadcasting (pwdata, pwrite, penable to all)
        //----------------------------------------------------------------------
        $display("");
        $display("--- Test 5: Signal broadcasting ---");
        psel_i    = 1'b1;
        penable_i = 1'b1;
        pwrite_i  = 1'b1;
        paddr_i   = 32'h2000_1008;
        pwdata_i  = 32'hCAFE_BABE;
        pstrb_i   = 4'b1010;
        pprot_i   = 3'b010;
        #1;
        // All slaves should see the same signals regardless of which is selected
        check(32'hCAFE_BABE, pwdata_uart,  "pwdata broadcast to UART");
        check(32'hCAFE_BABE, pwdata_timer, "pwdata broadcast to Timer");
        check(32'hCAFE_BABE, pwdata_gpio,  "pwdata broadcast to GPIO");
        check_bit(1'b1, penable_uart,  "penable broadcast to UART");
        check_bit(1'b1, penable_timer, "penable broadcast to Timer");
        check_bit(1'b1, penable_gpio,  "penable broadcast to GPIO");
        check_bit(1'b1, pwrite_uart,   "pwrite broadcast to UART");
        check_bit(1'b1, pwrite_timer,  "pwrite broadcast to Timer");
        check_bit(1'b1, pwrite_gpio,   "pwrite broadcast to GPIO");
        // Only Timer should have PSEL
        check_bit(1'b0, psel_uart,  "psel_uart (Timer selected)");
        check_bit(1'b1, psel_timer, "psel_timer (Timer selected)");
        check_bit(1'b0, psel_gpio,  "psel_gpio (Timer selected)");

        psel_i = 1'b0; penable_i = 1'b0; pwrite_i = 1'b0;
        @(posedge clk);

        //----------------------------------------------------------------------
        // TEST 6: PSTRB and PPROT passthrough
        //----------------------------------------------------------------------
        $display("");
        $display("--- Test 6: PSTRB and PPROT passthrough ---");
        psel_i  = 1'b1;
        paddr_i = 32'h2000_2000;
        pstrb_i = 4'b0110;
        pprot_i = 3'b101;
        #1;
        if (pstrb_gpio === 4'b0110) begin
            $display("[PASS] pstrb passthrough to GPIO = 4'b%04b", pstrb_gpio);
            pass_count = pass_count + 1;
        end else begin
            $display("[FAIL] pstrb passthrough to GPIO expected 4'b0110, got 4'b%04b", pstrb_gpio);
            fail_count = fail_count + 1;
        end
        if (pprot_gpio === 3'b101) begin
            $display("[PASS] pprot passthrough to GPIO = 3'b%03b", pprot_gpio);
            pass_count = pass_count + 1;
        end else begin
            $display("[FAIL] pprot passthrough to GPIO expected 3'b101, got 3'b%03b", pprot_gpio);
            fail_count = fail_count + 1;
        end
        psel_i = 1'b0;
        @(posedge clk);

        //----------------------------------------------------------------------
        // Summary
        //----------------------------------------------------------------------
        $display("");
        $display("========================================");
        $display("  Results: %0d PASSED, %0d FAILED", pass_count, fail_count);
        $display("========================================");
        $display("");

        if (fail_count == 0)
            $display("*** ALL TESTS PASSED ***");
        else
            $display("*** SOME TESTS FAILED ***");

        $display("");
        $finish;
    end

    // Timeout watchdog
    initial begin
        #50000;
        $display("");
        $display("[TIMEOUT] Simulation exceeded 50us — aborting.");
        $finish;
    end

endmodule
