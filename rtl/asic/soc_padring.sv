/*
 * soc_padring.sv — sky130_fd_io pad ring for SkyForge SoC
 *
 * Pin-to-edge assignment matches 2400x2000 area-optimised floorplan:
 *   EAST  — CLK, RST, UART, JTAG, SPI, GPIO[15:0]
 *   WEST  — FLASH QSPI, GPIO[31:16]
 *   SOUTH — TRAP
 *   NORTH — VDD/GND power pads only (macros block signal routing)
 *
 * Cell: sky130_fd_io__top_gpio_ovtv2
 *   OUT    — core drives pad (when OE_N=0)
 *   OE_N   — output enable, active-low (0=output, 1=input)
 *   IN     — pad value read by core
 *   DM[2:0]— drive mode: 3'b001=input, 3'b110=output strong
 *   INP_DIS— disable input buffer (1 for output-only pads)
 *
 * NOTE: This is a structural reference wrapper. soc_core is the
 * LibreLane tapeout target. Do NOT add this to VERILOG_FILES.
 */
module soc_padring (
    inout  wire        pad_clk,
    inout  wire        pad_rst_n,
    inout  wire        pad_uart_tx,
    inout  wire        pad_uart_rx,
    inout  wire        pad_trap,
    inout  wire [31:0] pad_gpio,
    inout  wire        pad_spi_sclk,
    inout  wire        pad_spi_mosi,
    inout  wire        pad_spi_miso,
    inout  wire [3:0]  pad_spi_cs_n,
    inout  wire        pad_flash_sclk,
    inout  wire        pad_flash_cs_n,
    inout  wire        pad_flash_mosi,
    inout  wire        pad_flash_miso,
    inout  wire        pad_jtag_tck,
    inout  wire        pad_jtag_tms,
    inout  wire        pad_jtag_tdi,
    inout  wire        pad_jtag_tdo,
    inout  wire        vccd1,
    inout  wire        vssd1
);

    wire clk_c, rst_n_c, uart_tx_c, uart_rx_c, trap_c;
    wire [31:0] gpio_in_c, gpio_out_c, gpio_oe_c;
    wire spi_sclk_c, spi_mosi_c, spi_miso_c;
    wire [3:0] spi_cs_n_c;
    wire flash_sclk_c, flash_cs_n_c, flash_mosi_c, flash_miso_c;
    wire jtag_tck_c, jtag_tms_c, jtag_tdi_c, jtag_tdo_c;

    // Macro for input pad
    `define IN_PAD(NAME_INST, PAD_SIG, CORE_SIG) \
        sky130_ef_io__gpiov2_pad_wrapped NAME_INST ( \
            .PAD(PAD_SIG), .OUT(1'b0), .OE_N(1'b1), .IN(CORE_SIG), .IN_H(), \
            .TIE_HI_ESD(), .TIE_LO_ESD(), \
            .VCCD(vccd1), .VSSD(vssd1), .VDDIO(vccd1), .VSSIO(vssd1), \
            .SLOW(1'b0), .VTRIP_SEL(1'b0), .HLD_H_N(1'b1), .HLD_OVR(1'b0), \
            .INP_DIS(1'b0), .IB_MODE_SEL(1'b0), \
            .ANALOG_EN(1'b0), .ANALOG_SEL(1'b0), .ANALOG_POL(1'b0), \
            .DM(3'b001), .AMUXBUS_A(), .AMUXBUS_B(), \
            .PAD_A_NOESD_H(), .PAD_A_ESD_0_H(), .PAD_A_ESD_1_H());

    // Macro for output pad
    `define OUT_PAD(NAME_INST, PAD_SIG, CORE_SIG) \
        sky130_ef_io__gpiov2_pad_wrapped NAME_INST ( \
            .PAD(PAD_SIG), .OUT(CORE_SIG), .OE_N(1'b0), .IN(), .IN_H(), \
            .TIE_HI_ESD(), .TIE_LO_ESD(), \
            .VCCD(vccd1), .VSSD(vssd1), .VDDIO(vccd1), .VSSIO(vssd1), \
            .SLOW(1'b0), .VTRIP_SEL(1'b0), .HLD_H_N(1'b1), .HLD_OVR(1'b0), \
            .INP_DIS(1'b1), .IB_MODE_SEL(1'b0), \
            .ANALOG_EN(1'b0), .ANALOG_SEL(1'b0), .ANALOG_POL(1'b0), \
            .DM(3'b110), .AMUXBUS_A(), .AMUXBUS_B(), \
            .PAD_A_NOESD_H(), .PAD_A_ESD_0_H(), .PAD_A_ESD_1_H());

    // ── EAST edge pads ──────────────────────────────────────────
    `IN_PAD (u_pad_clk,      pad_clk,      clk_c)
    `IN_PAD (u_pad_rst,      pad_rst_n,    rst_n_c)
    `OUT_PAD(u_pad_uart_tx,  pad_uart_tx,  uart_tx_c)
    `IN_PAD (u_pad_uart_rx,  pad_uart_rx,  uart_rx_c)
    `IN_PAD (u_pad_jtag_tck, pad_jtag_tck, jtag_tck_c)
    `IN_PAD (u_pad_jtag_tms, pad_jtag_tms, jtag_tms_c)
    `IN_PAD (u_pad_jtag_tdi, pad_jtag_tdi, jtag_tdi_c)
    `OUT_PAD(u_pad_jtag_tdo, pad_jtag_tdo, jtag_tdo_c)
    `OUT_PAD(u_pad_spi_sclk, pad_spi_sclk, spi_sclk_c)
    `OUT_PAD(u_pad_spi_mosi, pad_spi_mosi, spi_mosi_c)
    `IN_PAD (u_pad_spi_miso, pad_spi_miso, spi_miso_c)

    genvar gi;
    generate
        for (gi = 0; gi < 4; gi++) begin : gen_spi_cs
            `OUT_PAD(u_pad_spi_cs, pad_spi_cs_n[gi], spi_cs_n_c[gi])
        end
        for (gi = 0; gi < 32; gi++) begin : gen_gpio_pad
            sky130_ef_io__gpiov2_pad_wrapped u_pad_gpio (
                .PAD(pad_gpio[gi]), .OUT(gpio_out_c[gi]),
                .OE_N(~gpio_oe_c[gi]), .IN(gpio_in_c[gi]), .IN_H(),
                .TIE_HI_ESD(), .TIE_LO_ESD(),
                .VCCD(vccd1), .VSSD(vssd1), .VDDIO(vccd1), .VSSIO(vssd1),
                .SLOW(1'b0), .VTRIP_SEL(1'b0), .HLD_H_N(1'b1), .HLD_OVR(1'b0),
                .INP_DIS(1'b0), .IB_MODE_SEL(1'b0),
                .ANALOG_EN(1'b0), .ANALOG_SEL(1'b0), .ANALOG_POL(1'b0),
                .DM(3'b110), .AMUXBUS_A(), .AMUXBUS_B(),
                .PAD_A_NOESD_H(), .PAD_A_ESD_0_H(), .PAD_A_ESD_1_H());
        end
    endgenerate

    // ── SOUTH edge pads ─────────────────────────────────────────
    `OUT_PAD(u_pad_trap, pad_trap, trap_c)

    // ── WEST edge pads ──────────────────────────────────────────
    `OUT_PAD(u_pad_flash_sclk,  pad_flash_sclk,  flash_sclk_c)
    `OUT_PAD(u_pad_flash_cs_n,  pad_flash_cs_n,  flash_cs_n_c)
    `OUT_PAD(u_pad_flash_mosi,  pad_flash_mosi,  flash_mosi_c)
    `IN_PAD (u_pad_flash_miso,  pad_flash_miso,  flash_miso_c)

    // ── soc_core ────────────────────────────────────────────────
    soc_core u_soc_core (
        .clk_i(clk_c), .rst_ni(rst_n_c),
        .uart_tx_o(uart_tx_c), .uart_rx_i(uart_rx_c),
        .gpio_in_i(gpio_in_c), .gpio_out_o(gpio_out_c), .gpio_oe_o(gpio_oe_c),
        .spi_sclk_o(spi_sclk_c), .spi_mosi_o(spi_mosi_c),
        .spi_miso_i(spi_miso_c), .spi_cs_n_o(spi_cs_n_c),
        .flash_sclk_o(flash_sclk_c), .flash_cs_n_o(flash_cs_n_c),
        .flash_mosi_o(flash_mosi_c), .flash_miso_i(flash_miso_c),
        .jtag_tck_i(jtag_tck_c), .jtag_tms_i(jtag_tms_c),
        .jtag_tdi_i(jtag_tdi_c), .jtag_tdo_o(jtag_tdo_c),
        .trap_o(trap_c)
    );

    // ── Power and Corner Pads ───────────────────────────────────
    (* keep *) sky130_ef_io__corner_pad u_corner_sw ();
    (* keep *) sky130_ef_io__corner_pad u_corner_se ();
    (* keep *) sky130_ef_io__corner_pad u_corner_nw ();
    (* keep *) sky130_ef_io__corner_pad u_corner_ne ();

    (* keep *) sky130_ef_io__vccd_lvc_pad u_vccd1_n0 (.VCCD(vccd1), .VSSD(vssd1), .VDDIO(vccd1), .VSSIO(vssd1));
    (* keep *) sky130_ef_io__vccd_lvc_pad u_vccd1_n1 (.VCCD(vccd1), .VSSD(vssd1), .VDDIO(vccd1), .VSSIO(vssd1));
    (* keep *) sky130_ef_io__vssd_lvc_pad u_vssd1_n0 (.VCCD(vccd1), .VSSD(vssd1), .VDDIO(vccd1), .VSSIO(vssd1));
    (* keep *) sky130_ef_io__vssd_lvc_pad u_vssd1_n1 (.VCCD(vccd1), .VSSD(vssd1), .VDDIO(vccd1), .VSSIO(vssd1));

    (* keep *) sky130_ef_io__vddio_hvc_pad u_vddio_s0 (.VCCD(vccd1), .VSSD(vssd1), .VDDIO(vccd1), .VSSIO(vssd1));
    (* keep *) sky130_ef_io__vddio_hvc_pad u_vddio_s1 (.VCCD(vccd1), .VSSD(vssd1), .VDDIO(vccd1), .VSSIO(vssd1));
    (* keep *) sky130_ef_io__vssio_hvc_pad u_vssio_s0 (.VCCD(vccd1), .VSSD(vssd1), .VDDIO(vccd1), .VSSIO(vssd1));
    (* keep *) sky130_ef_io__vssio_hvc_pad u_vssio_s1 (.VCCD(vccd1), .VSSD(vssd1), .VDDIO(vccd1), .VSSIO(vssd1));

endmodule
