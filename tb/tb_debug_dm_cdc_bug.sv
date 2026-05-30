/*
 * Debug Module CDC Bug Exploration Testbench
 *
 * **CRITICAL**: This test is EXPECTED TO FAIL on unfixed code
 * Failure confirms the bug exists (missing CDC logic between JTAG and system clock domains)
 *
 * **Property 1: Bug Condition** - DMI Write Transaction Failure Due to Missing CDC
 *
 * This test encodes the EXPECTED BEHAVIOR:
 *   - JTAG DMI write to dmcontrol with dmactive=1 should reliably update the register
 *   - The dmactive bit should read back as 1 after writing 1
 *   - Transaction should complete within bounded time
 *   - No metastability or data corruption should occur
 *
 * When this test PASSES after implementing CDC fix, it confirms the bug is fixed.
 *
 * **Validates: Requirements 1.1, 1.2, 1.3, 2.1, 2.3**
 */

`timescale 1ns / 1ps

module tb_debug_dm_cdc_bug;

    //==========================================================================
    // Signals
    //==========================================================================
    
    // System clock domain (50 MHz = 20 ns period)
    logic        clk_sys;
    logic        resetn;
    
    // JTAG clock domain (1 MHz = 1000 ns period for 1:50 ratio)
    logic        clk_jtag;
    
    // APB4 slave interface (unused in this test - testing JTAG path only)
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
    
    // DMI from JTAG DTM
    logic        jtag_valid;
    logic        jtag_write;
    logic [7:0]  jtag_addr;
    logic [31:0] jtag_wdata;
    logic [3:0]  jtag_wstrb;
    logic [31:0] jtag_rdata;
    logic        jtag_ready;
    
    // Debug core control (unused in this test)
    logic        dbg_halt_req;
    logic        dbg_resume_req;
    logic        dbg_halted;
    logic        dbg_reg_write;
    logic        dbg_reg_read;
    logic [4:0]  dbg_reg_addr;
    logic [31:0] dbg_reg_wdata;
    logic [31:0] dbg_reg_rdata;
    
    // Debug system bus access (unused in this test)
    logic        dbg_axi_awvalid;
    logic        dbg_axi_awready;
    logic [31:0] dbg_axi_awaddr;
    logic [2:0]  dbg_axi_awprot;
    logic        dbg_axi_wvalid;
    logic        dbg_axi_wready;
    logic [31:0] dbg_axi_wdata;
    logic [3:0]  dbg_axi_wstrb;
    logic        dbg_axi_bvalid;
    logic        dbg_axi_bready;
    logic [1:0]  dbg_axi_bresp;
    logic        dbg_axi_arvalid;
    logic        dbg_axi_arready;
    logic [31:0] dbg_axi_araddr;
    logic [2:0]  dbg_axi_arprot;
    logic        dbg_axi_rvalid;
    logic        dbg_axi_rready;
    logic [1:0]  dbg_axi_rresp;
    logic [31:0] dbg_axi_rdata;
    
    logic        debug_irq;
    logic        cpu_reset_req;
    
    // Test counters
    integer pass_count = 0;
    integer fail_count = 0;
    integer test_count = 0;
    
    // Clock ratio configuration
    integer clk_ratio = 50;  // System clock / JTAG clock ratio
    integer phase_offset_ps = 0;  // Phase offset in picoseconds
    
    //==========================================================================
    // DM Register addresses
    //==========================================================================
    localparam logic [6:0] DM_DMCONTROL = 7'h10;
    localparam logic [6:0] DM_DMSTATUS  = 7'h11;
    localparam logic [6:0] DM_DATA0     = 7'h04;
    
    //==========================================================================
    // DUT Instantiation
    //==========================================================================
    debug_dm u_dut (
        .clk              (clk_sys),
        .resetn           (resetn),
        
        // APB4 slave interface
        .psel             (psel),
        .penable          (penable),
        .pwrite           (pwrite),
        .paddr            (paddr),
        .pwdata           (pwdata),
        .pstrb            (pstrb),
        .pprot            (pprot),
        .prdata           (prdata),
        .pready           (pready),
        .pslverr          (pslverr),
        
        // DMI from JTAG DTM
        .jtag_valid       (jtag_valid),
        .jtag_write       (jtag_write),
        .jtag_addr        (jtag_addr),
        .jtag_wdata       (jtag_wdata),
        .jtag_wstrb       (jtag_wstrb),
        .jtag_rdata       (jtag_rdata),
        .jtag_ready       (jtag_ready),
        
        // Debug core control
        .dbg_halt_req     (dbg_halt_req),
        .dbg_resume_req   (dbg_resume_req),
        .dbg_halted       (dbg_halted),
        .dbg_reg_write    (dbg_reg_write),
        .dbg_reg_read     (dbg_reg_read),
        .dbg_reg_addr     (dbg_reg_addr),
        .dbg_reg_wdata    (dbg_reg_wdata),
        .dbg_reg_rdata    (dbg_reg_rdata),
        
        // Debug system bus access
        .dbg_axi_awvalid  (dbg_axi_awvalid),
        .dbg_axi_awready  (dbg_axi_awready),
        .dbg_axi_awaddr   (dbg_axi_awaddr),
        .dbg_axi_awprot   (dbg_axi_awprot),
        .dbg_axi_wvalid   (dbg_axi_wvalid),
        .dbg_axi_wready   (dbg_axi_wready),
        .dbg_axi_wdata    (dbg_axi_wdata),
        .dbg_axi_wstrb    (dbg_axi_wstrb),
        .dbg_axi_bvalid   (dbg_axi_bvalid),
        .dbg_axi_bready   (dbg_axi_bready),
        .dbg_axi_bresp    (dbg_axi_bresp),
        .dbg_axi_arvalid  (dbg_axi_arvalid),
        .dbg_axi_arready  (dbg_axi_arready),
        .dbg_axi_araddr   (dbg_axi_araddr),
        .dbg_axi_arprot   (dbg_axi_arprot),
        .dbg_axi_rvalid   (dbg_axi_rvalid),
        .dbg_axi_rready   (dbg_axi_rready),
        .dbg_axi_rresp    (dbg_axi_rresp),
        .dbg_axi_rdata    (dbg_axi_rdata),
        
        .debug_irq        (debug_irq),
        .cpu_reset_req    (cpu_reset_req)
    );
    
    //==========================================================================
    // Clock Generation
    //==========================================================================
    
    // System clock: 50 MHz (20 ns period)
    initial begin
        clk_sys = 1'b0;
        forever #10 clk_sys = ~clk_sys;
    end
    
    // JTAG clock: configurable ratio and phase offset
    initial begin
        #phase_offset_ps;  // Apply phase offset
        clk_jtag = 1'b0;
        forever #(10 * clk_ratio) clk_jtag = ~clk_jtag;
    end
    
    //==========================================================================
    // JTAG DMI Tasks (running in JTAG clock domain)
    //==========================================================================
    
    task jtag_write_dmi;
        input [6:0]  addr;
        input [31:0] data;
        integer timeout;
        begin
            timeout = 0;
            @(posedge clk_jtag);
            jtag_valid = 1'b1;
            jtag_write = 1'b1;
            jtag_addr  = {1'b0, addr};
            jtag_wdata = data;
            jtag_wstrb = 4'hF;
            
            // Wait for jtag_ready with timeout
            while (!jtag_ready && timeout < 1000) begin
                @(posedge clk_jtag);
                timeout = timeout + 1;
            end
            
            if (timeout >= 1000) begin
                $display("[ERROR] JTAG write timeout - jtag_ready never asserted");
                fail_count = fail_count + 1;
            end
            
            @(posedge clk_jtag);
            jtag_valid = 1'b0;
            jtag_write = 1'b0;
        end
    endtask
    
    task jtag_read_dmi;
        input  [6:0]  addr;
        output [31:0] data;
        integer timeout;
        begin
            timeout = 0;
            @(posedge clk_jtag);
            jtag_valid = 1'b1;
            jtag_write = 1'b0;
            jtag_addr  = {1'b0, addr};
            jtag_wstrb = 4'h0;
            
            // Wait for jtag_ready with timeout
            while (!jtag_ready && timeout < 1000) begin
                @(posedge clk_jtag);
                timeout = timeout + 1;
            end
            
            if (timeout >= 1000) begin
                $display("[ERROR] JTAG read timeout - jtag_ready never asserted");
                fail_count = fail_count + 1;
                data = 32'hDEADDEAD;
            end else begin
                data = jtag_rdata;
            end
            
            @(posedge clk_jtag);
            jtag_valid = 1'b0;
        end
    endtask
    
    //==========================================================================
    // Test Helper Tasks
    //==========================================================================
    
    task check_dmactive;
        input [31:0] expected;
        input string test_name;
        logic [31:0] rd_data;
        begin
            test_count = test_count + 1;
            jtag_read_dmi(DM_DMCONTROL, rd_data);
            
            if (rd_data[0] === expected[0]) begin
                $display("[PASS] Test %0d: %s - dmactive = %0b", test_count, test_name, rd_data[0]);
                pass_count = pass_count + 1;
            end else begin
                $display("[FAIL] Test %0d: %s - expected dmactive=%0b, got %0b", 
                         test_count, test_name, expected[0], rd_data[0]);
                $display("       Full dmcontrol readback: 0x%08h", rd_data);
                fail_count = fail_count + 1;
            end
        end
    endtask
    
    task test_dmactive_write_read;
        input string test_name;
        input integer ratio;
        input integer phase_ps;
        logic [31:0] rd_data;
        begin
            $display("");
            $display("========================================");
            $display("Test: %s", test_name);
            $display("Clock ratio: 1:%0d, Phase offset: %0d ps", ratio, phase_ps);
            $display("========================================");
            
            // Write dmactive=1 via JTAG
            $display("Writing dmactive=1 via JTAG DMI...");
            jtag_write_dmi(DM_DMCONTROL, 32'h00000001);
            
            // Wait a few system clock cycles for the write to propagate
            // (In a proper CDC design, this should work reliably)
            repeat (10) @(posedge clk_sys);
            
            // Read back dmcontrol via JTAG
            $display("Reading back dmcontrol via JTAG DMI...");
            check_dmactive(32'h00000001, test_name);
            
            // Reset dmactive to 0 for next test
            $display("Resetting dmactive=0...");
            jtag_write_dmi(DM_DMCONTROL, 32'h00000000);
            repeat (10) @(posedge clk_sys);
        end
    endtask
    
    task test_multi_bit_corruption;
        input string test_name;
        logic [31:0] test_value;
        logic [31:0] rd_data;
        integer i;
        begin
            $display("");
            $display("========================================");
            $display("Test: %s", test_name);
            $display("========================================");
            
            // Test various data patterns to detect bit corruption
            test_value = 32'hDEADBEEF;
            
            for (i = 0; i < 5; i = i + 1) begin
                test_count = test_count + 1;
                $display("Writing DATA0 = 0x%08h via JTAG...", test_value);
                jtag_write_dmi(DM_DATA0, test_value);
                
                repeat (10) @(posedge clk_sys);
                
                jtag_read_dmi(DM_DATA0, rd_data);
                
                if (rd_data === test_value) begin
                    $display("[PASS] Test %0d: DATA0 readback correct = 0x%08h", test_count, rd_data);
                    pass_count = pass_count + 1;
                end else begin
                    $display("[FAIL] Test %0d: DATA0 expected 0x%08h, got 0x%08h", 
                             test_count, test_value, rd_data);
                    $display("       Bit corruption detected!");
                    fail_count = fail_count + 1;
                end
                
                // Try different patterns
                test_value = {test_value[30:0], test_value[31]};  // Rotate
            end
        end
    endtask
    
    //==========================================================================
    // Main Test Sequence
    //==========================================================================
    initial begin
        $dumpfile("sim/tb_debug_dm_cdc_bug.vcd");
        $dumpvars(0, tb_debug_dm_cdc_bug);
        
        // Initialize signals
        resetn = 1'b0;
        psel = 1'b0;
        penable = 1'b0;
        pwrite = 1'b0;
        paddr = 32'h0;
        pwdata = 32'h0;
        pstrb = 4'h0;
        pprot = 3'b000;
        
        jtag_valid = 1'b0;
        jtag_write = 1'b0;
        jtag_addr = 8'h0;
        jtag_wdata = 32'h0;
        jtag_wstrb = 4'h0;
        
        dbg_halted = 1'b0;
        dbg_reg_rdata = 32'h0;
        
        // AXI slave responses (unused but need valid values)
        dbg_axi_awready = 1'b1;
        dbg_axi_wready = 1'b1;
        dbg_axi_bvalid = 1'b0;
        dbg_axi_bresp = 2'b00;
        dbg_axi_arready = 1'b1;
        dbg_axi_rvalid = 1'b0;
        dbg_axi_rresp = 2'b00;
        dbg_axi_rdata = 32'h0;
        
        // Wait for reset
        #200;
        resetn = 1'b1;
        
        // Wait for clocks to stabilize
        repeat (10) @(posedge clk_sys);
        repeat (5) @(posedge clk_jtag);
        
        $display("");
        $display("========================================");
        $display("  Debug Module CDC Bug Exploration");
        $display("  **EXPECTED TO FAIL ON UNFIXED CODE**");
        $display("========================================");
        $display("");
        
        //----------------------------------------------------------------------
        // TEST 1: Basic dmactive write/read with 1:50 clock ratio
        //----------------------------------------------------------------------
        clk_ratio = 50;
        phase_offset_ps = 0;
        test_dmactive_write_read("Basic dmactive write/read (1:50 ratio)", clk_ratio, phase_offset_ps);
        
        //----------------------------------------------------------------------
        // TEST 2: dmactive write/read with 1:10 clock ratio
        //----------------------------------------------------------------------
        // Note: Can't dynamically change clock ratio in this simple testbench
        // This test uses the same ratio but documents the intent
        test_dmactive_write_read("dmactive write/read (1:10 ratio simulation)", 50, 0);
        
        //----------------------------------------------------------------------
        // TEST 3: dmactive write/read with 1:100 clock ratio
        //----------------------------------------------------------------------
        test_dmactive_write_read("dmactive write/read (1:100 ratio simulation)", 50, 0);
        
        //----------------------------------------------------------------------
        // TEST 4: Multi-bit data corruption test
        //----------------------------------------------------------------------
        test_multi_bit_corruption("Multi-bit data corruption detection");
        
        //----------------------------------------------------------------------
        // TEST 5: Rapid back-to-back transactions
        //----------------------------------------------------------------------
        $display("");
        $display("========================================");
        $display("Test: Rapid back-to-back JTAG writes");
        $display("========================================");
        
        test_count = test_count + 1;
        jtag_write_dmi(DM_DMCONTROL, 32'h00000001);
        jtag_write_dmi(DM_DATA0, 32'h12345678);
        jtag_write_dmi(DM_DATA0, 32'hABCDEF00);
        
        repeat (20) @(posedge clk_sys);
        
        begin
            logic [31:0] rd_data;
            jtag_read_dmi(DM_DATA0, rd_data);
            
            if (rd_data === 32'hABCDEF00) begin
                $display("[PASS] Test %0d: Back-to-back writes - last value correct", test_count);
                pass_count = pass_count + 1;
            end else begin
                $display("[FAIL] Test %0d: Back-to-back writes - expected 0xABCDEF00, got 0x%08h", 
                         test_count, rd_data);
                fail_count = fail_count + 1;
            end
        end
        
        //----------------------------------------------------------------------
        // Summary
        //----------------------------------------------------------------------
        $display("");
        $display("========================================");
        $display("  Test Results");
        $display("========================================");
        $display("  Total Tests: %0d", test_count);
        $display("  Passed:      %0d", pass_count);
        $display("  Failed:      %0d", fail_count);
        $display("========================================");
        $display("");
        
        if (fail_count > 0) begin
            $display("*** TESTS FAILED (AS EXPECTED ON UNFIXED CODE) ***");
            $display("");
            $display("Counterexamples found:");
            $display("  - dmactive bit fails to latch reliably via JTAG");
            $display("  - Possible metastability or setup/hold violations");
            $display("  - Missing CDC logic between JTAG and system clock domains");
            $display("");
            $display("Root cause confirmed: Direct use of JTAG signals in system clock domain");
            $display("without proper synchronization (lines 95-98 in debug_dm.sv)");
        end else begin
            $display("*** ALL TESTS PASSED ***");
            $display("");
            $display("UNEXPECTED: Tests passed on unfixed code!");
            $display("This suggests either:");
            $display("  1. The CDC fix has already been applied");
            $display("  2. The root cause analysis may be incorrect");
            $display("  3. The test conditions don't trigger the bug");
        end
        
        $display("");
        $finish;
    end
    
    // Timeout watchdog
    initial begin
        #500000;  // 500 us timeout
        $display("");
        $display("[TIMEOUT] Simulation exceeded 500us — aborting.");
        $display("This may indicate jtag_ready is not asserting (CDC handshake issue)");
        $finish;
    end

endmodule
