/*
 * GPIO Controller with APB4 Slave Interface
 *
 * A professional GPIO controller inspired by the ARM PrimeCell PL061 and SiFive
 * FE310-G002 GPIO. Provides per-pin direction control, 4-type interrupt support,
 * output XOR inversion, and I/O function mux for hardware peripheral override.
 *
 * Reference designs:
 *   - ARM PrimeCell PL061 (DDI 0190B)
 *   - SiFive FE310-G002 Manual, Chapter 17
 *
 * Register Map (active bits [GPIO_WIDTH-1:0]):
 *   Offset  Name       R/W    Description
 *   0x00    INPUT_VAL  [R]    Sampled pin values (synchronized)
 *   0x04    INPUT_EN   [R/W]  Per-pin input enable
 *   0x08    OUTPUT_EN  [R/W]  Per-pin output enable
 *   0x0C    OUTPUT_VAL [R/W]  Output data register
 *   0x10    PUE        [R/W]  Pull-up enable
 *   0x14    DS         [R/W]  Drive strength (1=high)
 *   0x18    RISE_IE    [R/W]  Rising-edge interrupt enable
 *   0x1C    RISE_IP    [R/W1C] Rising-edge interrupt pending
 *   0x20    FALL_IE    [R/W]  Falling-edge interrupt enable
 *   0x24    FALL_IP    [R/W1C] Falling-edge interrupt pending
 *   0x28    HIGH_IE    [R/W]  High-level interrupt enable
 *   0x2C    HIGH_IP    [R/W1C] High-level interrupt pending
 *   0x30    LOW_IE     [R/W]  Low-level interrupt enable
 *   0x34    LOW_IP     [R/W1C] Low-level interrupt pending
 *   0x38    OUT_XOR    [R/W]  Output XOR (invert output)
 *   0x3C    IOF_EN     [R/W]  I/O function enable (HW override)
 *   0x40    IOF_SEL    [R/W]  I/O function select (0/1)
 */

