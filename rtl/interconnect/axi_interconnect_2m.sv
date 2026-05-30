/*
 * AXI4-Lite Interconnect with 2 Masters (CPU + Debug)
 *
 * Debug master gets priority when it has a pending request. This is
 * intended for use while the CPU is halted, so no contention is expected.
 */

module axi_interconnect_2m (
    input logic clk,
    input logic resetn,

    // Master 0 (CPU)
    input  logic        m0_axi_awvalid,
    output logic        m0_axi_awready,
    input  logic [31:0] m0_axi_awaddr,
    input  logic [ 2:0] m0_axi_awprot,

    input  logic        m0_axi_wvalid,
    output logic        m0_axi_wready,
    input  logic [31:0] m0_axi_wdata,
    input  logic [ 3:0] m0_axi_wstrb,

    output logic [1:0]  m0_axi_bresp,
    output logic        m0_axi_bvalid,
    input  logic        m0_axi_bready,

    input  logic        m0_axi_arvalid,
    output logic        m0_axi_arready,
    input  logic [31:0] m0_axi_araddr,
    input  logic [ 2:0] m0_axi_arprot,

    output logic        m0_axi_rvalid,
    input  logic        m0_axi_rready,
    output logic [1:0]  m0_axi_rresp,
    output logic [31:0] m0_axi_rdata,

    // Master 1 (Debug)
    input  logic        m1_axi_awvalid,
    output logic        m1_axi_awready,
    input  logic [31:0] m1_axi_awaddr,
    input  logic [ 2:0] m1_axi_awprot,

    input  logic        m1_axi_wvalid,
    output logic        m1_axi_wready,
    input  logic [31:0] m1_axi_wdata,
    input  logic [ 3:0] m1_axi_wstrb,

    output logic [1:0]  m1_axi_bresp,
    output logic        m1_axi_bvalid,
    input  logic        m1_axi_bready,

    input  logic        m1_axi_arvalid,
    output logic        m1_axi_arready,
    input  logic [31:0] m1_axi_araddr,
    input  logic [ 2:0] m1_axi_arprot,

    output logic        m1_axi_rvalid,
    input  logic        m1_axi_rready,
    output logic [1:0]  m1_axi_rresp,
    output logic [31:0] m1_axi_rdata,

    // Slave ports (same as axi_interconnect)
    output logic        s0_axi_awvalid,
    input  logic        s0_axi_awready,
    output logic [31:0] s0_axi_awaddr,
    output logic [ 2:0] s0_axi_awprot,

    output logic        s0_axi_wvalid,
    input  logic        s0_axi_wready,
    output logic [31:0] s0_axi_wdata,
    output logic [ 3:0] s0_axi_wstrb,

    input  logic        s0_axi_bvalid,
    output logic        s0_axi_bready,
    input  logic [1:0]  s0_axi_bresp,

    output logic        s0_axi_arvalid,
    input  logic        s0_axi_arready,
    output logic [31:0] s0_axi_araddr,
    output logic [ 2:0] s0_axi_arprot,

    input  logic        s0_axi_rvalid,
    output logic        s0_axi_rready,
    input  logic [1:0]  s0_axi_rresp,
    input  logic [31:0] s0_axi_rdata,

    output logic        s1_axi_awvalid,
    input  logic        s1_axi_awready,
    output logic [31:0] s1_axi_awaddr,
    output logic [ 2:0] s1_axi_awprot,

    output logic        s1_axi_wvalid,
    input  logic        s1_axi_wready,
    output logic [31:0] s1_axi_wdata,
    output logic [ 3:0] s1_axi_wstrb,

    input  logic        s1_axi_bvalid,
    output logic        s1_axi_bready,
    input  logic [1:0]  s1_axi_bresp,

    output logic        s1_axi_arvalid,
    input  logic        s1_axi_arready,
    output logic [31:0] s1_axi_araddr,
    output logic [ 2:0] s1_axi_arprot,

    input  logic        s1_axi_rvalid,
    output logic        s1_axi_rready,
    input  logic [1:0]  s1_axi_rresp,
    input  logic [31:0] s1_axi_rdata,

    output logic        s2_axi_awvalid,
    input  logic        s2_axi_awready,
    output logic [31:0] s2_axi_awaddr,
    output logic [ 2:0] s2_axi_awprot,

    output logic        s2_axi_wvalid,
    input  logic        s2_axi_wready,
    output logic [31:0] s2_axi_wdata,
    output logic [ 3:0] s2_axi_wstrb,

    input  logic        s2_axi_bvalid,
    output logic        s2_axi_bready,
    input  logic [1:0]  s2_axi_bresp,

    output logic        s2_axi_arvalid,
    input  logic        s2_axi_arready,
    output logic [31:0] s2_axi_araddr,
    output logic [ 2:0] s2_axi_arprot,

    input  logic        s2_axi_rvalid,
    output logic        s2_axi_rready,
    input  logic [1:0]  s2_axi_rresp,
    input  logic [31:0] s2_axi_rdata,

    output logic        s3_axi_awvalid,
    input  logic        s3_axi_awready,
    output logic [31:0] s3_axi_awaddr,
    output logic [ 2:0] s3_axi_awprot,

    output logic        s3_axi_wvalid,
    input  logic        s3_axi_wready,
    output logic [31:0] s3_axi_wdata,
    output logic [ 3:0] s3_axi_wstrb,

    input  logic        s3_axi_bvalid,
    output logic        s3_axi_bready,
    input  logic [1:0]  s3_axi_bresp,

    output logic        s3_axi_arvalid,
    input  logic        s3_axi_arready,
    output logic [31:0] s3_axi_araddr,
    output logic [ 2:0] s3_axi_arprot,

    input  logic        s3_axi_rvalid,
    output logic        s3_axi_rready,
    input  logic [1:0]  s3_axi_rresp,
    input  logic [31:0] s3_axi_rdata
);

    // Arbitration
    logic w_active;
    logic r_active;
    logic w_sel_hold;
    logic r_sel_hold;

    wire w_sel_next = m1_axi_awvalid ? 1'b1 : 1'b0;
    wire r_sel_next = m1_axi_arvalid ? 1'b1 : 1'b0;

    // Selected master -> interconnect
    logic        x_awvalid;
    logic        x_awready;
    logic [31:0] x_awaddr;
    logic [2:0]  x_awprot;

    logic        x_wvalid;
    logic        x_wready;
    logic [31:0] x_wdata;
    logic [3:0]  x_wstrb;

    logic        x_bvalid;
    logic [1:0]  x_bresp;
    logic        x_bready;

    logic        x_arvalid;
    logic        x_arready;
    logic [31:0] x_araddr;
    logic [2:0]  x_arprot;

    logic        x_rvalid;
    logic [1:0]  x_rresp;
    logic [31:0] x_rdata;
    logic        x_rready;

    always_ff @(posedge clk) begin
        if (!resetn) begin
            w_active <= 1'b0;
            r_active <= 1'b0;
            w_sel_hold <= 1'b0;
            r_sel_hold <= 1'b0;
        end else begin
            if (!w_active) begin
                if (x_awvalid && x_awready) begin
                    w_active <= 1'b1;
                    w_sel_hold <= w_sel_next;
                end
            end else if (x_bvalid && x_bready) begin
                w_active <= 1'b0;
            end

            if (!r_active) begin
                if (x_arvalid && x_arready) begin
                    r_active <= 1'b1;
                    r_sel_hold <= r_sel_next;
                end
            end else if (x_rvalid && x_rready) begin
                r_active <= 1'b0;
            end
        end
    end

    // Write address mux
    assign x_awvalid = (w_active ? (w_sel_hold ? m1_axi_awvalid : m0_axi_awvalid)
                                : (w_sel_next ? m1_axi_awvalid : m0_axi_awvalid));
    assign x_awaddr  = (w_active ? (w_sel_hold ? m1_axi_awaddr  : m0_axi_awaddr)
                                : (w_sel_next ? m1_axi_awaddr  : m0_axi_awaddr));
    assign x_awprot  = (w_active ? (w_sel_hold ? m1_axi_awprot  : m0_axi_awprot)
                                : (w_sel_next ? m1_axi_awprot  : m0_axi_awprot));

    assign m0_axi_awready = (!w_active && !w_sel_next) ? x_awready : (w_active && !w_sel_hold ? x_awready : 1'b0);
    assign m1_axi_awready = (!w_active &&  w_sel_next) ? x_awready : (w_active &&  w_sel_hold ? x_awready : 1'b0);

    // Write data mux (track selected master before and after address handshake)
    assign x_wvalid = (w_active ? (w_sel_hold ? m1_axi_wvalid : m0_axi_wvalid)
                               : (w_sel_next ? m1_axi_wvalid : m0_axi_wvalid));
    assign x_wdata  = (w_active ? (w_sel_hold ? m1_axi_wdata  : m0_axi_wdata)
                               : (w_sel_next ? m1_axi_wdata  : m0_axi_wdata));
    assign x_wstrb  = (w_active ? (w_sel_hold ? m1_axi_wstrb  : m0_axi_wstrb)
                               : (w_sel_next ? m1_axi_wstrb  : m0_axi_wstrb));

    assign m0_axi_wready = (w_active ? (!w_sel_hold ? x_wready : 1'b0)
                                     : (!w_sel_next ? x_wready : 1'b0));
    assign m1_axi_wready = (w_active ? ( w_sel_hold ? x_wready : 1'b0)
                                     : ( w_sel_next ? x_wready : 1'b0));

    // Write response demux
    assign x_bready = w_sel_hold ? m1_axi_bready : m0_axi_bready;

    assign m0_axi_bvalid = w_sel_hold ? 1'b0 : x_bvalid;
    assign m0_axi_bresp  = w_sel_hold ? 2'b00 : x_bresp;

    assign m1_axi_bvalid = w_sel_hold ? x_bvalid : 1'b0;
    assign m1_axi_bresp  = w_sel_hold ? x_bresp : 2'b00;

    // Read address mux
    assign x_arvalid = (r_active ? (r_sel_hold ? m1_axi_arvalid : m0_axi_arvalid)
                                : (r_sel_next ? m1_axi_arvalid : m0_axi_arvalid));
    assign x_araddr  = (r_active ? (r_sel_hold ? m1_axi_araddr  : m0_axi_araddr)
                                : (r_sel_next ? m1_axi_araddr  : m0_axi_araddr));
    assign x_arprot  = (r_active ? (r_sel_hold ? m1_axi_arprot  : m0_axi_arprot)
                                : (r_sel_next ? m1_axi_arprot  : m0_axi_arprot));

    assign m0_axi_arready = (!r_active && !r_sel_next) ? x_arready : (r_active && !r_sel_hold ? x_arready : 1'b0);
    assign m1_axi_arready = (!r_active &&  r_sel_next) ? x_arready : (r_active &&  r_sel_hold ? x_arready : 1'b0);

    // Read data demux
    assign x_rready = r_sel_hold ? m1_axi_rready : m0_axi_rready;

    assign m0_axi_rvalid = r_sel_hold ? 1'b0 : x_rvalid;
    assign m0_axi_rresp  = r_sel_hold ? 2'b00 : x_rresp;
    assign m0_axi_rdata  = r_sel_hold ? 32'h0 : x_rdata;

    assign m1_axi_rvalid = r_sel_hold ? x_rvalid : 1'b0;
    assign m1_axi_rresp  = r_sel_hold ? x_rresp : 2'b00;
    assign m1_axi_rdata  = r_sel_hold ? x_rdata : 32'h0;

    axi_interconnect u_xbar (
        .clk            (clk),
        .resetn         (resetn),
        .m_axi_awvalid  (x_awvalid),
        .m_axi_awready  (x_awready),
        .m_axi_awaddr   (x_awaddr),
        .m_axi_awprot   (x_awprot),
        .m_axi_wvalid   (x_wvalid),
        .m_axi_wready   (x_wready),
        .m_axi_wdata    (x_wdata),
        .m_axi_wstrb    (x_wstrb),
        .m_axi_bvalid   (x_bvalid),
        .m_axi_bready   (x_bready),
        .m_axi_bresp    (x_bresp),
        .m_axi_arvalid  (x_arvalid),
        .m_axi_arready  (x_arready),
        .m_axi_araddr   (x_araddr),
        .m_axi_arprot   (x_arprot),
        .m_axi_rvalid   (x_rvalid),
        .m_axi_rready   (x_rready),
        .m_axi_rresp    (x_rresp),
        .m_axi_rdata    (x_rdata),
        .s0_axi_awvalid (s0_axi_awvalid),
        .s0_axi_awready (s0_axi_awready),
        .s0_axi_awaddr  (s0_axi_awaddr),
        .s0_axi_awprot  (s0_axi_awprot),
        .s0_axi_wvalid  (s0_axi_wvalid),
        .s0_axi_wready  (s0_axi_wready),
        .s0_axi_wdata   (s0_axi_wdata),
        .s0_axi_wstrb   (s0_axi_wstrb),
        .s0_axi_bvalid  (s0_axi_bvalid),
        .s0_axi_bready  (s0_axi_bready),
        .s0_axi_bresp   (s0_axi_bresp),
        .s0_axi_arvalid (s0_axi_arvalid),
        .s0_axi_arready (s0_axi_arready),
        .s0_axi_araddr  (s0_axi_araddr),
        .s0_axi_arprot  (s0_axi_arprot),
        .s0_axi_rvalid  (s0_axi_rvalid),
        .s0_axi_rready  (s0_axi_rready),
        .s0_axi_rresp   (s0_axi_rresp),
        .s0_axi_rdata   (s0_axi_rdata),
        .s1_axi_awvalid (s1_axi_awvalid),
        .s1_axi_awready (s1_axi_awready),
        .s1_axi_awaddr  (s1_axi_awaddr),
        .s1_axi_awprot  (s1_axi_awprot),
        .s1_axi_wvalid  (s1_axi_wvalid),
        .s1_axi_wready  (s1_axi_wready),
        .s1_axi_wdata   (s1_axi_wdata),
        .s1_axi_wstrb   (s1_axi_wstrb),
        .s1_axi_bvalid  (s1_axi_bvalid),
        .s1_axi_bready  (s1_axi_bready),
        .s1_axi_bresp   (s1_axi_bresp),
        .s1_axi_arvalid (s1_axi_arvalid),
        .s1_axi_arready (s1_axi_arready),
        .s1_axi_araddr  (s1_axi_araddr),
        .s1_axi_arprot  (s1_axi_arprot),
        .s1_axi_rvalid  (s1_axi_rvalid),
        .s1_axi_rready  (s1_axi_rready),
        .s1_axi_rresp   (s1_axi_rresp),
        .s1_axi_rdata   (s1_axi_rdata),
        .s2_axi_awvalid (s2_axi_awvalid),
        .s2_axi_awready (s2_axi_awready),
        .s2_axi_awaddr  (s2_axi_awaddr),
        .s2_axi_awprot  (s2_axi_awprot),
        .s2_axi_wvalid  (s2_axi_wvalid),
        .s2_axi_wready  (s2_axi_wready),
        .s2_axi_wdata   (s2_axi_wdata),
        .s2_axi_wstrb   (s2_axi_wstrb),
        .s2_axi_bvalid  (s2_axi_bvalid),
        .s2_axi_bready  (s2_axi_bready),
        .s2_axi_bresp   (s2_axi_bresp),
        .s2_axi_arvalid (s2_axi_arvalid),
        .s2_axi_arready (s2_axi_arready),
        .s2_axi_araddr  (s2_axi_araddr),
        .s2_axi_arprot  (s2_axi_arprot),
        .s2_axi_rvalid  (s2_axi_rvalid),
        .s2_axi_rready  (s2_axi_rready),
        .s2_axi_rresp   (s2_axi_rresp),
        .s2_axi_rdata   (s2_axi_rdata),
        .s3_axi_awvalid (s3_axi_awvalid),
        .s3_axi_awready (s3_axi_awready),
        .s3_axi_awaddr  (s3_axi_awaddr),
        .s3_axi_awprot  (s3_axi_awprot),
        .s3_axi_wvalid  (s3_axi_wvalid),
        .s3_axi_wready  (s3_axi_wready),
        .s3_axi_wdata   (s3_axi_wdata),
        .s3_axi_wstrb   (s3_axi_wstrb),
        .s3_axi_bvalid  (s3_axi_bvalid),
        .s3_axi_bready  (s3_axi_bready),
        .s3_axi_bresp   (s3_axi_bresp),
        .s3_axi_arvalid (s3_axi_arvalid),
        .s3_axi_arready (s3_axi_arready),
        .s3_axi_araddr  (s3_axi_araddr),
        .s3_axi_arprot  (s3_axi_arprot),
        .s3_axi_rvalid  (s3_axi_rvalid),
        .s3_axi_rready  (s3_axi_rready),
        .s3_axi_rresp   (s3_axi_rresp),
        .s3_axi_rdata   (s3_axi_rdata)
    );

endmodule
