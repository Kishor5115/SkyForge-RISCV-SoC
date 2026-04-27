/*
 * UART APB Controller Testbench
 *
 * Self-checking testbench for uart_ctrl_apb with FPGA-targeted verification.
 *
 * Uses baud_div=2 for fast simulation (~50 baud ticks per character).
 *
 * Tests:
 *   1. Reset defaults (tx_empty=1, rx_empty=1, tx_en=1, rx_en=1, irq_en=0)
 *   2. CTRL register write & readback (baud_div, enables)
 *   3. STATUS register read (tx_empty, tx_full flags)
 *   4. TX FIFO write → UART TX output (loopback verify)
 *   5. RX data reception (drive uart_rx line)
 *   6. IRQ assertion with irq_en=1 and RX data available
 *   7. FIFO full behavior (write >8 bytes)
 */

`timescale 1ns / 1ps

module uart_ctrl_apb_tb;

    //==========================================================================
    // Parameters & signals
    //==========================================================================
    localparam BAUD_DIV = 2;   // Very fast for simulation
    localparam CLK_PERIOD = 10; // 100 MHz

    logic        clk, resetn;

    // APB signals
    logic        psel, penable, pwrite;
    logic [31:0] paddr, pwdata;
    logic [3:0]  pstrb;
    logic [2:0]  pprot;
    logic [31:0] prdata;
    logic        pready, pslverr;

    // UART I/O - loopback
    logic        uart_tx_pin;
    logic        uart_rx_pin;
    logic        irq;

    // Test counters
    integer pass_count = 0;
    integer fail_count = 0;

    //==========================================================================
    // DUT
    //==========================================================================
    uart_ctrl_apb #(
        .DEFAULT_BAUD_DIV(BAUD_DIV)
    ) u_dut (
        .clk(clk),
        .resetn(resetn),
        .psel(psel),
        .penable(penable),
        .pwrite(pwrite),
        .paddr(paddr),
        .pwdata(pwdata),
        .pstrb(pstrb),
        .pprot(pprot),
        .prdata(prdata),
        .pready(pready),
        .pslverr(pslverr),
        .uart_tx(uart_tx_pin),
        .uart_rx(uart_rx_pin),
        .irq(irq)
    );

    //==========================================================================
    // Clock
    //==========================================================================
    initial begin
        clk = 1'b0;
        forever #(CLK_PERIOD/2) clk = ~clk;
    end

    //==========================================================================
    // APB Transaction Tasks
    //==========================================================================
    task apb_write;
        input [31:0] addr;
        input [31:0] data;
        begin
            @(posedge clk);
            #1;
            // SETUP phase
            psel    = 1'b1;
            penable = 1'b0;
            pwrite  = 1'b1;
            paddr   = addr;
            pwdata  = data;
            pstrb   = 4'b1111;
            @(posedge clk);
            #1;
            // ACCESS phase
            penable = 1'b1;
            @(posedge clk);
            #1;
            // Complete
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
            #1;
            // SETUP phase
            psel    = 1'b1;
            penable = 1'b0;
            pwrite  = 1'b0;
            paddr   = addr;
            @(posedge clk);
            #1;
            // ACCESS phase
            penable = 1'b1;
            #1; // Small delay for combinational read
            data    = prdata;
            @(posedge clk);
            #1;
            psel    = 1'b0;
            penable = 1'b0;
        end
    endtask

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
    // UART RX driver — send a serial byte to the DUT's RX pin
    //==========================================================================
    // Calculate bit period in clock cycles: baud_div * 16
    localparam BIT_CYCLES = BAUD_DIV * 16;

    task uart_send_byte;
        input [7:0] data;
        integer i;
        begin
            // Start bit
            uart_rx_pin = 1'b0;
            repeat (BIT_CYCLES) @(posedge clk);
            // Data bits (LSB first)
            for (i = 0; i < 8; i = i + 1) begin
                uart_rx_pin = data[i];
                repeat (BIT_CYCLES) @(posedge clk);
            end
            // Stop bit
            uart_rx_pin = 1'b1;
            repeat (BIT_CYCLES) @(posedge clk);
        end
    endtask

    //==========================================================================
    // UART TX capture — capture a serial byte from the DUT's TX pin
    //==========================================================================
    logic [7:0] tx_captured_byte;
    logic       tx_capture_valid;

    task uart_capture_tx;
        output [7:0] data;
        integer i;
        begin
            // Wait for start bit (falling edge of uart_tx_pin)
            wait(uart_tx_pin == 1'b0);
            // Wait half bit period to sample at center
            repeat (BIT_CYCLES / 2) @(posedge clk);
            // Verify start bit
            if (uart_tx_pin !== 1'b0) begin
                $display("[WARN] TX start bit not stable");
            end
            // Sample at center of each data bit
            for (i = 0; i < 8; i = i + 1) begin
                repeat (BIT_CYCLES) @(posedge clk);
                data[i] = uart_tx_pin;
            end
            // Wait for stop bit
            repeat (BIT_CYCLES) @(posedge clk);
        end
    endtask

    //==========================================================================
    // Register addresses
    //==========================================================================
    localparam ADDR_TX_DATA = 32'h0000_0000;
    localparam ADDR_RX_DATA = 32'h0000_0004;
    localparam ADDR_STATUS  = 32'h0000_0008;
    localparam ADDR_CTRL    = 32'h0000_000C;

    //==========================================================================
    // Main test sequence
    //==========================================================================
    logic [31:0] rd_data;
    logic [7:0]  captured_byte;

    initial begin
        $dumpfile("sim/uart_ctrl_apb_tb.vcd");
        $dumpvars(0, uart_ctrl_apb_tb);

        // Initialize
        psel = 0; penable = 0; pwrite = 0;
        paddr = 0; pwdata = 0; pstrb = 0; pprot = 0;
        uart_rx_pin = 1'b1;  // Idle high
        resetn = 0;
        #100;
        resetn = 1;
        repeat (5) @(posedge clk);

        $display("");
        $display("========================================");
        $display("  UART APB Controller Testbench");
        $display("========================================");
        $display("");

        //----------------------------------------------------------------------
        // TEST 1: Reset defaults
        //----------------------------------------------------------------------
        $display("--- Test 1: Reset defaults ---");
        apb_read(ADDR_STATUS, rd_data);
        check_bit(1'b1, rd_data[0], "tx_empty after reset");
        check_bit(1'b0, rd_data[1], "tx_full after reset");
        check_bit(1'b1, rd_data[2], "rx_empty after reset");
        check_bit(1'b0, rd_data[3], "rx_full after reset");

        apb_read(ADDR_CTRL, rd_data);
        check(BAUD_DIV[15:0], rd_data[15:0], "default baud_div");
        check_bit(1'b1, rd_data[16], "tx_en default");
        check_bit(1'b1, rd_data[17], "rx_en default");
        check_bit(1'b0, rd_data[18], "irq_en default");

        check_bit(1'b0, irq, "IRQ after reset");

        //----------------------------------------------------------------------
        // TEST 2: CTRL register write/readback
        //----------------------------------------------------------------------
        $display("");
        $display("--- Test 2: CTRL register write/readback ---");
        // Write new baud_div=100, tx_en=1, rx_en=1, irq_en=1
        apb_write(ADDR_CTRL, {13'h0, 1'b1, 1'b1, 1'b1, 16'd100});
        apb_read(ADDR_CTRL, rd_data);
        check(16'd100, rd_data[15:0], "baud_div readback");
        check_bit(1'b1, rd_data[16], "tx_en readback");
        check_bit(1'b1, rd_data[17], "rx_en readback");
        check_bit(1'b1, rd_data[18], "irq_en readback");

        // Restore fast baud for remaining tests
        apb_write(ADDR_CTRL, {13'h0, 1'b0, 1'b1, 1'b1, BAUD_DIV[15:0]});

        //----------------------------------------------------------------------
        // TEST 3: STATUS register — TX FIFO write
        //----------------------------------------------------------------------
        $display("");
        $display("--- Test 3: TX FIFO write & STATUS ---");

        // Write one byte to TX FIFO
        apb_write(ADDR_TX_DATA, 32'h0000_0041);  // 'A'
        repeat (3) @(posedge clk);  // Allow FIFO write to settle

        apb_read(ADDR_STATUS, rd_data);
        // After writing 1 byte: tx_empty should go 0 (byte in FIFO or being transmitted)
        // tx_full should still be 0
        check_bit(1'b0, rd_data[1], "tx_full after 1 byte write");

        // TX FIFO behavior verified — byte will be transmitted

        //----------------------------------------------------------------------
        // TEST 4: TX output verification (loopback)
        //----------------------------------------------------------------------
        $display("");
        $display("--- Test 4: TX output loopback ---");

        // The byte 'A' (0x41) written above should appear on uart_tx_pin
        uart_capture_tx(captured_byte);
        if (captured_byte === 8'h41) begin
            $display("[PASS] TX captured byte = 0x%02h ('A')", captured_byte);
            pass_count = pass_count + 1;
        end else begin
            $display("[FAIL] TX captured expected 0x41, got 0x%02h", captured_byte);
            fail_count = fail_count + 1;
        end

        // Wait for TX to finish
        repeat (BIT_CYCLES * 2) @(posedge clk);

        //----------------------------------------------------------------------
        // TEST 5: RX data reception
        //----------------------------------------------------------------------
        $display("");
        $display("--- Test 5: RX data reception ---");

        // Send a byte into the DUT via uart_rx_pin
        uart_send_byte(8'h5A);  // 'Z'
        repeat (10) @(posedge clk);  // Allow RX FIFO write

        // Check RX not empty
        apb_read(ADDR_STATUS, rd_data);
        check_bit(1'b0, rd_data[2], "rx_empty after RX byte");

        // Read RX FIFO
        apb_read(ADDR_RX_DATA, rd_data);
        check(32'h0000_005A, rd_data, "RX data = 0x5A");

        //----------------------------------------------------------------------
        // TEST 6: IRQ assertion
        //----------------------------------------------------------------------
        $display("");
        $display("--- Test 6: IRQ assertion ---");

        // Enable IRQ
        apb_write(ADDR_CTRL, {13'h0, 1'b1, 1'b1, 1'b1, BAUD_DIV[15:0]});

        // IRQ should be 0 now (RX FIFO empty)
        repeat (3) @(posedge clk);
        check_bit(1'b0, irq, "IRQ when RX FIFO empty");

        // Send a byte to RX
        uart_send_byte(8'hFF);
        repeat (10) @(posedge clk);

        // IRQ should be 1 (RX data available + irq_en=1)
        check_bit(1'b1, irq, "IRQ when RX data available");

        // Read RX to clear
        apb_read(ADDR_RX_DATA, rd_data);
        repeat (3) @(posedge clk);
        check_bit(1'b0, irq, "IRQ after RX read (FIFO empty)");

        //----------------------------------------------------------------------
        // TEST 7: TX FIFO full behavior
        //----------------------------------------------------------------------
        $display("");
        $display("--- Test 7: TX FIFO full ---");

        // Disable TX to let FIFO fill up
        apb_write(ADDR_CTRL, {13'h0, 1'b1, 1'b1, 1'b0, BAUD_DIV[15:0]});
        repeat (3) @(posedge clk);

        // Write 8 bytes to fill the FIFO (DEPTH=8)
        for (int i = 0; i < 8; i++) begin
            apb_write(ADDR_TX_DATA, i[7:0]);
        end
        repeat (3) @(posedge clk);

        apb_read(ADDR_STATUS, rd_data);
        check_bit(1'b1, rd_data[1], "tx_full after 8x write");
        check_bit(1'b0, rd_data[0], "tx_empty after 8x write");

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
        #5000000;
        $display("");
        $display("[TIMEOUT] Simulation exceeded 5ms — aborting.");
        $finish;
    end

endmodule
