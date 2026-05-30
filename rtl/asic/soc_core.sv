module soc_core #(
    parameter MEM_INIT_FILE       = "",
    parameter SRAM_INIT_FILE      = "",
    parameter BOOTROM_ADDR_WIDTH  = 8,  // 256 bytes (2^8 bytes = 0x00-0xFF)
    parameter PROGADDR_IRQ        = 32'h00010010 // Default: SRAM
)(
    input  logic         clk_i,
    input  logic         rst_ni,
    // UART
    output logic         uart_tx_o,
    input  logic         uart_rx_i,
    // GPIO
    input  logic [31:0]  gpio_in_i,
    output logic [31:0]  gpio_out_o,
    output logic [31:0]  gpio_oe_o,
    // SPI Master
    output logic         spi_sclk_o,
    output logic         spi_mosi_o,
    input  logic         spi_miso_i,
    output logic [3:0]   spi_cs_n_o,
    // Flash QSPI
    output logic         flash_sclk_o,
    output logic         flash_cs_n_o,
    output logic         flash_mosi_o,
    input  logic         flash_miso_i,
    // JTAG
    input  logic         jtag_tck_i,
    input  logic         jtag_tms_i,
    input  logic         jtag_tdi_i,
    output logic         jtag_tdo_o,
    // Status
    output logic         trap_o
);

    // ------------------------------------------------------------
    // Core <-> AXI fabric signals
    // ------------------------------------------------------------
    logic        mem_axi_awvalid;
    logic        mem_axi_awready;
    logic [31:0] mem_axi_awaddr;
    logic [2:0]  mem_axi_awprot;

    logic        mem_axi_wvalid;
    logic        mem_axi_wready;
    logic [31:0] mem_axi_wdata;
    logic [3:0]  mem_axi_wstrb;

    logic        mem_axi_bvalid;
    logic        mem_axi_bready;

    logic        mem_axi_arvalid;
    logic        mem_axi_arready;
    logic [31:0] mem_axi_araddr;
    logic [2:0]  mem_axi_arprot;

    logic        mem_axi_rvalid;
    logic        mem_axi_rready;
    logic [31:0] mem_axi_rdata;
    logic [1:0]  mem_axi_bresp;
    logic [1:0]  mem_axi_rresp;

    // Debug AXI master
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
    logic [31:0] dbg_axi_rdata;
    logic [1:0]  dbg_axi_rresp;

    logic [31:0] cpu_irq;
    logic [31:0] cpu_eoi;

    // ------------------------------------------------------------
    // AXI Interconnect <-> Slave signals
    // ------------------------------------------------------------
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

    // ------------------------------------------------------------
    // APB bridge/interconnect signals
    // ------------------------------------------------------------
    logic        apb_psel;
    logic        apb_penable;
    logic        apb_pwrite;
    logic [31:0] apb_paddr;
    logic [31:0] apb_pwdata;
    logic [3:0]  apb_pstrb;
    logic [2:0]  apb_pprot;
    logic [31:0] apb_prdata;
    logic        apb_pready;
    logic        apb_pslverr;

    logic        psel_uart, penable_uart, pwrite_uart, pready_uart, pslverr_uart;
    logic [31:0] paddr_uart, pwdata_uart, prdata_uart;
    logic [3:0]  pstrb_uart;
    logic [2:0]  pprot_uart;

    logic        psel_timer, penable_timer, pwrite_timer, pready_timer, pslverr_timer;
    logic [31:0] paddr_timer, pwdata_timer, prdata_timer;
    logic [3:0]  pstrb_timer;
    logic [2:0]  pprot_timer;

    logic        psel_gpio, penable_gpio, pwrite_gpio, pready_gpio, pslverr_gpio;
    logic [31:0] paddr_gpio, pwdata_gpio, prdata_gpio;
    logic [3:0]  pstrb_gpio;
    logic [2:0]  pprot_gpio;

    logic        psel_spi, penable_spi, pwrite_spi, pready_spi, pslverr_spi;
    logic [31:0] paddr_spi, pwdata_spi, prdata_spi;
    logic [3:0]  pstrb_spi;
    logic [2:0]  pprot_spi;

    logic        psel_debug, penable_debug, pwrite_debug, pready_debug, pslverr_debug;
    logic [31:0] paddr_debug, pwdata_debug, prdata_debug;
    logic [3:0]  pstrb_debug;
    logic [2:0]  pprot_debug;

    // ------------------------------------------------------------
    // Peripheral wires (directly driven by peripheral instances)
    // ------------------------------------------------------------
    logic        uart_irq, timer_irq, spi_irq_w, debug_irq;
    logic        gpio_irq_w;
    logic        dbg_cpu_reset_req;
    logic        dbg_halt_req;
    logic        dbg_resume_req;
    logic        dbg_halted;
    logic        dbg_reg_write;
    logic        dbg_reg_read;
    logic [4:0]  dbg_reg_addr;
    logic [31:0] dbg_reg_wdata;
    logic [31:0] dbg_reg_rdata;
    logic [31:0] dbg_cpu_pc;
    logic        dbg_set_pc;
    logic [31:0] dbg_set_pc_val;
    // JTAG <-> Debug bridge
    logic        jdbg_valid, jdbg_write, jdbg_ready;
    logic [7:0]  jdbg_addr;
    logic [31:0] jdbg_wdata, jdbg_rdata;
    logic [3:0]  jdbg_wstrb;
    // Flash controller status
    logic        flash_ready;
    logic [23:0] flash_jedec_id;
    logic        xip_active;

    // ------------------------------------------------------------
    // CPU core
    // ------------------------------------------------------------
    picorv32_axi #(
        .ENABLE_IRQ        (1),
        .ENABLE_IRQ_QREGS  (1),
        .ENABLE_IRQ_TIMER  (1),
        .PROGADDR_RESET    (32'h0000_0000),    // Boot ROM reset vector
        .PROGADDR_IRQ      (PROGADDR_IRQ),    // IRQ vector in SRAM (linker: .org 0x10 in SRAM)
        .STACKADDR         (32'h0001_3FFC)     // Top of 16KB SRAM
    ) u_cpu (
        .clk            (clk_i),
        .resetn         (rst_ni),
        .trap           (trap_o),
        .irq            (cpu_irq),
        .eoi            (cpu_eoi),
        .dbg_halt_req   (dbg_halt_req),
        .dbg_resume_req (dbg_resume_req),
        .dbg_reg_write  (dbg_reg_write),
        .dbg_reg_read   (dbg_reg_read),
        .dbg_reg_addr   (dbg_reg_addr),
        .dbg_reg_wdata  (dbg_reg_wdata),
        .dbg_halted     (dbg_halted),
        .dbg_reg_rdata  (dbg_reg_rdata),
        .dbg_pc         (dbg_cpu_pc),
        .dbg_set_pc     (dbg_set_pc),
        .dbg_set_pc_val (dbg_set_pc_val),
        .mem_axi_awvalid(mem_axi_awvalid),
        .mem_axi_awready(mem_axi_awready),
        .mem_axi_awaddr (mem_axi_awaddr),
        .mem_axi_awprot (mem_axi_awprot),
        .mem_axi_wvalid (mem_axi_wvalid),
        .mem_axi_wready (mem_axi_wready),
        .mem_axi_wdata  (mem_axi_wdata),
        .mem_axi_wstrb  (mem_axi_wstrb),
        .mem_axi_bvalid (mem_axi_bvalid),
        .mem_axi_bready (mem_axi_bready),
        .mem_axi_arvalid(mem_axi_arvalid),
        .mem_axi_arready(mem_axi_arready),
        .mem_axi_araddr (mem_axi_araddr),
        .mem_axi_arprot (mem_axi_arprot),
        .mem_axi_rvalid (mem_axi_rvalid),
        .mem_axi_rready (mem_axi_rready),
        .mem_axi_rdata  (mem_axi_rdata),
        .trace_valid    (),
        .trace_data     ()
    );

    axi_interconnect_2m u_axi_xbar (
        .clk            (clk_i),
        .resetn         (rst_ni),
        .m0_axi_awvalid (mem_axi_awvalid),
        .m0_axi_awready (mem_axi_awready),
        .m0_axi_awaddr  (mem_axi_awaddr),
        .m0_axi_awprot  (mem_axi_awprot),
        .m0_axi_wvalid  (mem_axi_wvalid),
        .m0_axi_wready  (mem_axi_wready),
        .m0_axi_wdata   (mem_axi_wdata),
        .m0_axi_wstrb   (mem_axi_wstrb),
        .m0_axi_bvalid  (mem_axi_bvalid),
        .m0_axi_bready  (mem_axi_bready),
        .m0_axi_bresp   (mem_axi_bresp),
        .m0_axi_arvalid (mem_axi_arvalid),
        .m0_axi_arready (mem_axi_arready),
        .m0_axi_araddr  (mem_axi_araddr),
        .m0_axi_arprot  (mem_axi_arprot),
        .m0_axi_rvalid  (mem_axi_rvalid),
        .m0_axi_rready  (mem_axi_rready),
        .m0_axi_rresp   (mem_axi_rresp),
        .m0_axi_rdata   (mem_axi_rdata),
        .m1_axi_awvalid (dbg_axi_awvalid),
        .m1_axi_awready (dbg_axi_awready),
        .m1_axi_awaddr  (dbg_axi_awaddr),
        .m1_axi_awprot  (dbg_axi_awprot),
        .m1_axi_wvalid  (dbg_axi_wvalid),
        .m1_axi_wready  (dbg_axi_wready),
        .m1_axi_wdata   (dbg_axi_wdata),
        .m1_axi_wstrb   (dbg_axi_wstrb),
        .m1_axi_bvalid  (dbg_axi_bvalid),
        .m1_axi_bready  (dbg_axi_bready),
        .m1_axi_bresp   (dbg_axi_bresp),
        .m1_axi_arvalid (dbg_axi_arvalid),
        .m1_axi_arready (dbg_axi_arready),
        .m1_axi_araddr  (dbg_axi_araddr),
        .m1_axi_arprot  (dbg_axi_arprot),
        .m1_axi_rvalid  (dbg_axi_rvalid),
        .m1_axi_rready  (dbg_axi_rready),
        .m1_axi_rresp   (dbg_axi_rresp),
        .m1_axi_rdata   (dbg_axi_rdata),
        .s0_axi_awvalid (s0_awvalid), .s0_axi_awready(s0_awready),
        .s0_axi_awaddr  (s0_awaddr),  .s0_axi_awprot (s0_awprot),
        .s0_axi_wvalid  (s0_wvalid),  .s0_axi_wready (s0_wready),
        .s0_axi_wdata   (s0_wdata),   .s0_axi_wstrb  (s0_wstrb),
        .s0_axi_bvalid  (s0_bvalid),  .s0_axi_bready (s0_bready),
        .s0_axi_bresp   (s0_bresp),
        .s0_axi_arvalid (s0_arvalid), .s0_axi_arready(s0_arready),
        .s0_axi_araddr  (s0_araddr),  .s0_axi_arprot (s0_arprot),
        .s0_axi_rvalid  (s0_rvalid),  .s0_axi_rready (s0_rready),
        .s0_axi_rresp   (s0_rresp),   .s0_axi_rdata  (s0_rdata),
        .s1_axi_awvalid (s1_awvalid), .s1_axi_awready(s1_awready),
        .s1_axi_awaddr  (s1_awaddr),  .s1_axi_awprot (s1_awprot),
        .s1_axi_wvalid  (s1_wvalid),  .s1_axi_wready (s1_wready),
        .s1_axi_wdata   (s1_wdata),   .s1_axi_wstrb  (s1_wstrb),
        .s1_axi_bvalid  (s1_bvalid),  .s1_axi_bready (s1_bready),
        .s1_axi_bresp   (s1_bresp),
        .s1_axi_arvalid (s1_arvalid), .s1_axi_arready(s1_arready),
        .s1_axi_araddr  (s1_araddr),  .s1_axi_arprot (s1_arprot),
        .s1_axi_rvalid  (s1_rvalid),  .s1_axi_rready (s1_rready),
        .s1_axi_rresp   (s1_rresp),   .s1_axi_rdata  (s1_rdata),
        .s2_axi_awvalid (s2_awvalid), .s2_axi_awready(s2_awready),
        .s2_axi_awaddr  (s2_awaddr),  .s2_axi_awprot (s2_awprot),
        .s2_axi_wvalid  (s2_wvalid),  .s2_axi_wready (s2_wready),
        .s2_axi_wdata   (s2_wdata),   .s2_axi_wstrb  (s2_wstrb),
        .s2_axi_bvalid  (s2_bvalid),  .s2_axi_bready (s2_bready),
        .s2_axi_bresp   (s2_bresp),
        .s2_axi_arvalid (s2_arvalid), .s2_axi_arready(s2_arready),
        .s2_axi_araddr  (s2_araddr),  .s2_axi_arprot (s2_arprot),
        .s2_axi_rvalid  (s2_rvalid),  .s2_axi_rready (s2_rready),
        .s2_axi_rresp   (s2_rresp),   .s2_axi_rdata  (s2_rdata),
        .s3_axi_awvalid (s3_awvalid), .s3_axi_awready(s3_awready),
        .s3_axi_awaddr  (s3_awaddr),  .s3_axi_awprot (s3_awprot),
        .s3_axi_wvalid  (s3_wvalid),  .s3_axi_wready (s3_wready),
        .s3_axi_wdata   (s3_wdata),   .s3_axi_wstrb  (s3_wstrb),
        .s3_axi_bvalid  (s3_bvalid),  .s3_axi_bready (s3_bready),
        .s3_axi_bresp   (s3_bresp),
        .s3_axi_arvalid (s3_arvalid), .s3_axi_arready(s3_arready),
        .s3_axi_araddr  (s3_araddr),  .s3_axi_arprot (s3_arprot),
        .s3_axi_rvalid  (s3_rvalid),  .s3_axi_rready (s3_rready),
        .s3_axi_rresp   (s3_rresp),   .s3_axi_rdata  (s3_rdata)
    );

    bootrom #(
        .ADDR_WIDTH   (BOOTROM_ADDR_WIDTH),
        .DATA_WIDTH   (32),
        .MEM_INIT_FILE(MEM_INIT_FILE)
    ) u_bootrom (
        .clk         (clk_i),
        .resetn      (rst_ni),
        .axi_awaddr  (s0_awaddr[BOOTROM_ADDR_WIDTH-1:0]),
        .axi_awprot  (s0_awprot),
        .axi_awvalid (s0_awvalid),
        .axi_awready (s0_awready),
        .axi_wdata   (s0_wdata),
        .axi_wvalid  (s0_wvalid),
        .axi_wready  (s0_wready),
        .axi_wstrb   (s0_wstrb),
        .axi_bvalid  (s0_bvalid),
        .axi_bready  (s0_bready),
        .axi_bresp   (s0_bresp),
        .axi_araddr  (s0_araddr[BOOTROM_ADDR_WIDTH-1:0]),
        .axi_arprot  (s0_arprot),
        .axi_arvalid (s0_arvalid),
        .axi_arready (s0_arready),
        .axi_rdata   (s0_rdata),
        .axi_rvalid  (s0_rvalid),
        .axi_rready  (s0_rready),
        .axi_rresp   (s0_rresp)
    );

    sram_axi #(
        .ADDR_WIDTH(14),
        .DATA_WIDTH(32),
        .SRAM_INIT_FILE(SRAM_INIT_FILE)
    ) u_sram (
        .clk         (clk_i),
        .resetn      (rst_ni),
        .axi_awaddr  (s1_awaddr[13:0]),
        .axi_awprot  (s1_awprot),
        .axi_awvalid (s1_awvalid),
        .axi_awready (s1_awready),
        .axi_wdata   (s1_wdata),
        .axi_wvalid  (s1_wvalid),
        .axi_wready  (s1_wready),
        .axi_wstrb   (s1_wstrb),
        .axi_bvalid  (s1_bvalid),
        .axi_bready  (s1_bready),
        .axi_bresp   (s1_bresp),
        .axi_araddr  (s1_araddr[13:0]),
        .axi_arprot  (s1_arprot),
        .axi_arvalid (s1_arvalid),
        .axi_arready (s1_arready),
        .axi_rdata   (s1_rdata),
        .axi_rvalid  (s1_rvalid),
        .axi_rready  (s1_rready),
        .axi_rresp   (s1_rresp)
    );

    flash_ctrl u_flash (
        .clk         (clk_i),
        .resetn      (rst_ni),
        // Register AXI port (directly on S2 for addresses < 0x100)
        .axi_awaddr  (s2_awaddr[7:0]),
        .axi_awprot  (s2_awprot),
        .axi_awvalid (s2_awvalid),
        .axi_awready (s2_awready),
        .axi_wdata   (s2_wdata),
        .axi_wvalid  (s2_wvalid),
        .axi_wready  (s2_wready),
        .axi_wstrb   (s2_wstrb),
        .axi_bvalid  (s2_bvalid),
        .axi_bready  (s2_bready),
        .axi_bresp   (s2_bresp),
        .axi_araddr  (s2_araddr[7:0]),
        .axi_arprot  (s2_arprot),
        .axi_arvalid (s2_arvalid),
        .axi_arready (s2_arready),
        .axi_rdata   (s2_rdata),
        .axi_rvalid  (s2_rvalid),
        .axi_rready  (s2_rready),
        .axi_rresp   (s2_rresp),
        // XIP port — directly memory-mapped reads (active when xip_en)
        .xip_araddr  (32'h0),
        .xip_arvalid (1'b0),
        .xip_arready (),
        .xip_rdata   (),
        .xip_rvalid  (),
        .xip_rready  (1'b0),
        .xip_rresp   (),
        .xip_awaddr  (32'h0),
        .xip_awvalid (1'b0),
        .xip_awready (),
        .xip_wdata   (32'h0),
        .xip_wvalid  (1'b0),
        .xip_wready  (),
        .xip_wstrb   (4'h0),
        .xip_bvalid  (),
        .xip_bready  (1'b0),
        .xip_bresp   (),
        // QSPI pins
        .flash_sclk  (flash_sclk_o),
        .flash_cs_n  (flash_cs_n_o),
        .flash_mosi  (flash_mosi_o),
        .flash_miso  (flash_miso_i),
        // Status
        .flash_ready (flash_ready),
        .jedec_id    (flash_jedec_id),
        .xip_active  (xip_active)
    );

    axi2apb_bridge u_axi2apb (
        .clk       (clk_i),
        .resetn    (rst_ni),
        .axi_awvalid(s3_awvalid),
        .axi_awready(s3_awready),
        .axi_awaddr (s3_awaddr),
        .axi_awprot (s3_awprot),
        .axi_wvalid (s3_wvalid),
        .axi_wready (s3_wready),
        .axi_wdata  (s3_wdata),
        .axi_wstrb  (s3_wstrb),
        .axi_bvalid (s3_bvalid),
        .axi_bready (s3_bready),
        .axi_bresp  (s3_bresp),
        .axi_arvalid(s3_arvalid),
        .axi_arready(s3_arready),
        .axi_araddr (s3_araddr),
        .axi_arprot (s3_arprot),
        .axi_rvalid (s3_rvalid),
        .axi_rready (s3_rready),
        .axi_rdata  (s3_rdata),
        .axi_rresp  (s3_rresp),
        .apb_psel   (apb_psel),
        .apb_penable(apb_penable),
        .apb_pwrite (apb_pwrite),
        .apb_paddr  (apb_paddr),
        .apb_pwdata (apb_pwdata),
        .apb_pstrb  (apb_pstrb),
        .apb_pprot  (apb_pprot),
        .apb_prdata (apb_prdata),
        .apb_pready (apb_pready),
        .apb_pslverr(apb_pslverr)
    );

    apb_interconnect u_apb_xbar (
        .clk          (clk_i),
        .resetn       (rst_ni),
        .psel_i       (apb_psel),
        .penable_i    (apb_penable),
        .pwrite_i     (apb_pwrite),
        .paddr_i      (apb_paddr),
        .pwdata_i     (apb_pwdata),
        .pstrb_i      (apb_pstrb),
        .pprot_i      (apb_pprot),
        .prdata_o     (apb_prdata),
        .pready_o     (apb_pready),
        .pslverr_o    (apb_pslverr),
        .psel_uart    (psel_uart),
        .penable_uart (penable_uart),
        .pwrite_uart  (pwrite_uart),
        .paddr_uart   (paddr_uart),
        .pwdata_uart  (pwdata_uart),
        .pstrb_uart   (pstrb_uart),
        .pprot_uart   (pprot_uart),
        .prdata_uart  (prdata_uart),
        .pready_uart  (pready_uart),
        .pslverr_uart (pslverr_uart),
        .psel_timer   (psel_timer),
        .penable_timer(penable_timer),
        .pwrite_timer (pwrite_timer),
        .paddr_timer  (paddr_timer),
        .pwdata_timer (pwdata_timer),
        .pstrb_timer  (pstrb_timer),
        .pprot_timer  (pprot_timer),
        .prdata_timer (prdata_timer),
        .pready_timer (pready_timer),
        .pslverr_timer(pslverr_timer),
        .psel_gpio    (psel_gpio),
        .penable_gpio (penable_gpio),
        .pwrite_gpio  (pwrite_gpio),
        .paddr_gpio   (paddr_gpio),
        .pwdata_gpio  (pwdata_gpio),
        .pstrb_gpio   (pstrb_gpio),
        .pprot_gpio   (pprot_gpio),
        .prdata_gpio  (prdata_gpio),
        .pready_gpio  (pready_gpio),
        .pslverr_gpio (pslverr_gpio),
        .psel_spi     (psel_spi),
        .penable_spi  (penable_spi),
        .pwrite_spi   (pwrite_spi),
        .paddr_spi    (paddr_spi),
        .pwdata_spi   (pwdata_spi),
        .pstrb_spi    (pstrb_spi),
        .pprot_spi    (pprot_spi),
        .prdata_spi   (prdata_spi),
        .pready_spi   (pready_spi),
        .pslverr_spi  (pslverr_spi),
        .psel_debug   (psel_debug),
        .penable_debug(penable_debug),
        .pwrite_debug (pwrite_debug),
        .paddr_debug  (paddr_debug),
        .pwdata_debug (pwdata_debug),
        .pstrb_debug  (pstrb_debug),
        .pprot_debug  (pprot_debug),
        .prdata_debug (prdata_debug),
        .pready_debug (pready_debug),
        .pslverr_debug(pslverr_debug)
    );

    //========================================
    // Peripherals (ASIC-safe subset)
    //========================================

    // UART
    uart_ctrl_apb u_uart (
        .clk        (clk_i),
        .resetn     (rst_ni),
        .psel       (psel_uart),
        .penable    (penable_uart),
        .pwrite     (pwrite_uart),
        .paddr      (paddr_uart),
        .pwdata     (pwdata_uart),
        .pstrb      (pstrb_uart),
        .pprot      (pprot_uart),
        .prdata     (prdata_uart),
        .pready     (pready_uart),
        .pslverr    (pslverr_uart),
        .uart_tx    (uart_tx_o),
        .uart_rx    (uart_rx_i),
        .irq        (uart_irq)
    );

    // Timer
    timer_apb u_timer (
        .clk        (clk_i),
        .resetn     (rst_ni),
        .psel       (psel_timer),
        .penable    (penable_timer),
        .pwrite     (pwrite_timer),
        .paddr      (paddr_timer),
        .pwdata     (pwdata_timer),
        .pstrb      (pstrb_timer),
        .pprot      (pprot_timer),
        .prdata     (prdata_timer),
        .pready     (pready_timer),
        .pslverr    (pslverr_timer),
        .timer_irq  (timer_irq)
    );

    // GPIO
    gpio_apb u_gpio (
        .clk        (clk_i),
        .resetn     (rst_ni),
        .psel       (psel_gpio),
        .penable    (penable_gpio),
        .pwrite     (pwrite_gpio),
        .paddr      (paddr_gpio),
        .pwdata     (pwdata_gpio),
        .pstrb      (pstrb_gpio),
        .pprot      (pprot_gpio),
        .prdata     (prdata_gpio),
        .pready     (pready_gpio),
        .pslverr    (pslverr_gpio),
        .gpio_in    (gpio_in_i),
        .gpio_out   (gpio_out_o),
        .gpio_oe    (gpio_oe_o),
        .gpio_pue   (),
        .gpio_ds    (),
        .iof_en     (),
        .iof_sel    (),
        .gpio_irq   (gpio_irq_w)
    );

    // SPI Master
    spi_master_apb u_spi (
        .clk        (clk_i),
        .resetn     (rst_ni),
        .psel       (psel_spi),
        .penable    (penable_spi),
        .pwrite     (pwrite_spi),
        .paddr      (paddr_spi),
        .pwdata     (pwdata_spi),
        .pstrb      (pstrb_spi),
        .pprot      (pprot_spi),
        .prdata     (prdata_spi),
        .pready     (pready_spi),
        .pslverr    (pslverr_spi),
        .spi_sclk   (spi_sclk_o),
        .spi_mosi   (spi_mosi_o),
        .spi_miso   (spi_miso_i),
        .spi_cs_n   (spi_cs_n_o),
        .irq        (spi_irq_w)
    );

    debug_dm u_debug (
        .clk        (clk_i),
        .resetn     (rst_ni),
        .psel       (psel_debug),
        .penable    (penable_debug),
        .pwrite     (pwrite_debug),
        .paddr      (paddr_debug),
        .pwdata     (pwdata_debug),
        .pstrb      (pstrb_debug),
        .pprot      (pprot_debug),
        .prdata     (prdata_debug),
        .pready     (pready_debug),
        .pslverr    (pslverr_debug),
        .jtag_valid (jdbg_valid),
        .jtag_write (jdbg_write),
        .jtag_addr  (jdbg_addr),
        .jtag_wdata (jdbg_wdata),
        .jtag_wstrb (jdbg_wstrb),
        .jtag_rdata (jdbg_rdata),
        .jtag_ready (jdbg_ready),
        .dbg_halt_req (dbg_halt_req),
        .dbg_resume_req (dbg_resume_req),
        .dbg_halted (dbg_halted),
        .dbg_reg_write (dbg_reg_write),
        .dbg_reg_read (dbg_reg_read),
        .dbg_reg_addr (dbg_reg_addr),
        .dbg_reg_wdata (dbg_reg_wdata),
        .dbg_reg_rdata (dbg_reg_rdata),
        .dbg_cpu_pc    (dbg_cpu_pc),
        .dbg_set_pc    (dbg_set_pc),
        .dbg_set_pc_val(dbg_set_pc_val),
        .dbg_axi_awvalid (dbg_axi_awvalid),
        .dbg_axi_awready (dbg_axi_awready),
        .dbg_axi_awaddr (dbg_axi_awaddr),
        .dbg_axi_awprot (dbg_axi_awprot),
        .dbg_axi_wvalid (dbg_axi_wvalid),
        .dbg_axi_wready (dbg_axi_wready),
        .dbg_axi_wdata (dbg_axi_wdata),
        .dbg_axi_wstrb (dbg_axi_wstrb),
        .dbg_axi_bvalid (dbg_axi_bvalid),
        .dbg_axi_bready (dbg_axi_bready),
        .dbg_axi_bresp (dbg_axi_bresp),
        .dbg_axi_arvalid (dbg_axi_arvalid),
        .dbg_axi_arready (dbg_axi_arready),
        .dbg_axi_araddr (dbg_axi_araddr),
        .dbg_axi_arprot (dbg_axi_arprot),
        .dbg_axi_rvalid (dbg_axi_rvalid),
        .dbg_axi_rready (dbg_axi_rready),
        .dbg_axi_rresp (dbg_axi_rresp),
        .dbg_axi_rdata (dbg_axi_rdata),
        .debug_irq  (debug_irq),
        .cpu_reset_req(dbg_cpu_reset_req)
    );

    jtag_dtm u_jtag_dtm (
        .tck        (jtag_tck_i),
        .tms        (jtag_tms_i),
        .tdi        (jtag_tdi_i),
        .tdo        (jtag_tdo_o),
        .clk        (clk_i),
        .resetn     (rst_ni),
        .dbg_valid  (jdbg_valid),
        .dbg_write  (jdbg_write),
        .dbg_addr   (jdbg_addr),
        .dbg_wdata  (jdbg_wdata),
        .dbg_wstrb  (jdbg_wstrb),
        .dbg_rdata  (jdbg_rdata),
        .dbg_ready  (jdbg_ready)
    );

    //========================================
    // Interrupt Aggregation
    //========================================

    irq_aggregator u_irq_aggregator (
        .clk        (clk_i),
        .resetn     (rst_ni),
        .uart_irq   (uart_irq),
        .gpio_irq   (gpio_irq_w),
        .timer_irq  (timer_irq),
        .spi_irq    (spi_irq_w),
        .debug_irq  (debug_irq),
        .eoi        (cpu_eoi),
        .irq        (cpu_irq)
    );

endmodule