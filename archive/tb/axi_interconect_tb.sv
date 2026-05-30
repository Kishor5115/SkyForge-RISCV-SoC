/*
 * AXI Interconnect Testbench
 *
 * Self-checking testbench for AXI4-Lite interconnect with 1 master and 4 slaves.
 *
 * Address Map verified:
 *   Slave 0 (Boot ROM): 0x00000000 - 0x0000FFFF
 *   Slave 1 (SRAM)    : 0x00010000 - 0x0002FFFF
 *   Slave 2 (Flash)   : 0x40000000 - 0x40FFFFFF
 *   Slave 3 (APB)     : 0x20000000 - 0x2000FFFF
 */

`timescale 1ns / 1ps

module axi_interconnect_tb;

    //==========================================================================
    // Signals
    //==========================================================================
    logic        clk;
    logic        resetn;

    // Master AXI interface
    logic        m_awvalid, m_awready;
    logic [31:0] m_awaddr;
    logic [2:0]  m_awprot;
    logic        m_wvalid, m_wready;
    logic [31:0] m_wdata;
    logic [3:0]  m_wstrb;
    logic        m_bvalid, m_bready;
    logic [1:0]  m_bresp;
    logic        m_arvalid, m_arready;
    logic [31:0] m_araddr;
    logic [2:0]  m_arprot;
    logic        m_rvalid, m_rready;
    logic [31:0] m_rdata;
    logic [1:0]  m_rresp;

    // Slave 0 AXI interface (Boot ROM region)
    logic        s0_awvalid, s0_awready;
    logic [31:0] s0_awaddr;
    logic [2:0]  s0_awprot;
    logic        s0_wvalid, s0_wready;
    logic [31:0] s0_wdata;
    logic [3:0]  s0_wstrb;
    logic        s0_bvalid, s0_bready;
    logic [1:0]  s0_bresp;
    logic        s0_arvalid, s0_arready;
    logic [31:0] s0_araddr;
    logic [2:0]  s0_arprot;
    logic        s0_rvalid, s0_rready;
    logic [31:0] s0_rdata;
    logic [1:0]  s0_rresp;

    // Slave 1 AXI interface (SRAM region)
    logic        s1_awvalid, s1_awready;
    logic [31:0] s1_awaddr;
    logic [2:0]  s1_awprot;
    logic        s1_wvalid, s1_wready;
    logic [31:0] s1_wdata;
    logic [3:0]  s1_wstrb;
    logic        s1_bvalid, s1_bready;
    logic [1:0]  s1_bresp;
    logic        s1_arvalid, s1_arready;
    logic [31:0] s1_araddr;
    logic [2:0]  s1_arprot;
    logic        s1_rvalid, s1_rready;
    logic [31:0] s1_rdata;
    logic [1:0]  s1_rresp;

    // Slave 2 AXI interface (Flash region)
    logic        s2_awvalid, s2_awready;
    logic [31:0] s2_awaddr;
    logic [2:0]  s2_awprot;
    logic        s2_wvalid, s2_wready;
    logic [31:0] s2_wdata;
    logic [3:0]  s2_wstrb;
    logic        s2_bvalid, s2_bready;
    logic [1:0]  s2_bresp;
    logic        s2_arvalid, s2_arready;
    logic [31:0] s2_araddr;
    logic [2:0]  s2_arprot;
    logic        s2_rvalid, s2_rready;
    logic [31:0] s2_rdata;
    logic [1:0]  s2_rresp;

    // Slave 3 AXI interface (APB region)
    logic        s3_awvalid, s3_awready;
    logic [31:0] s3_awaddr;
    logic [2:0]  s3_awprot;
    logic        s3_wvalid, s3_wready;
    logic [31:0] s3_wdata;
    logic [3:0]  s3_wstrb;
    logic        s3_bvalid, s3_bready;
    logic [1:0]  s3_bresp;
    logic        s3_arvalid, s3_arready;
    logic [31:0] s3_araddr;
    logic [2:0]  s3_arprot;
    logic        s3_rvalid, s3_rready;
    logic [31:0] s3_rdata;
    logic [1:0]  s3_rresp;

    integer pass_count = 0;
    integer fail_count = 0;

    //==========================================================================
    // DUT
    //==========================================================================
    axi_interconnect u_dut (
        .clk(clk),
        .resetn(resetn),

        .m_axi_awvalid(m_awvalid), .m_axi_awready(m_awready),
        .m_axi_awaddr(m_awaddr),   .m_axi_awprot(m_awprot),
        .m_axi_wvalid(m_wvalid),   .m_axi_wready(m_wready),
        .m_axi_wdata(m_wdata),     .m_axi_wstrb(m_wstrb),
        .m_axi_bvalid(m_bvalid),   .m_axi_bready(m_bready),
        .m_axi_bresp(m_bresp),
        .m_axi_arvalid(m_arvalid), .m_axi_arready(m_arready),
        .m_axi_araddr(m_araddr),   .m_axi_arprot(m_arprot),
        .m_axi_rvalid(m_rvalid),   .m_axi_rready(m_rready),
        .m_axi_rdata(m_rdata),     .m_axi_rresp(m_rresp),

        .s0_axi_awvalid(s0_awvalid), .s0_axi_awready(s0_awready),
        .s0_axi_awaddr(s0_awaddr),   .s0_axi_awprot(s0_awprot),
        .s0_axi_wvalid(s0_wvalid),   .s0_axi_wready(s0_wready),
        .s0_axi_wdata(s0_wdata),     .s0_axi_wstrb(s0_wstrb),
        .s0_axi_bvalid(s0_bvalid),   .s0_axi_bready(s0_bready),
        .s0_axi_bresp(s0_bresp),
        .s0_axi_arvalid(s0_arvalid), .s0_axi_arready(s0_arready),
        .s0_axi_araddr(s0_araddr),   .s0_axi_arprot(s0_arprot),
        .s0_axi_rvalid(s0_rvalid),   .s0_axi_rready(s0_rready),
        .s0_axi_rdata(s0_rdata),     .s0_axi_rresp(s0_rresp),

        .s1_axi_awvalid(s1_awvalid), .s1_axi_awready(s1_awready),
        .s1_axi_awaddr(s1_awaddr),   .s1_axi_awprot(s1_awprot),
        .s1_axi_wvalid(s1_wvalid),   .s1_axi_wready(s1_wready),
        .s1_axi_wdata(s1_wdata),     .s1_axi_wstrb(s1_wstrb),
        .s1_axi_bvalid(s1_bvalid),   .s1_axi_bready(s1_bready),
        .s1_axi_bresp(s1_bresp),
        .s1_axi_arvalid(s1_arvalid), .s1_axi_arready(s1_arready),
        .s1_axi_araddr(s1_araddr),   .s1_axi_arprot(s1_arprot),
        .s1_axi_rvalid(s1_rvalid),   .s1_axi_rready(s1_rready),
        .s1_axi_rdata(s1_rdata),     .s1_axi_rresp(s1_rresp),

        .s2_axi_awvalid(s2_awvalid), .s2_axi_awready(s2_awready),
        .s2_axi_awaddr(s2_awaddr),   .s2_axi_awprot(s2_awprot),
        .s2_axi_wvalid(s2_wvalid),   .s2_axi_wready(s2_wready),
        .s2_axi_wdata(s2_wdata),     .s2_axi_wstrb(s2_wstrb),
        .s2_axi_bvalid(s2_bvalid),   .s2_axi_bready(s2_bready),
        .s2_axi_bresp(s2_bresp),
        .s2_axi_arvalid(s2_arvalid), .s2_axi_arready(s2_arready),
        .s2_axi_araddr(s2_araddr),   .s2_axi_arprot(s2_arprot),
        .s2_axi_rvalid(s2_rvalid),   .s2_axi_rready(s2_rready),
        .s2_axi_rdata(s2_rdata),     .s2_axi_rresp(s2_rresp),

        .s3_axi_awvalid(s3_awvalid), .s3_axi_awready(s3_awready),
        .s3_axi_awaddr(s3_awaddr),   .s3_axi_awprot(s3_awprot),
        .s3_axi_wvalid(s3_wvalid),   .s3_axi_wready(s3_wready),
        .s3_axi_wdata(s3_wdata),     .s3_axi_wstrb(s3_wstrb),
        .s3_axi_bvalid(s3_bvalid),   .s3_axi_bready(s3_bready),
        .s3_axi_bresp(s3_bresp),
        .s3_axi_arvalid(s3_arvalid), .s3_axi_arready(s3_arready),
        .s3_axi_araddr(s3_araddr),   .s3_axi_arprot(s3_arprot),
        .s3_axi_rvalid(s3_rvalid),   .s3_axi_rready(s3_rready),
        .s3_axi_rdata(s3_rdata),     .s3_axi_rresp(s3_rresp)
    );

    //==========================================================================
    // Slave 0: AXI RAM (64KB for Boot ROM window checks)
    //==========================================================================
    axi_ram #(
        .ADDR_WIDTH(16),
        .DATA_WIDTH(32)
    ) u_slave0_ram (
        .clk(clk),
        .resetn(resetn),
        .axi_awaddr(s0_awaddr[15:0]),
        .axi_awprot(s0_awprot),
        .axi_awvalid(s0_awvalid),
        .axi_awready(s0_awready),
        .axi_wdata(s0_wdata),
        .axi_wvalid(s0_wvalid),
        .axi_wready(s0_wready),
        .axi_wstrb(s0_wstrb),
        .axi_bvalid(s0_bvalid),
        .axi_bready(s0_bready),
        .axi_bresp(s0_bresp),
        .axi_araddr(s0_araddr[15:0]),
        .axi_arprot(s0_arprot),
        .axi_arvalid(s0_arvalid),
        .axi_arready(s0_arready),
        .axi_rdata(s0_rdata),
        .axi_rvalid(s0_rvalid),
        .axi_rready(s0_rready),
        .axi_rresp(s0_rresp)
    );

    //==========================================================================
    // Slave 1: AXI RAM (128KB SRAM window checks)
    //==========================================================================
    axi_ram #(
        .ADDR_WIDTH(17),
        .DATA_WIDTH(32)
    ) u_slave1_ram (
        .clk(clk),
        .resetn(resetn),
        .axi_awaddr(s1_awaddr[16:0]),
        .axi_awprot(s1_awprot),
        .axi_awvalid(s1_awvalid),
        .axi_awready(s1_awready),
        .axi_wdata(s1_wdata),
        .axi_wvalid(s1_wvalid),
        .axi_wready(s1_wready),
        .axi_wstrb(s1_wstrb),
        .axi_bvalid(s1_bvalid),
        .axi_bready(s1_bready),
        .axi_bresp(s1_bresp),
        .axi_araddr(s1_araddr[16:0]),
        .axi_arprot(s1_arprot),
        .axi_arvalid(s1_arvalid),
        .axi_arready(s1_arready),
        .axi_rdata(s1_rdata),
        .axi_rvalid(s1_rvalid),
        .axi_rready(s1_rready),
        .axi_rresp(s1_rresp)
    );

    //==========================================================================
    // Slave 2: Simple AXI Stub (Flash window)
    //==========================================================================
    logic [31:0] s2_stored_data;
    logic        s2_aw_done, s2_w_done, s2_bvalid_r, s2_rvalid_r;
    logic [31:0] s2_rdata_r;

    assign s2_awready = !s2_aw_done && !s2_bvalid_r;
    assign s2_wready  = !s2_w_done  && !s2_bvalid_r;
    assign s2_bvalid  = s2_bvalid_r;
    assign s2_bresp   = 2'b00;
    assign s2_arready = !s2_rvalid_r;
    assign s2_rvalid  = s2_rvalid_r;
    assign s2_rdata   = s2_rdata_r;
    assign s2_rresp   = 2'b00;

    always_ff @(posedge clk) begin
        if (!resetn) begin
            s2_aw_done     <= 1'b0;
            s2_w_done      <= 1'b0;
            s2_bvalid_r    <= 1'b0;
            s2_rvalid_r    <= 1'b0;
            s2_stored_data <= 32'h0;
            s2_rdata_r     <= 32'h0;
        end else begin
            if (s2_awvalid && s2_awready) s2_aw_done <= 1'b1;
            if (s2_wvalid && s2_wready) begin
                s2_w_done <= 1'b1;
                s2_stored_data <= s2_wdata;
            end
            if (s2_aw_done && s2_w_done && !s2_bvalid_r) s2_bvalid_r <= 1'b1;
            if (s2_bvalid_r && s2_bready) begin
                s2_bvalid_r <= 1'b0;
                s2_aw_done  <= 1'b0;
                s2_w_done   <= 1'b0;
            end

            if (s2_arvalid && s2_arready) begin
                s2_rdata_r  <= s2_stored_data;
                s2_rvalid_r <= 1'b1;
            end
            if (s2_rvalid_r && s2_rready) s2_rvalid_r <= 1'b0;
        end
    end

    //==========================================================================
    // Slave 3: Simple AXI Stub (APB window)
    //==========================================================================
    logic [31:0] s3_stored_data;
    logic        s3_aw_done, s3_w_done, s3_bvalid_r, s3_rvalid_r;
    logic [31:0] s3_rdata_r;

    assign s3_awready = !s3_aw_done && !s3_bvalid_r;
    assign s3_wready  = !s3_w_done  && !s3_bvalid_r;
    assign s3_bvalid  = s3_bvalid_r;
    assign s3_bresp   = 2'b00;
    assign s3_arready = !s3_rvalid_r;
    assign s3_rvalid  = s3_rvalid_r;
    assign s3_rdata   = s3_rdata_r;
    assign s3_rresp   = 2'b00;

    always_ff @(posedge clk) begin
        if (!resetn) begin
            s3_aw_done     <= 1'b0;
            s3_w_done      <= 1'b0;
            s3_bvalid_r    <= 1'b0;
            s3_rvalid_r    <= 1'b0;
            s3_stored_data <= 32'h0;
            s3_rdata_r     <= 32'h0;
        end else begin
            if (s3_awvalid && s3_awready) s3_aw_done <= 1'b1;
            if (s3_wvalid && s3_wready) begin
                s3_w_done <= 1'b1;
                s3_stored_data <= s3_wdata;
            end
            if (s3_aw_done && s3_w_done && !s3_bvalid_r) s3_bvalid_r <= 1'b1;
            if (s3_bvalid_r && s3_bready) begin
                s3_bvalid_r <= 1'b0;
                s3_aw_done  <= 1'b0;
                s3_w_done   <= 1'b0;
            end

            if (s3_arvalid && s3_arready) begin
                s3_rdata_r  <= s3_stored_data;
                s3_rvalid_r <= 1'b1;
            end
            if (s3_rvalid_r && s3_rready) s3_rvalid_r <= 1'b0;
        end
    end

    //==========================================================================
    // Clock generation — 100 MHz
    //==========================================================================
    initial begin
        clk = 1'b0;
        forever #5 clk = ~clk;
    end

    //==========================================================================
    // AXI Master Tasks
    //==========================================================================
    task axi_write;
        input [31:0] addr;
        input [31:0] data;
        input [3:0]  strb;
        begin
            @(posedge clk);
            m_awvalid = 1'b1;
            m_awaddr  = addr;
            m_awprot  = 3'b000;
            m_wvalid  = 1'b1;
            m_wdata   = data;
            m_wstrb   = strb;
            m_bready  = 1'b1;

            fork
                begin wait(m_awready && m_awvalid); @(posedge clk); #1; m_awvalid = 1'b0; end
                begin wait(m_wready && m_wvalid);   @(posedge clk); #1; m_wvalid  = 1'b0; end
            join

            wait(m_bvalid);
            @(posedge clk);
            #1;
            m_bready = 1'b0;
        end
    endtask

    task axi_read;
        input  [31:0] addr;
        output [31:0] data;
        begin
            @(posedge clk);
            m_arvalid = 1'b1;
            m_araddr  = addr;
            m_arprot  = 3'b000;
            m_rready  = 1'b1;

            wait(m_arready && m_arvalid);
            @(posedge clk);
            #1;
            m_arvalid = 1'b0;

            wait(m_rvalid);
            data = m_rdata;
            @(posedge clk);
            #1;
            m_rready = 1'b0;
        end
    endtask

    //==========================================================================
    // Main test sequence
    //==========================================================================
    logic [31:0] rd_data;

    initial begin
        $dumpfile("sim/axi_interconnect_tb.vcd");
        $dumpvars(0, axi_interconnect_tb);

        // Initialize
        m_awvalid = 0; m_awaddr = 0; m_awprot = 0;
        m_wvalid  = 0; m_wdata  = 0; m_wstrb  = 0;
        m_bready  = 0;
        m_arvalid = 0; m_araddr = 0; m_arprot = 0;
        m_rready  = 0;

        resetn = 0;
        #100;
        resetn = 1;
        repeat (3) @(posedge clk);

        $display("");
        $display("========================================");
        $display("  AXI Interconnect 4-Slave Testbench");
        $display("========================================");
        $display("");

        //----------------------------------------------------------------------
        // TEST 1: Slave 0 (Boot ROM window)
        //----------------------------------------------------------------------
        $display("--- Test 1: Write/Read Slave 0 @ 0x0000_1000 ---");
        axi_write(32'h0000_1000, 32'hDEAD_BEEF, 4'b1111);
        axi_read (32'h0000_1000, rd_data);
        if (rd_data === 32'hDEAD_BEEF) begin
            $display("[PASS] S0 read = 0x%08h", rd_data);
            pass_count = pass_count + 1;
        end else begin
            $display("[FAIL] S0 expected 0xDEADBEEF, got 0x%08h", rd_data);
            fail_count = fail_count + 1;
        end

        //----------------------------------------------------------------------
        // TEST 2: Slave 1 (SRAM window)
        //----------------------------------------------------------------------
        $display("");
        $display("--- Test 2: Write/Read Slave 1 @ 0x0001_0100 ---");
        axi_write(32'h0001_0100, 32'hCAFE_BABE, 4'b1111);
        axi_read (32'h0001_0100, rd_data);
        if (rd_data === 32'hCAFE_BABE) begin
            $display("[PASS] S1 read = 0x%08h", rd_data);
            pass_count = pass_count + 1;
        end else begin
            $display("[FAIL] S1 expected 0xCAFEBABE, got 0x%08h", rd_data);
            fail_count = fail_count + 1;
        end

        //----------------------------------------------------------------------
        // TEST 3: Slave 2 (Flash window)
        //----------------------------------------------------------------------
        $display("");
        $display("--- Test 3: Write/Read Slave 2 @ 0x4000_0020 ---");
        axi_write(32'h4000_0020, 32'h1234_5678, 4'b1111);
        axi_read (32'h4000_0020, rd_data);
        if (rd_data === 32'h1234_5678) begin
            $display("[PASS] S2 read = 0x%08h", rd_data);
            pass_count = pass_count + 1;
        end else begin
            $display("[FAIL] S2 expected 0x12345678, got 0x%08h", rd_data);
            fail_count = fail_count + 1;
        end

        //----------------------------------------------------------------------
        // TEST 4: Slave 3 (APB window)
        //----------------------------------------------------------------------
        $display("");
        $display("--- Test 4: Write/Read Slave 3 @ 0x2000_0000 ---");
        axi_write(32'h2000_0000, 32'h0BAD_F00D, 4'b1111);
        axi_read (32'h2000_0000, rd_data);
        if (rd_data === 32'h0BAD_F00D) begin
            $display("[PASS] S3 read = 0x%08h", rd_data);
            pass_count = pass_count + 1;
        end else begin
            $display("[FAIL] S3 expected 0x0BADF00D, got 0x%08h", rd_data);
            fail_count = fail_count + 1;
        end

        //----------------------------------------------------------------------
        // TEST 5: Decode error on invalid address
        //----------------------------------------------------------------------
        $display("");
        $display("--- Test 5: Decode error @ 0x5000_0000 ---");

        // Invalid write
        @(posedge clk);
        m_awvalid = 1'b1;
        m_awaddr  = 32'h5000_0000;
        m_awprot  = 3'b000;
        m_wvalid  = 1'b1;
        m_wdata   = 32'hA5A5_A5A5;
        m_wstrb   = 4'b1111;
        m_bready  = 1'b0;

        fork
            begin wait(m_awready && m_awvalid); @(posedge clk); #1; m_awvalid = 1'b0; end
            begin wait(m_wready && m_wvalid);   @(posedge clk); #1; m_wvalid  = 1'b0; end
        join

        @(posedge clk);
        m_bready = 1'b1;
        wait(m_bvalid);
        if (m_bresp === 2'b11) begin
            $display("[PASS] Invalid write BRESP = DECERR");
            pass_count = pass_count + 1;
        end else begin
            $display("[FAIL] Invalid write BRESP expected DECERR, got 0x%0h", m_bresp);
            fail_count = fail_count + 1;
        end
        @(posedge clk);
        #1;
        m_bready = 1'b0;

        // Invalid read
        @(posedge clk);
        m_arvalid = 1'b1;
        m_araddr  = 32'h5000_0000;
        m_arprot  = 3'b000;
        m_rready  = 1'b0;

        wait(m_arready && m_arvalid);
        @(posedge clk);
        #1;
        m_arvalid = 1'b0;

        @(posedge clk);
        m_rready = 1'b1;
        wait(m_rvalid);
        if (m_rresp === 2'b11) begin
            $display("[PASS] Invalid read RRESP = DECERR");
            pass_count = pass_count + 1;
        end else begin
            $display("[FAIL] Invalid read RRESP expected DECERR, got 0x%0h", m_rresp);
            fail_count = fail_count + 1;
        end
        @(posedge clk);
        #1;
        m_rready = 1'b0;

        //----------------------------------------------------------------------
        // TEST 6: Alternating all slave windows
        //----------------------------------------------------------------------
        $display("");
        $display("--- Test 6: Alternating S0/S1/S2/S3 transactions ---");
        axi_write(32'h0000_2000, 32'hAAAA_AAAA, 4'b1111); // S0
        axi_write(32'h0001_2000, 32'hBBBB_BBBB, 4'b1111); // S1
        axi_write(32'h4000_1000, 32'hCCCC_CCCC, 4'b1111); // S2
        axi_write(32'h2000_0010, 32'hDDDD_DDDD, 4'b1111); // S3

        axi_read(32'h0000_2000, rd_data);
        if (rd_data === 32'hAAAA_AAAA) begin
            $display("[PASS] Alt S0 = 0x%08h", rd_data);
            pass_count = pass_count + 1;
        end else begin
            $display("[FAIL] Alt S0 expected 0xAAAAAAAA, got 0x%08h", rd_data);
            fail_count = fail_count + 1;
        end

        axi_read(32'h0001_2000, rd_data);
        if (rd_data === 32'hBBBB_BBBB) begin
            $display("[PASS] Alt S1 = 0x%08h", rd_data);
            pass_count = pass_count + 1;
        end else begin
            $display("[FAIL] Alt S1 expected 0xBBBBBBBB, got 0x%08h", rd_data);
            fail_count = fail_count + 1;
        end

        axi_read(32'h4000_1000, rd_data);
        if (rd_data === 32'hCCCC_CCCC) begin
            $display("[PASS] Alt S2 = 0x%08h", rd_data);
            pass_count = pass_count + 1;
        end else begin
            $display("[FAIL] Alt S2 expected 0xCCCCCCCC, got 0x%08h", rd_data);
            fail_count = fail_count + 1;
        end

        axi_read(32'h2000_0010, rd_data);
        if (rd_data === 32'hDDDD_DDDD) begin
            $display("[PASS] Alt S3 = 0x%08h", rd_data);
            pass_count = pass_count + 1;
        end else begin
            $display("[FAIL] Alt S3 expected 0xDDDDDDDD, got 0x%08h", rd_data);
            fail_count = fail_count + 1;
        end

        //----------------------------------------------------------------------
        // TEST 7: Byte-lane write preservation on Slave 1 RAM
        //----------------------------------------------------------------------
        $display("");
        $display("--- Test 7: WSTRB byte-lane write on S1 ---");
        axi_write(32'h0001_3000, 32'hFFFF_FFFF, 4'b1111);
        axi_write(32'h0001_3000, 32'h0000_00AA, 4'b0001);

        axi_read(32'h0001_3000, rd_data);
        if (rd_data === 32'hFFFF_FFAA) begin
            $display("[PASS] WSTRB result = 0x%08h", rd_data);
            pass_count = pass_count + 1;
        end else begin
            $display("[FAIL] WSTRB expected 0xFFFFFFAA, got 0x%08h", rd_data);
            fail_count = fail_count + 1;
        end

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
        #500000;
        $display("");
        $display("[TIMEOUT] Simulation exceeded 500us — aborting.");
        $finish;
    end

endmodule
