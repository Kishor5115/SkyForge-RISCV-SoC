/*
 * Timer APB Testbench
 *
 * Standalone testbench for the SP804-inspired timer_apb peripheral.
 * Exercises all major features:
 *   1. Periodic mode with interrupt
 *   2. One-shot mode
 *   3. Free-running mode
 *   4. Interrupt clear
 *   5. Prescaler (÷16)
 *   6. 16-bit mode
 *   7. Background load
 *   8. MIS with interrupt disabled
 */

`timescale 1ns / 1ps

module timer_apb_tb;

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
    logic        timer_irq;

    // Test counters
    integer pass_count = 0;
    integer fail_count = 0;

    // Read data capture
    logic [31:0] rd_data;

    //==========================================================================
    // Register addresses
    //==========================================================================
    localparam [31:0] ADDR_LOAD         = 32'h00;
    localparam [31:0] ADDR_VALUE        = 32'h04;
    localparam [31:0] ADDR_CTRL         = 32'h08;
    localparam [31:0] ADDR_INTCLR       = 32'h0C;
    localparam [31:0] ADDR_RIS          = 32'h10;
    localparam [31:0] ADDR_MIS          = 32'h14;
    localparam [31:0] ADDR_BGLOAD       = 32'h18;
    localparam [31:0] ADDR_PRESCALE_CNT = 32'h1C;

    // CTRL register bits
    localparam [7:0] CTRL_ONESHOT  = 8'h01;
    localparam [7:0] CTRL_32BIT    = 8'h02;
    localparam [7:0] CTRL_PRE_16   = 8'h04;
    localparam [7:0] CTRL_PRE_256  = 8'h08;
    localparam [7:0] CTRL_INT_EN   = 8'h20;
    localparam [7:0] CTRL_PERIODIC = 8'h40;
    localparam [7:0] CTRL_ENABLE   = 8'h80;

    //==========================================================================
    // DUT
    //==========================================================================
    timer_apb u_dut (
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
        .timer_irq (timer_irq)
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

    //==========================================================================
    // Main test sequence
    //==========================================================================

    initial begin
        $dumpfile("sim/timer_apb_tb.vcd");
        $dumpvars(0, timer_apb_tb);

        // Initialize
        psel    = 0; penable = 0; pwrite = 0;
        paddr   = 0; pwdata  = 0; pstrb  = 0; pprot = 0;
        resetn  = 0;
        #100;
        resetn  = 1;
        @(posedge clk);

        $display("");
        $display("========================================");
        $display("  Timer APB Testbench");
        $display("========================================");
        $display("");

        //----------------------------------------------------------------------
        // TEST 1: Periodic mode with interrupt
        //----------------------------------------------------------------------
        $display("--- Test 1: Periodic mode with interrupt ---");

        // Load a small value for quick test
        apb_write(ADDR_LOAD, 32'd10);

        // Verify LOAD readback
        apb_read(ADDR_LOAD, rd_data);
        if (rd_data === 32'd10) begin
            $display("[PASS] LOAD readback = 0x%08h", rd_data);
            pass_count = pass_count + 1;
        end else begin
            $display("[FAIL] LOAD readback expected 0x0000000a, got 0x%08h", rd_data);
            fail_count = fail_count + 1;
        end

        // Start timer: 32-bit, periodic, interrupt enabled
        apb_write(ADDR_CTRL, CTRL_32BIT | CTRL_PERIODIC | CTRL_INT_EN | CTRL_ENABLE);

        // Read CTRL back
        apb_read(ADDR_CTRL, rd_data);
        if (rd_data === 32'hE2) begin
            $display("[PASS] CTRL readback = 0x%08h", rd_data);
            pass_count = pass_count + 1;
        end else begin
            $display("[FAIL] CTRL readback expected 0x000000e2, got 0x%08h", rd_data);
            fail_count = fail_count + 1;
        end

        // Wait for counter to count down (10 cycles + margin)
        repeat (15) @(posedge clk);

        // Check that interrupt fired
        apb_read(ADDR_RIS, rd_data);
        if (rd_data === 32'h1) begin
            $display("[PASS] RIS after wrap = 0x%08h", rd_data);
            pass_count = pass_count + 1;
        end else begin
            $display("[FAIL] RIS after wrap expected 0x00000001, got 0x%08h", rd_data);
            fail_count = fail_count + 1;
        end

        apb_read(ADDR_MIS, rd_data);
        if (rd_data === 32'h1) begin
            $display("[PASS] MIS after wrap = 0x%08h", rd_data);
            pass_count = pass_count + 1;
        end else begin
            $display("[FAIL] MIS after wrap expected 0x00000001, got 0x%08h", rd_data);
            fail_count = fail_count + 1;
        end

        if (timer_irq === 1'b1) begin
            $display("[PASS] timer_irq asserted");
            pass_count = pass_count + 1;
        end else begin
            $display("[FAIL] timer_irq expected 1, got %0b", timer_irq);
            fail_count = fail_count + 1;
        end

        // Verify counter reloaded
        apb_read(ADDR_VALUE, rd_data);
        $display("  [INFO] VALUE after reload: 0x%08h", rd_data);

        //----------------------------------------------------------------------
        // TEST 2: Interrupt clear
        //----------------------------------------------------------------------
        $display("");
        $display("--- Test 2: Interrupt clear ---");

        apb_write(ADDR_INTCLR, 32'h1);

        apb_read(ADDR_RIS, rd_data);
        if (rd_data === 32'h0) begin
            $display("[PASS] RIS after clear = 0x%08h", rd_data);
            pass_count = pass_count + 1;
        end else begin
            $display("[FAIL] RIS after clear expected 0x00000000, got 0x%08h", rd_data);
            fail_count = fail_count + 1;
        end

        if (timer_irq === 1'b0) begin
            $display("[PASS] timer_irq deasserted");
            pass_count = pass_count + 1;
        end else begin
            $display("[FAIL] timer_irq expected 0, got %0b", timer_irq);
            fail_count = fail_count + 1;
        end

        // Disable timer for next test
        apb_write(ADDR_CTRL, 32'h0);

        //----------------------------------------------------------------------
        // TEST 3: One-shot mode
        //----------------------------------------------------------------------
        $display("");
        $display("--- Test 3: One-shot mode ---");

        apb_write(ADDR_INTCLR, 32'h1);
        apb_write(ADDR_LOAD, 32'd5);

        // Start: 32-bit, one-shot, interrupt enabled
        apb_write(ADDR_CTRL, CTRL_32BIT | CTRL_ONESHOT | CTRL_INT_EN | CTRL_ENABLE);

        // Wait enough for countdown
        repeat (12) @(posedge clk);

        // Check counter stopped at 0
        apb_read(ADDR_VALUE, rd_data);
        if (rd_data === 32'h0) begin
            $display("[PASS] VALUE after one-shot = 0x%08h", rd_data);
            pass_count = pass_count + 1;
        end else begin
            $display("[FAIL] VALUE after one-shot expected 0x00000000, got 0x%08h", rd_data);
            fail_count = fail_count + 1;
        end

        // Check interrupt fired
        apb_read(ADDR_RIS, rd_data);
        if (rd_data === 32'h1) begin
            $display("[PASS] RIS after one-shot = 0x%08h", rd_data);
            pass_count = pass_count + 1;
        end else begin
            $display("[FAIL] RIS after one-shot expected 0x00000001, got 0x%08h", rd_data);
            fail_count = fail_count + 1;
        end

        // Wait more — counter should stay at 0
        repeat (10) @(posedge clk);
        apb_read(ADDR_VALUE, rd_data);
        if (rd_data === 32'h0) begin
            $display("[PASS] VALUE still 0 (stopped) = 0x%08h", rd_data);
            pass_count = pass_count + 1;
        end else begin
            $display("[FAIL] VALUE still 0 expected 0x00000000, got 0x%08h", rd_data);
            fail_count = fail_count + 1;
        end

        // Cleanup
        apb_write(ADDR_INTCLR, 32'h1);
        apb_write(ADDR_CTRL, 32'h0);

        //----------------------------------------------------------------------
        // TEST 4: Free-running mode (32-bit)
        //----------------------------------------------------------------------
        $display("");
        $display("--- Test 4: Free-running mode ---");

        apb_write(ADDR_INTCLR, 32'h1);
        apb_write(ADDR_LOAD, 32'd3);

        // Start: 32-bit, free-running (mode=0), interrupt enabled
        apb_write(ADDR_CTRL, CTRL_32BIT | CTRL_INT_EN | CTRL_ENABLE);

        // Wait for counter to reach 0 and wrap
        repeat (10) @(posedge clk);

        // After wrapping, free-running counter should reload to 0xFFFFFFFF
        apb_read(ADDR_RIS, rd_data);
        if (rd_data === 32'h1) begin
            $display("[PASS] RIS after free-run wrap = 0x%08h", rd_data);
            pass_count = pass_count + 1;
        end else begin
            $display("[FAIL] RIS after free-run wrap expected 0x00000001, got 0x%08h", rd_data);
            fail_count = fail_count + 1;
        end

        // Read VALUE — should be near 0xFFFFFFFF
        apb_read(ADDR_VALUE, rd_data);
        $display("  [INFO] VALUE after free-run wrap: 0x%08h", rd_data);

        // Cleanup
        apb_write(ADDR_INTCLR, 32'h1);
        apb_write(ADDR_CTRL, 32'h0);

        //----------------------------------------------------------------------
        // TEST 5: Prescaler ÷16
        //----------------------------------------------------------------------
        $display("");
        $display("--- Test 5: Prescaler div-16 ---");

        apb_write(ADDR_INTCLR, 32'h1);
        apb_write(ADDR_LOAD, 32'd2);

        // Start: 32-bit, periodic, prescale=÷16, interrupt enabled
        apb_write(ADDR_CTRL, CTRL_32BIT | CTRL_PERIODIC | CTRL_PRE_16 | CTRL_INT_EN | CTRL_ENABLE);

        // With prescale ÷16 and LOAD=2, counter ticks at clk/16
        // 10 clocks is < 1 prescale tick, so counter shouldn't have decremented much
        repeat (10) @(posedge clk);
        apb_read(ADDR_VALUE, rd_data);
        $display("  [INFO] VALUE after 10 clk with div16: 0x%08h", rd_data);

        // No interrupt yet
        apb_read(ADDR_RIS, rd_data);
        if (rd_data === 32'h0) begin
            $display("[PASS] RIS too early (div16) = 0x%08h", rd_data);
            pass_count = pass_count + 1;
        end else begin
            $display("[FAIL] RIS too early (div16) expected 0x00000000, got 0x%08h", rd_data);
            fail_count = fail_count + 1;
        end

        // Wait for full countdown: ~(2+1)*16 = 48 more clocks
        repeat (50) @(posedge clk);
        apb_read(ADDR_RIS, rd_data);
        if (rd_data === 32'h1) begin
            $display("[PASS] RIS after div16 countdown = 0x%08h", rd_data);
            pass_count = pass_count + 1;
        end else begin
            $display("[FAIL] RIS after div16 countdown expected 0x00000001, got 0x%08h", rd_data);
            fail_count = fail_count + 1;
        end

        // Cleanup
        apb_write(ADDR_INTCLR, 32'h1);
        apb_write(ADDR_CTRL, 32'h0);

        //----------------------------------------------------------------------
        // TEST 6: 16-bit mode
        //----------------------------------------------------------------------
        $display("");
        $display("--- Test 6: 16-bit mode ---");

        apb_write(ADDR_INTCLR, 32'h1);

        // Load a value that exceeds 16 bits — should be masked
        apb_write(ADDR_LOAD, 32'h0001_0005);

        // Start: 16-bit (timer_size=0), periodic, interrupt enabled
        apb_write(ADDR_CTRL, CTRL_PERIODIC | CTRL_INT_EN | CTRL_ENABLE);

        // Counter should start from 5 (0x10005 masked to 16-bit = 0x0005)
        @(posedge clk);
        apb_read(ADDR_VALUE, rd_data);
        $display("  [INFO] VALUE in 16-bit mode: 0x%08h", rd_data);

        // Wait for countdown
        repeat (10) @(posedge clk);

        apb_read(ADDR_RIS, rd_data);
        if (rd_data === 32'h1) begin
            $display("[PASS] RIS after 16-bit countdown = 0x%08h", rd_data);
            pass_count = pass_count + 1;
        end else begin
            $display("[FAIL] RIS after 16-bit countdown expected 0x00000001, got 0x%08h", rd_data);
            fail_count = fail_count + 1;
        end

        // Cleanup
        apb_write(ADDR_INTCLR, 32'h1);
        apb_write(ADDR_CTRL, 32'h0);

        //----------------------------------------------------------------------
        // TEST 7: Background load
        //----------------------------------------------------------------------
        $display("");
        $display("--- Test 7: Background load ---");

        apb_write(ADDR_INTCLR, 32'h1);
        apb_write(ADDR_LOAD, 32'd100);

        // Start: 32-bit, periodic, int enabled
        apb_write(ADDR_CTRL, CTRL_32BIT | CTRL_PERIODIC | CTRL_INT_EN | CTRL_ENABLE);

        // Let it run a few cycles
        repeat (5) @(posedge clk);

        // Read current value — should be counting down from 100
        apb_read(ADDR_VALUE, rd_data);
        $display("  [INFO] VALUE before BGLOAD: 0x%08h", rd_data);

        // Write BGLOAD — should NOT reset counter
        apb_write(ADDR_BGLOAD, 32'd20);

        // Read value — should still be counting from where it was
        apb_read(ADDR_VALUE, rd_data);
        $display("  [INFO] VALUE after BGLOAD: 0x%08h (should NOT be 20)", rd_data);

        // Verify LOAD register was updated
        apb_read(ADDR_LOAD, rd_data);
        if (rd_data === 32'd20) begin
            $display("[PASS] LOAD after BGLOAD = 0x%08h", rd_data);
            pass_count = pass_count + 1;
        end else begin
            $display("[FAIL] LOAD after BGLOAD expected 0x00000014, got 0x%08h", rd_data);
            fail_count = fail_count + 1;
        end

        // Cleanup
        apb_write(ADDR_INTCLR, 32'h1);
        apb_write(ADDR_CTRL, 32'h0);

        //----------------------------------------------------------------------
        // TEST 8: MIS (masked interrupt) with int_en=0
        //----------------------------------------------------------------------
        $display("");
        $display("--- Test 8: MIS with interrupt disabled ---");

        apb_write(ADDR_INTCLR, 32'h1);
        apb_write(ADDR_LOAD, 32'd5);

        // Start: 32-bit, periodic, interrupt DISABLED
        apb_write(ADDR_CTRL, CTRL_32BIT | CTRL_PERIODIC | CTRL_ENABLE);

        repeat (12) @(posedge clk);

        // RIS should be set, but MIS should be 0
        apb_read(ADDR_RIS, rd_data);
        if (rd_data === 32'h1) begin
            $display("[PASS] RIS (int disabled) = 0x%08h", rd_data);
            pass_count = pass_count + 1;
        end else begin
            $display("[FAIL] RIS (int disabled) expected 0x00000001, got 0x%08h", rd_data);
            fail_count = fail_count + 1;
        end

        apb_read(ADDR_MIS, rd_data);
        if (rd_data === 32'h0) begin
            $display("[PASS] MIS (int disabled) = 0x%08h", rd_data);
            pass_count = pass_count + 1;
        end else begin
            $display("[FAIL] MIS (int disabled) expected 0x00000000, got 0x%08h", rd_data);
            fail_count = fail_count + 1;
        end

        if (timer_irq === 1'b0) begin
            $display("[PASS] timer_irq deasserted (int disabled)");
            pass_count = pass_count + 1;
        end else begin
            $display("[FAIL] timer_irq expected 0, got %0b", timer_irq);
            fail_count = fail_count + 1;
        end

        // Cleanup
        apb_write(ADDR_INTCLR, 32'h1);
        apb_write(ADDR_CTRL, 32'h0);

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
        #100000;
        $display("");
        $display("[TIMEOUT] Simulation exceeded 100us — aborting.");
        $finish;
    end

endmodule
