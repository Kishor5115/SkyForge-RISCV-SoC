/*
 * flash_xip — External-QSPI-Flash XIP Subsystem  (v2)
 *
 * Owns the AXI slave S2 flash region (0x4000_0000 - 0x40FF_FFFF) and splits it:
 *
 *   REGISTER window : 0x4000_0000 - 0x4000_FFFF   (araddr[23:16] == 0x00)
 *                     -> flash_ctrl control/status registers (uncached, R/W).
 *                        Only addr[7:0] is decoded by flash_ctrl.
 *
 *   XIP memory      : 0x4001_0000 - 0x40FF_FFFF
 *                     -> reads served by icache_1k, which fills lines from the
 *                        flash_ctrl XIP read port (external QSPI flash chip).
 *                        Flash physical offset = addr[23:0] (e.g. 0x4001_0000
 *                        maps to flash offset 0x01_0000).
 *
 * Writes to the XIP window are not supported and return SLVERR (via the
 * flash_ctrl XIP write port). The external flash chip itself is NOT part of
 * the SoC — only this controller and the QSPI pins are. A behavioral flash
 * model lives in the testbench.
 *
 * picorv32 issues a single outstanding transaction at a time, so the read and
 * write routing selectors are latched at address-handshake and held until the
 * response handshake.
 */

