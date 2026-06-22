/*
 * flash_xip_tb — Directed test for the v2 flash XIP datapath
 *
 * Exercises flash_xip (icache_1k + flash_ctrl) against the behavioral external
 * flash model:
 *   1. Configure flash_ctrl: small CLKDIV, enable + XIP enable via reg window.
 *   2. Read cached XIP words (0x40010000+) and check against known flash data.
 *   3. Re-read a word in an already-filled line -> cache HIT (single cycle).
 *   4. Read a different line -> MISS (refill) and check data.
 *
 * Flash model is preloaded (hierarchically) with mem[0x10000+i] = i so the
 * little-endian word at 0x40010000 is 0x03020100, at 0x40010004 is 0x07060504.
 */
`timescale 1ns/1ps

module flash_xip_tb;

    logic clk = 0;
    logic resetn = 0;
    always #5 clk = ~clk;   // 100 MHz

    // ── DUT AXI-Lite slave signals ────────────────────────────
    logic [31:0] awaddr=0, wdata=0, araddr=0;
    logic [2:0]  awprot=0, arprot=0;
    logic        awvalid=0, wvalid=0, arvalid=0, bready=0, rready=0;
    logic [3:0]  wstrb=0;
    logic        awready, wready, bvalid, arready, rvalid;
    logic [1:0]  bresp, rresp;
    logic [31:0] rdata;

    // ── QSPI nets ─────────────────────────────────────────────
    logic flash_sclk, flash_cs_n, flash_mosi, flash_miso;
    logic flash_ready, xip_active;
    logic [23:0] jedec_id;

    // ── DUT ───────────────────────────────────────────────────
    flash_xip dut (
        .clk(clk), .resetn(resetn),
        .axi_awaddr(awaddr), .axi_awprot(awprot), .axi_awvalid(awvalid), .axi_awready(awready),
        .axi_wdata(wdata), .axi_wvalid(wvalid), .axi_wready(wready), .axi_wstrb(wstrb),
        .axi_bvalid(bvalid), .axi_bready(bready), .axi_bresp(bresp),
        .axi_araddr(araddr), .axi_arprot(arprot), .axi_arvalid(arvalid), .axi_arready(arready),
        .axi_rdata(rdata), .axi_rvalid(rvalid), .axi_rready(rready), .axi_rresp(rresp),
        .flash_sclk(flash_sclk), .flash_cs_n(flash_cs_n), .flash_mosi(flash_mosi), .flash_miso(flash_miso),
        .flash_ready(flash_ready), .jedec_id(jedec_id), .xip_active(xip_active)
    );

    // ── External flash model ──────────────────────────────────
    flash_model #(.INIT_FILE("")) u_fm (
        .sclk(flash_sclk), .cs_n(flash_cs_n), .mosi(flash_mosi), .miso(flash_miso)
    );

    // ── AXI-Lite master BFM ───────────────────────────────────
    task automatic axi_write(input [31:0] a, input [31:0] d);
        reg da, dw, db;
        begin
            da=0; dw=0; db=0;
            @(posedge clk); #1;
            awaddr=a; awvalid=1; wdata=d; wstrb=4'hF; wvalid=1; bready=1;
            while (!(da && dw && db)) begin
                @(posedge clk);
                if (awvalid && awready) da=1;
                if (wvalid  && wready ) dw=1;
                if (bvalid)             db=1;
                #1;
                if (da) awvalid=0;
                if (dw) wvalid=0;
                if (db) bready=0;
            end
        end
    endtask

    task automatic axi_read(input [31:0] a, output [31:0] d);
        reg dar, dr;
        integer cyc;
        begin
            dar=0; dr=0; cyc=0;
            @(posedge clk); #1;
            araddr=a; arvalid=1; rready=1;
            while (!(dar && dr)) begin
                @(posedge clk);
                cyc = cyc + 1;
                if (arvalid && arready) dar=1;
                if (rvalid  && rready ) begin dr=1; d=rdata; end
                #1;
                if (dar) arvalid=0;
                if (dr)  rready=0;
            end
            last_read_cycles = cyc;
        end
    endtask

    integer last_read_cycles = 0;
    integer errors = 0;
    logic [31:0] v;

    task check(input [31:0] got, input [31:0] exp, input [127:0] name);
        begin
            if (got !== exp) begin
                $display("  FAIL %0s: got %08x expected %08x", name, got, exp);
                errors = errors + 1;
            end else begin
                $display("  PASS %0s: %08x", name, got);
            end
        end
    endtask

    integer i;
    initial begin
        // Preload flash model: mem[0x10000 + i] = i
        for (i = 0; i < 2048; i = i + 1)
            u_fm.mem[24'h010000 + i] = i[7:0];

        // Reset
        repeat (4) @(posedge clk);
        resetn = 1;
        repeat (2) @(posedge clk);

        // Configure flash_ctrl: small clock divisor, then enable + XIP
        axi_write(32'h4000_0018, 32'd1);    // CLKDIV
        axi_write(32'h4000_0000, 32'h0000_0003); // CTRL: enable | xip_en (24-bit)
        repeat (4) @(posedge clk);
        $display("xip_active=%0b flash_ready=%0b", xip_active, flash_ready);

        // First XIP read: MISS, fills line 0
        axi_read(32'h4001_0000, v);
        check(v, 32'h0302_0100, "xip[0x10000]");
        $display("    (miss fill took %0d cycles)", last_read_cycles);

        // Same line, next word: HIT (should be only a few cycles)
        axi_read(32'h4001_0004, v);
        check(v, 32'h0706_0504, "xip[0x10004]");
        $display("    (same-line read took %0d cycles -> expect HIT)", last_read_cycles);

        // Last word of line 0 (offset 0x1C): still HIT
        axi_read(32'h4001_001C, v);
        check(v, 32'h1F1E_1D1C, "xip[0x1001C]");

        // Different line (offset 0x20): MISS refill
        axi_read(32'h4001_0020, v);
        check(v, 32'h2322_2120, "xip[0x10020]");
        $display("    (new-line read took %0d cycles -> expect MISS)", last_read_cycles);

        // Re-read line 0 word 0: still cached HIT
        axi_read(32'h4001_0000, v);
        check(v, 32'h0302_0100, "xip[0x10000] re-read");
        $display("    (re-read took %0d cycles -> expect HIT)", last_read_cycles);

        if (errors == 0) $display("\nFLASH_XIP_TB: ALL PASS");
        else             $display("\nFLASH_XIP_TB: %0d FAILURE(S)", errors);
        $finish;
    end

    // Watchdog
    initial begin
        #5_000_000;
        $display("FLASH_XIP_TB: TIMEOUT");
        $finish;
    end

endmodule
