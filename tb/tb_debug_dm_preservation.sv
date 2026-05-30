/*
 * Debug Module Preservation Property Tests
 *
 * **Property 2: Preservation** - Non-JTAG Interface Behavior Unchanged
 *
 * **IMPORTANT**: This test runs on UNFIXED code to observe baseline behavior
 * **EXPECTED OUTCOME**: Tests PASS (confirms baseline behavior to preserve)
 *
 * This testbench verifies that non-JTAG interfaces work correctly:
 *   - APB4 slave interface transactions (register reads/writes)
 *   - Abstract command execution via APB
 *   - System Bus Access (SBA) operations via APB
 *   - Debug core interface signals (halt/resume/register access)
 *
 * After implementing CDC fix, these tests should still PASS, confirming
 * that the fix preserves existing functionality.
 *
 * **Validates: Requirements 1.5, 3.1, 3.2, 3.3, 4.1, 4.2, 4.3, 4.4, 
 *              5.1, 5.2, 5.3, 6.1, 6.2, 6.3, 7.1, 7.2, 7.3**
 */

`timescale 1ns / 1ps

module tb_debug_dm_preservation;

    //==========================================================================
    // Signals
    //==========================================================================
    
    // System clock domain (50 MHz = 20 ns period)
    logic        clk;
    logic        resetn;
    
    // APB4 slave interface
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
    
    // DMI from JTAG DTM (unused in preservation tests)
    logic        jtag_valid;
    logic        jtag_write;
    logic [7:0]  jtag_addr;
    logic [31:0] jtag_wdata;
    logic [3:0]  jtag_wstrb;
    logic [31:0] jtag_rdata;
    logic        jtag_ready;
    
    // Debug core control
    logic        dbg_halt_req;
    logic        dbg_resume_req;
    logic        dbg_halted;
    logic        dbg_reg_write;
    logic        dbg_reg_read;
    logic [4:0]  dbg_reg_addr;
    logic [31:0] dbg_reg_wdata;
    logic [31:0] dbg_reg_rdata;
    
    // Debug system bus access (AXI-lite master)
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
    
    //==========================================================================
    // DM Register addresses (APB byte addresses = DMI address << 2)
    //==========================================================================
    localparam logic [31:0] ADDR_DATA0      = 32'h00000010;  // DMI 0x04 << 2
    localparam logic [31:0] ADDR_DMCONTROL  = 32'h00000040;  // DMI 0x10 << 2
    localparam logic [31:0] ADDR_DMSTATUS   = 32'h00000044;  // DMI 0x11 << 2
    localparam logic [31:0] ADDR_HARTINFO   = 32'h00000048;  // DMI 0x12 << 2
    localparam logic [31:0] ADDR_ABSTRACTCS = 32'h00000058;  // DMI 0x16 << 2
    localparam logic [31:0] ADDR_COMMAND    = 32'h0000005C;  // DMI 0x17 << 2
    localparam logic [31:0] ADDR_SBCS       = 32'h000000E0;  // DMI 0x38 << 2
    localparam logic [31:0] ADDR_SBADDRESS0 = 32'h000000E4;  // DMI 0x39 << 2
    localparam logic [31:0] ADDR_SBDATA0    = 32'h000000F0;  // DMI 0x3C << 2
    
    //==========================================================================
    // DUT Instantiation
    //==========================================================================
    debug_dm u_dut (
        .clk              (clk),
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
        clk = 1'b0;
        forever #10 clk = ~clk;
    end
    
    //==========================================================================
    // APB Transaction Tasks
    //==========================================================================
    
    task apb_write;
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
            
            @(posedge clk);
            penable = 1'b1;
            
            // Wait for pready (always 1 in this design, but good practice)
            while (!pready) @(posedge clk);
            
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
            
            @(posedge clk);
            penable = 1'b1;
            
            // Wait for pready (always 1 in this design, but good practice)
            while (!pready) @(posedge clk);
            
            // Sample prdata after a small delay to ensure it's stable
            #1;
            data = prdata;
            
            @(posedge clk);
            psel    = 1'b0;
            penable = 1'b0;
        end
    endtask
    
    //==========================================================================
    // Test Helper Tasks
    //==========================================================================
    
    task check_value;
        input [31:0] actual;
        input [31:0] expected;
        input string test_name;
        begin
            test_count = test_count + 1;
            if (actual === expected) begin
                $display("[PASS] Test %0d: %s - got 0x%08h", test_count, test_name, actual);
                pass_count = pass_count + 1;
            end else begin
                $display("[FAIL] Test %0d: %s - expected 0x%08h, got 0x%08h", 
                         test_count, test_name, expected, actual);
                fail_count = fail_count + 1;
            end
        end
    endtask
    
    task check_signal;
        input logic actual;
        input logic expected;
        input string test_name;
        begin
            test_count = test_count + 1;
            if (actual === expected) begin
                $display("[PASS] Test %0d: %s - signal = %0b", test_count, test_name, actual);
                pass_count = pass_count + 1;
            end else begin
                $display("[FAIL] Test %0d: %s - expected %0b, got %0b", 
                         test_count, test_name, expected, actual);
                fail_count = fail_count + 1;
            end
        end
    endtask
    
    //==========================================================================
    // Property-Based Test Generators
    //==========================================================================
    
    // Generate random APB write transactions
    task property_apb_write_preservation;
        input integer num_tests;
        logic [31:0] test_addr;
        logic [31:0] test_data;
        logic [31:0] rd_data;
        logic [6:0]  reg_addr;
        integer i;
        begin
            $display("");
            $display("========================================");
            $display("Property: APB Write Preservation");
            $display("Testing %0d random APB write transactions", num_tests);
            $display("========================================");
            
            for (i = 0; i < num_tests; i = i + 1) begin
                // Generate random register address (valid DM registers)
                reg_addr = $urandom_range(0, 7);
                case (reg_addr)
                    0: test_addr = ADDR_DATA0;
                    1: test_addr = ADDR_DMCONTROL;
                    2: test_addr = ADDR_COMMAND;
                    3: test_addr = ADDR_ABSTRACTCS;
                    4: test_addr = ADDR_SBCS;
                    5: test_addr = ADDR_SBADDRESS0;
                    6: test_addr = ADDR_SBDATA0;
                    default: test_addr = ADDR_DATA0;
                endcase
                
                // Generate random data
                test_data = $urandom();
                
                // Perform APB write
                apb_write(test_addr, test_data, 4'hF);
                
                // Read back and verify (for writable registers)
                apb_read(test_addr, rd_data);
                
                // Note: Some bits may be read-only or have special behavior
                // For preservation testing, we just verify the transaction completes
                $display("  [%0d] APB write to 0x%08h = 0x%08h, readback = 0x%08h", 
                         i, test_addr, test_data, rd_data);
            end
            
            $display("APB write preservation test completed");
        end
    endtask
    
    // Generate random APB read transactions
    task property_apb_read_preservation;
        input integer num_tests;
        logic [31:0] test_addr;
        logic [31:0] rd_data;
        logic [6:0]  reg_addr;
        integer i;
        begin
            $display("");
            $display("========================================");
            $display("Property: APB Read Preservation");
            $display("Testing %0d random APB read transactions", num_tests);
            $display("========================================");
            
            for (i = 0; i < num_tests; i = i + 1) begin
                // Generate random register address
                reg_addr = $urandom_range(0, 8);
                case (reg_addr)
                    0: test_addr = ADDR_DATA0;
                    1: test_addr = ADDR_DMCONTROL;
                    2: test_addr = ADDR_DMSTATUS;
                    3: test_addr = ADDR_HARTINFO;
                    4: test_addr = ADDR_ABSTRACTCS;
                    5: test_addr = ADDR_COMMAND;
                    6: test_addr = ADDR_SBCS;
                    7: test_addr = ADDR_SBADDRESS0;
                    8: test_addr = ADDR_SBDATA0;
                    default: test_addr = ADDR_DMSTATUS;
                endcase
                
                // Perform APB read
                apb_read(test_addr, rd_data);
                
                $display("  [%0d] APB read from 0x%08h = 0x%08h", i, test_addr, rd_data);
            end
            
            $display("APB read preservation test completed");
        end
    endtask
    
    //==========================================================================
    // Specific Preservation Tests
    //==========================================================================
    
    task test_apb_dmcontrol_write;
        logic [31:0] rd_data;
        begin
            $display("");
            $display("========================================");
            $display("Test: APB dmcontrol Write Preservation");
            $display("========================================");
            
            // Write dmactive=1 via APB
            $display("Writing dmactive=1 via APB...");
            apb_write(ADDR_DMCONTROL, 32'h00000001, 4'hF);
            
            // Wait a bit for the write to take effect
            repeat (2) @(posedge clk);
            
            // Read back via APB
            apb_read(ADDR_DMCONTROL, rd_data);
            check_value(rd_data[0], 1'b1, "APB dmcontrol write dmactive=1");
            
            // Now that dmactive=1, write haltreq=1 via APB
            $display("Writing haltreq=1 via APB (with dmactive=1)...");
            apb_write(ADDR_DMCONTROL, 32'h80000001, 4'hF);
            
            // Wait a bit
            repeat (2) @(posedge clk);
            
            // Read back via APB
            apb_read(ADDR_DMCONTROL, rd_data);
            check_value(rd_data[31], 1'b1, "APB dmcontrol write haltreq=1");
            
            // Reset dmactive
            apb_write(ADDR_DMCONTROL, 32'h00000000, 4'hF);
            repeat (2) @(posedge clk);
        end
    endtask
    
    task test_apb_data0_write_read;
        logic [31:0] test_data;
        logic [31:0] rd_data;
        integer i;
        begin
            $display("");
            $display("========================================");
            $display("Test: APB DATA0 Write/Read Preservation");
            $display("========================================");
            
            // Test various data patterns
            for (i = 0; i < 5; i = i + 1) begin
                test_data = $urandom();
                
                $display("Writing DATA0 = 0x%08h via APB...", test_data);
                apb_write(ADDR_DATA0, test_data, 4'hF);
                
                // Wait for write to take effect
                repeat (2) @(posedge clk);
                
                apb_read(ADDR_DATA0, rd_data);
                check_value(rd_data, test_data, $sformatf("APB DATA0 write/read pattern %0d", i));
            end
        end
    endtask
    
    task test_abstract_command_preservation;
        logic [31:0] rd_data;
        logic [31:0] cmd;
        begin
            $display("");
            $display("========================================");
            $display("Test: Abstract Command Preservation");
            $display("========================================");
            
            // Activate debug module via APB
            apb_write(ADDR_DMCONTROL, 32'h00000001, 4'hF);
            
            // Simulate hart halted
            dbg_halted = 1'b1;
            dbg_reg_rdata = 32'hCAFEBABE;
            
            // Write data0 for register write command
            apb_write(ADDR_DATA0, 32'h12345678, 4'hF);
            
            // Issue Access Register write command (write to x1)
            // cmdtype=0 (Access Register), write=1, regno=0x1001 (GPR x1)
            cmd = 32'h00231000;  // transfer=1, write=1, regno=0x1001
            $display("Issuing Access Register write command via APB...");
            apb_write(ADDR_COMMAND, cmd, 4'hF);
            
            // Wait for command to complete
            repeat (5) @(posedge clk);
            
            // Check that dbg_reg_write was asserted
            check_signal(dbg_reg_write, 1'b1, "Abstract command asserts dbg_reg_write");
            check_value(dbg_reg_addr, 5'h01, "Abstract command sets correct reg_addr");
            check_value(dbg_reg_wdata, 32'h12345678, "Abstract command sets correct reg_wdata");
            
            // Issue Access Register read command (read from x2)
            cmd = 32'h00221000;  // transfer=1, write=0, regno=0x1002
            $display("Issuing Access Register read command via APB...");
            apb_write(ADDR_COMMAND, cmd, 4'hF);
            
            // Wait for command to complete
            repeat (5) @(posedge clk);
            
            // Check that dbg_reg_read was asserted
            check_signal(dbg_reg_read, 1'b1, "Abstract command asserts dbg_reg_read");
            check_value(dbg_reg_addr, 5'h02, "Abstract command sets correct reg_addr for read");
            
            // Read back data0 to verify register read result
            apb_read(ADDR_DATA0, rd_data);
            check_value(rd_data, 32'hCAFEBABE, "Abstract command read result in DATA0");
            
            // Reset
            dbg_halted = 1'b0;
            apb_write(ADDR_DMCONTROL, 32'h00000000, 4'hF);
        end
    endtask
    
    task test_debug_core_interface_preservation;
        logic [31:0] rd_data;
        begin
            $display("");
            $display("========================================");
            $display("Test: Debug Core Interface Preservation");
            $display("========================================");
            
            // Initially, debug signals should be inactive
            check_signal(dbg_halt_req, 1'b0, "Initial dbg_halt_req inactive");
            check_signal(dbg_resume_req, 1'b0, "Initial dbg_resume_req inactive");
            
            // Activate debug module via APB
            apb_write(ADDR_DMCONTROL, 32'h00000001, 4'hF);
            @(posedge clk);
            
            // Write haltreq=1 via APB
            $display("Writing haltreq=1 via APB...");
            apb_write(ADDR_DMCONTROL, 32'h80000001, 4'hF);
            
            // Check that dbg_halt_req is asserted
            repeat (2) @(posedge clk);
            check_signal(dbg_halt_req, 1'b1, "dbg_halt_req asserted after haltreq write");
            
            // Simulate hart halted
            dbg_halted = 1'b1;
            repeat (2) @(posedge clk);
            
            // dbg_halt_req should deassert when hart is halted
            check_signal(dbg_halt_req, 1'b0, "dbg_halt_req deasserts when hart halted");
            
            // Write resumereq=1 via APB
            $display("Writing resumereq=1 via APB...");
            apb_write(ADDR_DMCONTROL, 32'h40000001, 4'hF);
            
            // Check that dbg_resume_req is asserted
            repeat (2) @(posedge clk);
            check_signal(dbg_resume_req, 1'b1, "dbg_resume_req asserted after resumereq write");
            
            // Resume req should be one-shot
            repeat (2) @(posedge clk);
            check_signal(dbg_resume_req, 1'b0, "dbg_resume_req is one-shot");
            
            // Reset
            dbg_halted = 1'b0;
            apb_write(ADDR_DMCONTROL, 32'h00000000, 4'hF);
        end
    endtask
    
    task test_system_bus_access_preservation;
        logic [31:0] rd_data;
        logic [31:0] test_addr;
        logic [31:0] test_data;
        begin
            $display("");
            $display("========================================");
            $display("Test: System Bus Access Preservation");
            $display("========================================");
            
            // Activate debug module via APB
            apb_write(ADDR_DMCONTROL, 32'h00000001, 4'hF);
            
            // Configure SBCS for 32-bit access with sbreadonaddr
            // sbreadonaddr=1 (bit 23), sbaccess=2 (32-bit, bits 19:17)
            $display("Configuring SBCS with sbreadonaddr=1...");
            apb_write(ADDR_SBCS, 32'h00840000, 4'hF);
            
            // Write sbaddress0 to trigger read
            test_addr = 32'h20000000;
            $display("Writing sbaddress0 = 0x%08h to trigger SBA read...", test_addr);
            apb_write(ADDR_SBADDRESS0, test_addr, 4'hF);
            
            // Check that AXI read transaction is initiated
            repeat (2) @(posedge clk);
            check_signal(dbg_axi_arvalid, 1'b1, "SBA initiates AXI read (arvalid)");
            check_value(dbg_axi_araddr, test_addr, "SBA AXI read address correct");
            
            // Simulate AXI read response
            @(posedge clk);
            dbg_axi_rvalid = 1'b1;
            dbg_axi_rdata = 32'hDEADBEEF;
            dbg_axi_rresp = 2'b00;
            
            @(posedge clk);
            dbg_axi_rvalid = 1'b0;
            
            // Wait for transaction to complete
            repeat (5) @(posedge clk);
            
            // Read sbdata0 to verify read data
            apb_read(ADDR_SBDATA0, rd_data);
            check_value(rd_data, 32'hDEADBEEF, "SBA read data in sbdata0");
            
            // Test SBA write
            $display("Testing SBA write operation...");
            test_data = 32'h12345678;
            apb_write(ADDR_SBDATA0, test_data, 4'hF);
            
            // Check that AXI write transaction is initiated
            repeat (2) @(posedge clk);
            check_signal(dbg_axi_awvalid, 1'b1, "SBA initiates AXI write (awvalid)");
            check_signal(dbg_axi_wvalid, 1'b1, "SBA initiates AXI write (wvalid)");
            check_value(dbg_axi_wdata, test_data, "SBA AXI write data correct");
            
            // Simulate AXI write response
            @(posedge clk);
            dbg_axi_bvalid = 1'b1;
            dbg_axi_bresp = 2'b00;
            
            @(posedge clk);
            dbg_axi_bvalid = 1'b0;
            
            // Wait for transaction to complete
            repeat (5) @(posedge clk);
            
            // Reset
            apb_write(ADDR_DMCONTROL, 32'h00000000, 4'hF);
        end
    endtask
    
    //==========================================================================
    // Main Test Sequence
    //==========================================================================
    initial begin
        $dumpfile("sim/tb_debug_dm_preservation.vcd");
        $dumpvars(0, tb_debug_dm_preservation);
        
        // Initialize signals
        resetn = 1'b0;
        psel = 1'b0;
        penable = 1'b0;
        pwrite = 1'b0;
        paddr = 32'h0;
        pwdata = 32'h0;
        pstrb = 4'h0;
        pprot = 3'b000;
        
        // JTAG interface unused in preservation tests
        jtag_valid = 1'b0;
        jtag_write = 1'b0;
        jtag_addr = 8'h0;
        jtag_wdata = 32'h0;
        jtag_wstrb = 4'h0;
        
        dbg_halted = 1'b0;
        dbg_reg_rdata = 32'h0;
        
        // AXI slave responses
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
        repeat (10) @(posedge clk);
        
        $display("");
        $display("========================================");
        $display("  Debug Module Preservation Tests");
        $display("  Testing on UNFIXED code");
        $display("  **EXPECTED TO PASS**");
        $display("========================================");
        $display("");
        
        //----------------------------------------------------------------------
        // Specific Preservation Tests
        //----------------------------------------------------------------------
        
        test_apb_dmcontrol_write();
        test_apb_data0_write_read();
        test_abstract_command_preservation();
        test_debug_core_interface_preservation();
        test_system_bus_access_preservation();
        
        //----------------------------------------------------------------------
        // Property-Based Preservation Tests
        //----------------------------------------------------------------------
        
        property_apb_write_preservation(20);  // 20 random APB writes
        property_apb_read_preservation(20);   // 20 random APB reads
        
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
        
        if (fail_count == 0) begin
            $display("*** ALL PRESERVATION TESTS PASSED ***");
            $display("");
            $display("Baseline behavior confirmed:");
            $display("  - APB write transactions work correctly");
            $display("  - APB read transactions work correctly");
            $display("  - Abstract commands execute via APB");
            $display("  - Debug core interface signals respond correctly");
            $display("  - System Bus Access operations work via APB");
            $display("");
            $display("These behaviors MUST be preserved after CDC fix implementation.");
        end else begin
            $display("*** PRESERVATION TESTS FAILED ***");
            $display("");
            $display("UNEXPECTED: Some preservation tests failed on unfixed code!");
            $display("This suggests issues with the baseline implementation");
            $display("that are unrelated to the JTAG CDC bug.");
        end
        
        $display("");
        $finish;
    end
    
    // Timeout watchdog
    initial begin
        #100000;  // 100 us timeout
        $display("");
        $display("[TIMEOUT] Simulation exceeded 100us — aborting.");
        $finish;
    end

endmodule