module gpio_apb #(
    parameter GPIO_WIDTH = 32
) (
    input  logic                    clk,
    input  logic                    resetn,

    // APB4 Slave Interface
    input  logic                    psel,
    input  logic                    penable,
    input  logic                    pwrite,
    input  logic [31:0]             paddr,
    input  logic [31:0]             pwdata,
    input  logic [3:0]              pstrb,
    input  logic [2:0]              pprot,     // APB4: Protection type (unused)
    output logic [31:0]             prdata,
    output logic                    pready,
    output logic                    pslverr,

    // GPIO I/O
    input  logic [GPIO_WIDTH-1:0]   gpio_in,   // External pin inputs
    output logic [GPIO_WIDTH-1:0]   gpio_out,  // Pin output values
    output logic [GPIO_WIDTH-1:0]   gpio_oe,   // Output enable (active high)

    // Auxiliary outputs (directly drive pad attributes)
    output logic [GPIO_WIDTH-1:0]   gpio_pue,  // Pull-up enable
    output logic [GPIO_WIDTH-1:0]   gpio_ds,   // Drive strength

    // I/O Function mux (for alternate HW peripherals like UART/SPI)
    output logic [GPIO_WIDTH-1:0]   iof_en,    // I/O function enable
    output logic [GPIO_WIDTH-1:0]   iof_sel,   // I/O function select

    // Interrupt output (active high, active when any enabled IRQ is pending)
    output logic                    gpio_irq
);

    //==========================================================================
    //? Register address offsets — use bits [6:0] of address
    //==========================================================================
    localparam [6:0] ADDR_INPUT_VAL  = 7'h00;
    localparam [6:0] ADDR_INPUT_EN   = 7'h04;
    localparam [6:0] ADDR_OUTPUT_EN  = 7'h08;
    localparam [6:0] ADDR_OUTPUT_VAL = 7'h0C;
    localparam [6:0] ADDR_PUE        = 7'h10;
    localparam [6:0] ADDR_DS         = 7'h14;
    localparam [6:0] ADDR_RISE_IE    = 7'h18;
    localparam [6:0] ADDR_RISE_IP    = 7'h1C;
    localparam [6:0] ADDR_FALL_IE    = 7'h20;
    localparam [6:0] ADDR_FALL_IP    = 7'h24;
    localparam [6:0] ADDR_HIGH_IE    = 7'h28;
    localparam [6:0] ADDR_HIGH_IP    = 7'h2C;
    localparam [6:0] ADDR_LOW_IE     = 7'h30;
    localparam [6:0] ADDR_LOW_IP     = 7'h34;
    localparam [6:0] ADDR_OUT_XOR    = 7'h38;
    localparam [6:0] ADDR_IOF_EN     = 7'h3C;
    localparam [6:0] ADDR_IOF_SEL    = 7'h40;

    //==========================================================================
    //? Internal registers
    //==========================================================================
    logic [GPIO_WIDTH-1:0] reg_input_en;
    logic [GPIO_WIDTH-1:0] reg_output_en;
    logic [GPIO_WIDTH-1:0] reg_output_val;
    logic [GPIO_WIDTH-1:0] reg_pue;
    logic [GPIO_WIDTH-1:0] reg_ds;
    logic [GPIO_WIDTH-1:0] reg_rise_ie;
    logic [GPIO_WIDTH-1:0] reg_rise_ip;
    logic [GPIO_WIDTH-1:0] reg_fall_ie;
    logic [GPIO_WIDTH-1:0] reg_fall_ip;
    logic [GPIO_WIDTH-1:0] reg_high_ie;
    logic [GPIO_WIDTH-1:0] reg_high_ip;
    logic [GPIO_WIDTH-1:0] reg_low_ie;
    logic [GPIO_WIDTH-1:0] reg_low_ip;
    logic [GPIO_WIDTH-1:0] reg_out_xor;
    logic [GPIO_WIDTH-1:0] reg_iof_en;
    logic [GPIO_WIDTH-1:0] reg_iof_sel;

    //==========================================================================
    // TODO :  2-stage synchronizer for gpio_in (metastability protection)
    //==========================================================================
    logic [GPIO_WIDTH-1:0] sync_stage1;
    logic [GPIO_WIDTH-1:0] sync_stage2;       // Synchronized value
    logic [GPIO_WIDTH-1:0] sync_prev;         // Previous cycle value for edge detection

    always_ff @(posedge clk or negedge resetn) begin
        if (!resetn) begin
            sync_stage1 <= '0;
            sync_stage2 <= '0;
            sync_prev   <= '0;
        end else begin
            sync_stage1 <= gpio_in;
            sync_stage2 <= sync_stage1;
            sync_prev   <= sync_stage2;
        end
    end

    //==========================================================================
    //? Edge & level detection
    //==========================================================================
    logic [GPIO_WIDTH-1:0] rise_detect;   // Rising edge: was 0, now 1
    logic [GPIO_WIDTH-1:0] fall_detect;   // Falling edge: was 1, now 0
    logic [GPIO_WIDTH-1:0] high_detect;   // Currently high
    logic [GPIO_WIDTH-1:0] low_detect;    // Currently low

    assign rise_detect = sync_stage2 & ~sync_prev;
    assign fall_detect = ~sync_stage2 & sync_prev;
    assign high_detect = sync_stage2;
    assign low_detect  = ~sync_stage2;

    //==========================================================================
    //? INPUT_VAL — synchronized pin values gated by input enable
    //==========================================================================
    logic [GPIO_WIDTH-1:0] input_val;
    assign input_val = sync_stage2 & reg_input_en;

    //==========================================================================
    //  TODO : Output logic
    //==========================================================================
    // Output value with optional XOR inversion
    assign gpio_out = reg_output_val ^ reg_out_xor;
    assign gpio_oe  = reg_output_en;

    // Pad attribute outputs
    assign gpio_pue = reg_pue;
    assign gpio_ds  = reg_ds;

    // I/O function mux outputs
    assign iof_en   = reg_iof_en;
    assign iof_sel  = reg_iof_sel;

    //==========================================================================
    // TODO : APB write decode
    //==========================================================================
    logic apb_write;
    assign apb_write = psel && penable && pwrite;

    // Byte-lane mask from PSTRB (each bit enables one byte of the 32-bit word)
    logic [31:0] strb_mask;
    assign strb_mask = {{8{pstrb[3]}}, {8{pstrb[2]}}, {8{pstrb[1]}}, {8{pstrb[0]}}};

    //==========================================================================
    // TODO : Register write logic
    //==========================================================================
    always_ff @(posedge clk or negedge resetn) begin
        if (!resetn) begin
            reg_input_en   <= '0;
            reg_output_en  <= '0;
            reg_output_val <= '0;
            reg_pue        <= '0;
            reg_ds         <= '0;
            reg_rise_ie    <= '0;
            reg_rise_ip    <= '0;
            reg_fall_ie    <= '0;
            reg_fall_ip    <= '0;
            reg_high_ie    <= '0;
            reg_high_ip    <= '0;
            reg_low_ie     <= '0;
            reg_low_ip     <= '0;
            reg_out_xor    <= '0;
            reg_iof_en     <= '0;
            reg_iof_sel    <= '0;
        end else begin
            // ---- Interrupt pending: hardware sets, software clears (W1C) ----
            // Rising edge
            reg_rise_ip <= (reg_rise_ip | rise_detect) &
                           ~(apb_write && (paddr[6:0] == ADDR_RISE_IP) ? (pwdata[GPIO_WIDTH-1:0] & strb_mask[GPIO_WIDTH-1:0]) : '0);
            // Falling edge
            reg_fall_ip <= (reg_fall_ip | fall_detect) &
                           ~(apb_write && (paddr[6:0] == ADDR_FALL_IP) ? (pwdata[GPIO_WIDTH-1:0] & strb_mask[GPIO_WIDTH-1:0]) : '0);
            // High level
            reg_high_ip <= (reg_high_ip | high_detect) &
                           ~(apb_write && (paddr[6:0] == ADDR_HIGH_IP) ? (pwdata[GPIO_WIDTH-1:0] & strb_mask[GPIO_WIDTH-1:0]) : '0);
            // Low level
            reg_low_ip  <= (reg_low_ip | low_detect) &
                           ~(apb_write && (paddr[6:0] == ADDR_LOW_IP)  ? (pwdata[GPIO_WIDTH-1:0] & strb_mask[GPIO_WIDTH-1:0]) : '0);

            // ---- Normal R/W registers ----
            if (apb_write) begin
                case (paddr[6:0])
                    ADDR_INPUT_EN:   reg_input_en   <= (reg_input_en   & ~strb_mask[GPIO_WIDTH-1:0]) | (pwdata[GPIO_WIDTH-1:0] & strb_mask[GPIO_WIDTH-1:0]);
                    ADDR_OUTPUT_EN:  reg_output_en  <= (reg_output_en  & ~strb_mask[GPIO_WIDTH-1:0]) | (pwdata[GPIO_WIDTH-1:0] & strb_mask[GPIO_WIDTH-1:0]);
                    ADDR_OUTPUT_VAL: reg_output_val <= (reg_output_val & ~strb_mask[GPIO_WIDTH-1:0]) | (pwdata[GPIO_WIDTH-1:0] & strb_mask[GPIO_WIDTH-1:0]);
                    ADDR_PUE:        reg_pue        <= (reg_pue        & ~strb_mask[GPIO_WIDTH-1:0]) | (pwdata[GPIO_WIDTH-1:0] & strb_mask[GPIO_WIDTH-1:0]);
                    ADDR_DS:         reg_ds         <= (reg_ds         & ~strb_mask[GPIO_WIDTH-1:0]) | (pwdata[GPIO_WIDTH-1:0] & strb_mask[GPIO_WIDTH-1:0]);
                    ADDR_RISE_IE:    reg_rise_ie    <= (reg_rise_ie    & ~strb_mask[GPIO_WIDTH-1:0]) | (pwdata[GPIO_WIDTH-1:0] & strb_mask[GPIO_WIDTH-1:0]);
                    ADDR_FALL_IE:    reg_fall_ie    <= (reg_fall_ie    & ~strb_mask[GPIO_WIDTH-1:0]) | (pwdata[GPIO_WIDTH-1:0] & strb_mask[GPIO_WIDTH-1:0]);
                    ADDR_HIGH_IE:    reg_high_ie    <= (reg_high_ie    & ~strb_mask[GPIO_WIDTH-1:0]) | (pwdata[GPIO_WIDTH-1:0] & strb_mask[GPIO_WIDTH-1:0]);
                    ADDR_LOW_IE:     reg_low_ie     <= (reg_low_ie     & ~strb_mask[GPIO_WIDTH-1:0]) | (pwdata[GPIO_WIDTH-1:0] & strb_mask[GPIO_WIDTH-1:0]);
                    ADDR_OUT_XOR:    reg_out_xor    <= (reg_out_xor    & ~strb_mask[GPIO_WIDTH-1:0]) | (pwdata[GPIO_WIDTH-1:0] & strb_mask[GPIO_WIDTH-1:0]);
                    ADDR_IOF_EN:     reg_iof_en     <= (reg_iof_en     & ~strb_mask[GPIO_WIDTH-1:0]) | (pwdata[GPIO_WIDTH-1:0] & strb_mask[GPIO_WIDTH-1:0]);
                    ADDR_IOF_SEL:    reg_iof_sel    <= (reg_iof_sel    & ~strb_mask[GPIO_WIDTH-1:0]) | (pwdata[GPIO_WIDTH-1:0] & strb_mask[GPIO_WIDTH-1:0]);
                    default: ; // W1C registers handled above; INPUT_VAL is read-only
                endcase
            end
        end
    end

    //==========================================================================
    // TODO : Interrupt output — OR of all (enabled & pending)
    //==========================================================================
    assign gpio_irq = |((reg_rise_ip & reg_rise_ie) |
                        (reg_fall_ip & reg_fall_ie) |
                        (reg_high_ip & reg_high_ie) |
                        (reg_low_ip  & reg_low_ie));

    //==========================================================================
    // TODO : APB read logic
    //==========================================================================
    logic addr_valid;

    always_comb begin
        prdata     = 32'h0;
        addr_valid = 1'b1;

        case (paddr[6:0])
            ADDR_INPUT_VAL:  prdata[GPIO_WIDTH-1:0] = input_val;
            ADDR_INPUT_EN:   prdata[GPIO_WIDTH-1:0] = reg_input_en;
            ADDR_OUTPUT_EN:  prdata[GPIO_WIDTH-1:0] = reg_output_en;
            ADDR_OUTPUT_VAL: prdata[GPIO_WIDTH-1:0] = reg_output_val;
            ADDR_PUE:        prdata[GPIO_WIDTH-1:0] = reg_pue;
            ADDR_DS:         prdata[GPIO_WIDTH-1:0] = reg_ds;
            ADDR_RISE_IE:    prdata[GPIO_WIDTH-1:0] = reg_rise_ie;
            ADDR_RISE_IP:    prdata[GPIO_WIDTH-1:0] = reg_rise_ip;
            ADDR_FALL_IE:    prdata[GPIO_WIDTH-1:0] = reg_fall_ie;
            ADDR_FALL_IP:    prdata[GPIO_WIDTH-1:0] = reg_fall_ip;
            ADDR_HIGH_IE:    prdata[GPIO_WIDTH-1:0] = reg_high_ie;
            ADDR_HIGH_IP:    prdata[GPIO_WIDTH-1:0] = reg_high_ip;
            ADDR_LOW_IE:     prdata[GPIO_WIDTH-1:0] = reg_low_ie;
            ADDR_LOW_IP:     prdata[GPIO_WIDTH-1:0] = reg_low_ip;
            ADDR_OUT_XOR:    prdata[GPIO_WIDTH-1:0] = reg_out_xor;
            ADDR_IOF_EN:     prdata[GPIO_WIDTH-1:0] = reg_iof_en;
            ADDR_IOF_SEL:    prdata[GPIO_WIDTH-1:0] = reg_iof_sel;
            default: begin
                prdata     = 32'h0;
                addr_valid = 1'b0;
            end
        endcase
    end

    //==========================================================================
    //? APB response
    //==========================================================================
    // Always ready (no wait states), error on invalid address access
    assign pready  = 1'b1;
    assign pslverr = psel && penable && !addr_valid;

endmodule