module flash_xip (
    input  logic        clk,
    input  logic        resetn,

    // ── AXI4-Lite slave (interconnect S2) ─────────────────────
    input  logic [31:0] axi_awaddr,
    input  logic [ 2:0] axi_awprot,
    input  logic        axi_awvalid,
    output logic        axi_awready,

    input  logic [31:0] axi_wdata,
    input  logic        axi_wvalid,
    output logic        axi_wready,
    input  logic [ 3:0] axi_wstrb,

    output logic        axi_bvalid,
    input  logic        axi_bready,
    output logic [ 1:0] axi_bresp,

    input  logic [31:0] axi_araddr,
    input  logic [ 2:0] axi_arprot,
    input  logic        axi_arvalid,
    output logic        axi_arready,

    output logic [31:0] axi_rdata,
    output logic        axi_rvalid,
    input  logic        axi_rready,
    output logic [ 1:0] axi_rresp,

    // ── QSPI flash pins (to external flash chip) ──────────────
    output logic        flash_sclk,
    output logic        flash_cs_n,
    output logic        flash_mosi,
    input  logic        flash_miso,

    // ── Status ────────────────────────────────────────────────
    output logic        flash_ready,
    output logic [23:0] jedec_id,
    output logic        xip_active
);

    // ── Window decode: register window = top 8 addr bits of the
    //    24-bit flash offset are zero (0x4000_0000 - 0x4000_FFFF) ──
    wire aw_is_reg = (axi_awaddr[23:16] == 8'h00);
    wire ar_is_reg = (axi_araddr[23:16] == 8'h00);

    // ── Write routing selector (latched, single outstanding) ──
    logic w_sel_valid, w_sel_reg;
    wire  w_reg = w_sel_valid ? w_sel_reg : aw_is_reg;

    // ── Read routing selector (latched, single outstanding) ───
    logic r_sel_valid, r_sel_reg;
    wire  r_reg = r_sel_valid ? r_sel_reg : ar_is_reg;

    always_ff @(posedge clk) begin
        if (!resetn) begin
            w_sel_valid <= 1'b0; w_sel_reg <= 1'b0;
            r_sel_valid <= 1'b0; r_sel_reg <= 1'b0;
        end else begin
            if (!w_sel_valid && axi_awvalid && axi_awready) begin
                w_sel_valid <= 1'b1;
                w_sel_reg   <= aw_is_reg;
            end
            if (w_sel_valid && axi_bvalid && axi_bready)
                w_sel_valid <= 1'b0;

            if (!r_sel_valid && axi_arvalid && axi_arready) begin
                r_sel_valid <= 1'b1;
                r_sel_reg   <= ar_is_reg;
            end
            if (r_sel_valid && axi_rvalid && axi_rready)
                r_sel_valid <= 1'b0;
        end
    end

    // ── flash_ctrl register port nets ─────────────────────────
    logic        fc_awvalid, fc_awready, fc_wvalid, fc_wready;
    logic        fc_bvalid,  fc_bready;
    logic [1:0]  fc_bresp;
    logic        fc_arvalid, fc_arready, fc_rvalid, fc_rready;
    logic [31:0] fc_rdata;
    logic [1:0]  fc_rresp;

    // ── flash_ctrl XIP write port nets (SLVERR path) ──────────
    logic        xw_awvalid, xw_awready, xw_wvalid, xw_wready;
    logic        xw_bvalid,  xw_bready;
    logic [1:0]  xw_bresp;

    // ── icache <-> flash_ctrl XIP read port nets ──────────────
    logic        ic_s_arvalid, ic_s_arready, ic_s_rvalid, ic_s_rready;
    logic [31:0] ic_s_rdata;
    logic [1:0]  ic_s_rresp;
    logic         xr_arvalid, xr_arready, xr_rvalid, xr_rready;
    logic [31:0] xr_araddr, xr_rdata;
    logic [1:0]  xr_rresp;

    // ── Write-channel demux (reg port vs XIP-write SLVERR) ────
    assign fc_awvalid  = axi_awvalid &  w_reg;
    assign xw_awvalid  = axi_awvalid & ~w_reg;
    assign axi_awready = w_reg ? fc_awready : xw_awready;

    assign fc_wvalid   = axi_wvalid &  w_reg;
    assign xw_wvalid   = axi_wvalid & ~w_reg;
    assign axi_wready  = w_reg ? fc_wready : xw_wready;

    assign axi_bvalid  = w_reg ? fc_bvalid : xw_bvalid;
    assign axi_bresp   = w_reg ? fc_bresp  : xw_bresp;
    assign fc_bready   = axi_bready &  w_reg;
    assign xw_bready   = axi_bready & ~w_reg;

    // ── Read-channel mux (reg port vs icache) ─────────────────
    assign fc_arvalid   = axi_arvalid &  r_reg;
    assign ic_s_arvalid = axi_arvalid & ~r_reg;
    assign axi_arready  = r_reg ? fc_arready : ic_s_arready;

    assign axi_rvalid   = r_reg ? fc_rvalid : ic_s_rvalid;
    assign axi_rdata    = r_reg ? fc_rdata  : ic_s_rdata;
    assign axi_rresp    = r_reg ? fc_rresp  : ic_s_rresp;
    assign fc_rready    = axi_rready &  r_reg;
    assign ic_s_rready  = axi_rready & ~r_reg;

    // ── I-Cache ────────────────────────────────────────────────
    icache_1k #(
        .NUM_LINES (32),
        .LINE_WORDS(8)
    ) u_icache (
        .clk          (clk),
        .resetn       (resetn),
        .s_axi_arvalid(ic_s_arvalid),
        .s_axi_arready(ic_s_arready),
        .s_axi_araddr (axi_araddr),
        .s_axi_arprot (axi_arprot),
        .s_axi_rvalid (ic_s_rvalid),
        .s_axi_rready (ic_s_rready),
        .s_axi_rdata  (ic_s_rdata),
        .s_axi_rresp  (ic_s_rresp),
        .m_axi_arvalid(xr_arvalid),
        .m_axi_arready(xr_arready),
        .m_axi_araddr (xr_araddr),
        .m_axi_rvalid (xr_rvalid),
        .m_axi_rready (xr_rready),
        .m_axi_rdata  (xr_rdata),
        .m_axi_rresp  (xr_rresp)
    );

    // ── QSPI flash controller (external flash chip is off-SoC) ─
    flash_ctrl u_flash_ctrl (
        .clk         (clk),
        .resetn      (resetn),
        // Register AXI port
        .axi_araddr  (axi_araddr[7:0]),
        .axi_arprot  (axi_arprot),
        .axi_arvalid (fc_arvalid),
        .axi_arready (fc_arready),
        .axi_rdata   (fc_rdata),
        .axi_rvalid  (fc_rvalid),
        .axi_rready  (fc_rready),
        .axi_rresp   (fc_rresp),
        .axi_awaddr  (axi_awaddr[7:0]),
        .axi_awprot  (axi_awprot),
        .axi_awvalid (fc_awvalid),
        .axi_awready (fc_awready),
        .axi_wdata   (axi_wdata),
        .axi_wvalid  (fc_wvalid),
        .axi_wready  (fc_wready),
        .axi_wstrb   (axi_wstrb),
        .axi_bvalid  (fc_bvalid),
        .axi_bready  (fc_bready),
        .axi_bresp   (fc_bresp),
        // XIP read port (driven by icache)
        .xip_araddr  (xr_araddr),
        .xip_arvalid (xr_arvalid),
        .xip_arready (xr_arready),
        .xip_rdata   (xr_rdata),
        .xip_rvalid  (xr_rvalid),
        .xip_rready  (xr_rready),
        .xip_rresp   (xr_rresp),
        // XIP write port (XIP-window writes -> SLVERR)
        .xip_awaddr  (axi_awaddr),
        .xip_awvalid (xw_awvalid),
        .xip_awready (xw_awready),
        .xip_wdata   (axi_wdata),
        .xip_wvalid  (xw_wvalid),
        .xip_wready  (xw_wready),
        .xip_wstrb   (axi_wstrb),
        .xip_bvalid  (xw_bvalid),
        .xip_bready  (xw_bready),
        .xip_bresp   (xw_bresp),
        // QSPI pins
        .flash_sclk  (flash_sclk),
        .flash_cs_n  (flash_cs_n),
        .flash_mosi  (flash_mosi),
        .flash_miso  (flash_miso),
        // Status
        .flash_ready (flash_ready),
        .jedec_id    (jedec_id),
        .xip_active  (xip_active)
    );

endmodule
