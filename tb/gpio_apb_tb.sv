/*
 * GPIO APB Testbench
 *
 * Standalone testbench for the PL061/SiFive FE310-inspired gpio_apb peripheral.
 * Exercises all major features:
 *   1.  Reset state verification
 *   2.  Output enable & output value
 *   3.  Input read
 *   4.  Rising-edge interrupt
 *   5.  Falling-edge interrupt
 *   6.  High-level interrupt
 *   7.  Low-level interrupt
 *   8.  Interrupt clear (W1C)
 *   9.  Combined gpio_irq output
 *   10. Output XOR (inversion)
 *   11. PSLVERR on invalid address
 *   12. Byte-lane writes (PSTRB)
 */

`timescale 1ns / 1ps

module gpio_apb_tb;

    //==========================================================================
    // Signals
    //==========================================================================
    logic        clk;
    logic        resetn;

    // APB signals
    logic        psel;
    logic        penable;
    logic        pwrite;
    logic [31:0] paddr;
    logic [31:0] pwdata;
    logic [3:0]  pstrb;
    logic [2:0]  pprot;
    logic [31:0] prdata;
    logic        pready;
    logic        pslverr;

    // GPIO signals
    logic [31:0] gpio_in;
    logic [31:0] gpio_out;
    logic [31:0] gpio_oe;
    logic [31:0] gpio_pue;
    logic [31:0] gpio_ds;
    logic [31:0] iof_en;
    logic [31:0] iof_sel;
    logic        gpio_irq;

    // Test counters
    integer pass_count = 0;
    integer fail_count = 0;

    // Read data capture
    logic [31:0] rd_data;

    //==========================================================================
    // Register addresses
    //==========================================================================
    localparam [31:0] ADDR_INPUT_VAL  = 32'h00;
    localparam [31:0] ADDR_INPUT_EN   = 32'h04;
    localparam [31:0] ADDR_OUTPUT_EN  = 32'h08;
    localparam [31:0] ADDR_OUTPUT_VAL = 32'h0C;
    localparam [31:0] ADDR_PUE        = 32'h10;
    localparam [31:0] ADDR_DS         = 32'h14;
    localparam [31:0] ADDR_RISE_IE    = 32'h18;
    localparam [31:0] ADDR_RISE_IP    = 32'h1C;
    localparam [31:0] ADDR_FALL_IE    = 32'h20;
    localparam [31:0] ADDR_FALL_IP    = 32'h24;
    localparam [31:0] ADDR_HIGH_IE    = 32'h28;
    localparam [31:0] ADDR_HIGH_IP    = 32'h2C;
    localparam [31:0] ADDR_LOW_IE     = 32'h30;
    localparam [31:0] ADDR_LOW_IP     = 32'h34;
    localparam [31:0] ADDR_OUT_XOR    = 32'h38;
    localparam [31:0] ADDR_IOF_EN     = 32'h3C;
    localparam [31:0] ADDR_IOF_SEL    = 32'h40;

    //==========================================================================
    // DUT
    //==========================================================================
    gpio_apb #(
        .GPIO_WIDTH(32)
    ) u_dut (
        .clk       (clk),
        .resetn    (resetn),
        .psel      (psel),
        .penable   (penable),
        .pwrite    (pwrite),
        .paddr     (paddr),
        .pwdata    (pwdata),
        .pstrb     (pstrb),
        .pprot     (pprot),
        .prdata    (prdata),
        .pready    (pready),
        .pslverr   (pslverr),
        .gpio_in   (gpio_in),
        .gpio_out  (gpio_out),
        .gpio_oe   (gpio_oe),
        .gpio_pue  (gpio_pue),
        .gpio_ds   (gpio_ds),
        .iof_en    (iof_en),
        .iof_sel   (iof_sel),
        .gpio_irq  (gpio_irq)
    );

    //==========================================================================
    // Clock generation — 100 MHz (10 ns period)
    //==========================================================================
    initial begin
        clk = 1'b0;
        forever #5 clk = ~clk;
    end

    //==========================================================================
    // APB Tasks
    //==========================================================================
    task apb_write;
        input [31:0] addr;
        input [31:0] data;
        begin
            @(posedge clk);
            psel    = 1'b1;
            penable = 1'b0;
            pwrite  = 1'b1;
            paddr   = addr;
            pwdata  = data;
            pstrb   = 4'hF;
            pprot   = 3'b000;

            @(posedge clk);
            penable = 1'b1;

            @(posedge clk);
            psel    = 1'b0;
            penable = 1'b0;
            pwrite  = 1'b0;
        end
    endtask

    task apb_write_strb;
        input [31:0] addr;
        input [31:0] data;
        input [3:0]  strb;
        begin
            @(posedge clk);
            psel    = 1'b1;
            penable = 1'b0;
            pwrite  = 1'b1;
            paddr   = addr;
            pwdata  = data;
            pstrb   = strb;
            pprot   = 3'b000;

            @(posedge clk);
            penable = 1'b1;

            @(posedge clk);
            psel    = 1'b0;
            penable = 1'b0;
            pwrite  = 1'b0;
        end
    endtask

    task apb_read;
        input  [31:0] addr;
        output [31:0] data;
        begin
            @(posedge clk);
            psel    = 1'b1;
            penable = 1'b0;
            pwrite  = 1'b0;
            paddr   = addr;
            pstrb   = 4'h0;
            pprot   = 3'b000;

            @(posedge clk);
            penable = 1'b1;

            @(posedge clk);
            data = prdata;
            psel    = 1'b0;
            penable = 1'b0;
        end
    endtask

    // Check helper
    task check;
        input [31:0] expected;
        input [31:0] actual;
        input [255:0] msg;  // String label
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

    //==========================================================================
    // Main test sequence
    //==========================================================================
    initial begin
        $dumpfile("sim/gpio_apb_tb.vcd");
        $dumpvars(0, gpio_apb_tb);

        // Initialize
        psel    = 0; penable = 0; pwrite = 0;
        paddr   = 0; pwdata  = 0; pstrb  = 0; pprot = 0;
        gpio_in = 32'h0;
        resetn  = 0;
        #100;
        resetn  = 1;
        @(posedge clk);

        $display("");
        $display("========================================");
        $display("  GPIO APB Testbench");
        $display("========================================");
        $display("");

        //----------------------------------------------------------------------
        // TEST 1: Reset state — all registers should read 0
        //----------------------------------------------------------------------
        $display("--- Test 1: Reset state ---");

        apb_read(ADDR_INPUT_VAL,  rd_data); check(32'h0, rd_data, "INPUT_VAL reset");
        apb_read(ADDR_INPUT_EN,   rd_data); check(32'h0, rd_data, "INPUT_EN reset");
        apb_read(ADDR_OUTPUT_EN,  rd_data); check(32'h0, rd_data, "OUTPUT_EN reset");
        apb_read(ADDR_OUTPUT_VAL, rd_data); check(32'h0, rd_data, "OUTPUT_VAL reset");
        apb_read(ADDR_RISE_IE,    rd_data); check(32'h0, rd_data, "RISE_IE reset");
        apb_read(ADDR_RISE_IP,    rd_data); check(32'h0, rd_data, "RISE_IP reset");
        apb_read(ADDR_OUT_XOR,    rd_data); check(32'h0, rd_data, "OUT_XOR reset");

        //----------------------------------------------------------------------
        // TEST 2: Output enable and output value
        //----------------------------------------------------------------------
        $display("");
        $display("--- Test 2: Output direction & write ---");

        apb_write(ADDR_OUTPUT_EN, 32'h0000_00FF);  // Enable lower 8 pins as output
        apb_read(ADDR_OUTPUT_EN, rd_data);
        check(32'h0000_00FF, rd_data, "OUTPUT_EN readback");

        apb_write(ADDR_OUTPUT_VAL, 32'h0000_00A5);
        apb_read(ADDR_OUTPUT_VAL, rd_data);
        check(32'h0000_00A5, rd_data, "OUTPUT_VAL readback");

        // Verify gpio_out and gpio_oe hardware outputs
        @(posedge clk);
        check(32'h0000_00A5, gpio_out, "gpio_out pin value");
        check(32'h0000_00FF, gpio_oe,  "gpio_oe pin value");

        //----------------------------------------------------------------------
        // TEST 3: Input read
        //----------------------------------------------------------------------
        $display("");
        $display("--- Test 3: Input read ---");

        apb_write(ADDR_INPUT_EN, 32'hFFFF_0000);  // Enable upper 16 pins as input
        gpio_in = 32'hDEAD_0000;

        // Wait for 2-stage synchronizer (3 cycles)
        repeat (4) @(posedge clk);

        apb_read(ADDR_INPUT_VAL, rd_data);
        check(32'hDEAD_0000, rd_data, "INPUT_VAL synced");

        // Pins not enabled should read 0
        gpio_in = 32'hDEAD_BEEF;
        repeat (4) @(posedge clk);
        apb_read(ADDR_INPUT_VAL, rd_data);
        check(32'hDEAD_0000, rd_data, "INPUT_VAL masked by INPUT_EN");

        //----------------------------------------------------------------------
        // TEST 4: Rising-edge interrupt
        //----------------------------------------------------------------------
        $display("");
        $display("--- Test 4: Rising-edge interrupt ---");

        // Enable rising-edge interrupt on pin 0
        apb_write(ADDR_RISE_IE, 32'h0000_0001);

        // Drive pin 0 low first, then high
        gpio_in[0] = 1'b0;
        repeat (4) @(posedge clk);  // Let synchronizer settle

        gpio_in[0] = 1'b1;
        repeat (4) @(posedge clk);  // Edge should be detected

        apb_read(ADDR_RISE_IP, rd_data);
        check(32'h0000_0001, rd_data[0], "RISE_IP[0] after low->high");

        // gpio_irq should be asserted
        if (gpio_irq === 1'b1) begin
            $display("[PASS] gpio_irq asserted on rising edge");
            pass_count = pass_count + 1;
        end else begin
            $display("[FAIL] gpio_irq expected 1 after rising edge, got %0b", gpio_irq);
            fail_count = fail_count + 1;
        end

        // Clear pending
        apb_write(ADDR_RISE_IP, 32'h0000_0001);

        //----------------------------------------------------------------------
        // TEST 5: Falling-edge interrupt
        //----------------------------------------------------------------------
        $display("");
        $display("--- Test 5: Falling-edge interrupt ---");

        apb_write(ADDR_FALL_IE, 32'h0000_0001);

        // Pin 0 is currently high from test 4
        gpio_in[0] = 1'b0;
        repeat (4) @(posedge clk);

        apb_read(ADDR_FALL_IP, rd_data);
        check(32'h0000_0001, rd_data[0], "FALL_IP[0] after high->low");

        // Clear
        apb_write(ADDR_FALL_IP, 32'h0000_0001);
        apb_write(ADDR_FALL_IE, 32'h0);

        //----------------------------------------------------------------------
        // TEST 6: High-level interrupt
        //----------------------------------------------------------------------
        $display("");
        $display("--- Test 6: High-level interrupt ---");

        apb_write(ADDR_HIGH_IE, 32'h0000_0004);  // Enable on pin 2
        gpio_in[2] = 1'b1;
        repeat (4) @(posedge clk);

        apb_read(ADDR_HIGH_IP, rd_data);
        check(32'h1, rd_data[2], "HIGH_IP[2] while pin high");

        // Clear and disable
        apb_write(ADDR_HIGH_IP, 32'h0000_0004);
        apb_write(ADDR_HIGH_IE, 32'h0);
        gpio_in[2] = 1'b0;
        repeat (4) @(posedge clk);

        //----------------------------------------------------------------------
        // TEST 7: Low-level interrupt
        //----------------------------------------------------------------------
        $display("");
        $display("--- Test 7: Low-level interrupt ---");

        apb_write(ADDR_LOW_IE, 32'h0000_0008);  // Enable on pin 3
        gpio_in[3] = 1'b0;
        repeat (4) @(posedge clk);

        apb_read(ADDR_LOW_IP, rd_data);
        check(32'h1, rd_data[3], "LOW_IP[3] while pin low");

        // Clear and disable
        apb_write(ADDR_LOW_IP, 32'h0000_0008);
        apb_write(ADDR_LOW_IE, 32'h0);

        //----------------------------------------------------------------------
        // TEST 8: Interrupt clear (W1C)
        //----------------------------------------------------------------------
        $display("");
        $display("--- Test 8: Interrupt clear (W1C) ---");

        // Re-trigger a rising edge on pin 0
        apb_write(ADDR_RISE_IE, 32'h0000_0001);
        gpio_in[0] = 1'b0;
        repeat (4) @(posedge clk);
        gpio_in[0] = 1'b1;
        repeat (4) @(posedge clk);

        apb_read(ADDR_RISE_IP, rd_data);
        check(32'h0000_0001, rd_data[0], "RISE_IP[0] before clear");

        // W1C: write 1 to clear
        apb_write(ADDR_RISE_IP, 32'h0000_0001);
        // Need a couple cycles for the change to take effect after the edge stops
        gpio_in[0] = 1'b1;  // Keep stable (no new edge)
        repeat (2) @(posedge clk);

        apb_read(ADDR_RISE_IP, rd_data);
        check(32'h0, rd_data[0], "RISE_IP[0] after W1C");

        //----------------------------------------------------------------------
        // TEST 9: Combined gpio_irq output
        //----------------------------------------------------------------------
        $display("");
        $display("--- Test 9: Combined gpio_irq output ---");

        // Disable all interrupt enables
        apb_write(ADDR_RISE_IE, 32'h0);
        apb_write(ADDR_FALL_IE, 32'h0);
        apb_write(ADDR_HIGH_IE, 32'h0);
        apb_write(ADDR_LOW_IE, 32'h0);
        // Clear all pendings
        apb_write(ADDR_RISE_IP, 32'hFFFF_FFFF);
        apb_write(ADDR_FALL_IP, 32'hFFFF_FFFF);
        apb_write(ADDR_HIGH_IP, 32'hFFFF_FFFF);
        apb_write(ADDR_LOW_IP, 32'hFFFF_FFFF);
        repeat (4) @(posedge clk);

        // gpio_irq should be 0 now
        if (gpio_irq === 1'b0) begin
            $display("[PASS] gpio_irq deasserted when no enabled pending");
            pass_count = pass_count + 1;
        end else begin
            $display("[FAIL] gpio_irq expected 0 when no enabled pending, got %0b", gpio_irq);
            fail_count = fail_count + 1;
        end

        //----------------------------------------------------------------------
        // TEST 10: Output XOR (inversion)
        //----------------------------------------------------------------------
        $display("");
        $display("--- Test 10: Output XOR (inversion) ---");

        apb_write(ADDR_OUTPUT_VAL, 32'h0000_00FF);
        apb_write(ADDR_OUT_XOR,    32'h0000_00FF);
        @(posedge clk);

        check(32'h0000_0000, gpio_out, "gpio_out with XOR inversion");

        // Clear XOR
        apb_write(ADDR_OUT_XOR, 32'h0);
        @(posedge clk);
        check(32'h0000_00FF, gpio_out, "gpio_out after clearing XOR");

        //----------------------------------------------------------------------
        // TEST 11: PSLVERR on invalid address
        //----------------------------------------------------------------------
        $display("");
        $display("--- Test 11: PSLVERR on invalid address ---");

        // Read from an undefined offset (0x50)
        @(posedge clk);
        psel    = 1'b1;
        penable = 1'b0;
        pwrite  = 1'b0;
        paddr   = 32'h50;
        pstrb   = 4'h0;
        pprot   = 3'b000;

        @(posedge clk);
        penable = 1'b1;

        @(posedge clk);
        if (pslverr === 1'b1) begin
            $display("[PASS] PSLVERR asserted on invalid address 0x50");
            pass_count = pass_count + 1;
        end else begin
            $display("[FAIL] PSLVERR expected 1 on invalid address 0x50, got %0b", pslverr);
            fail_count = fail_count + 1;
        end
        psel    = 1'b0;
        penable = 1'b0;

        //----------------------------------------------------------------------
        // TEST 12: Byte-lane writes (PSTRB)
        //----------------------------------------------------------------------
        $display("");
        $display("--- Test 12: Byte-lane writes (PSTRB) ---");

        // First write a known value
        apb_write(ADDR_OUTPUT_VAL, 32'hAABB_CCDD);
        apb_read(ADDR_OUTPUT_VAL, rd_data);
        check(32'hAABB_CCDD, rd_data, "OUTPUT_VAL before partial write");

        // Write only byte 1 (bits [15:8]) with 0x55
        apb_write_strb(ADDR_OUTPUT_VAL, 32'h0000_5500, 4'b0010);
        apb_read(ADDR_OUTPUT_VAL, rd_data);
        check(32'hAABB_55DD, rd_data, "OUTPUT_VAL after PSTRB byte1 write");

        // Write only byte 3 (bits [31:24]) with 0x11
        apb_write_strb(ADDR_OUTPUT_VAL, 32'h1100_0000, 4'b1000);
        apb_read(ADDR_OUTPUT_VAL, rd_data);
        check(32'h11BB_55DD, rd_data, "OUTPUT_VAL after PSTRB byte3 write");

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
        #200000;
        $display("");
        $display("[TIMEOUT] Simulation exceeded 200us — aborting.");
        $finish;
    end

endmodule
