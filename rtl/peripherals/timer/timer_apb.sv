/*
 * Timer Controller with APB4 Slave Interface
 *
 * A professional, single-channel 32-bit down-counter timer inspired by the
 * ARM SP804 Dual-Timer. Features include selectable 16/32-bit width,
 * prescaler (÷1, ÷16, ÷256), and three operating modes: free-running,
 * periodic, and one-shot.
 *
 * Reference: ARM DDI 0271 (SP804 Technical Reference Manual)
 *
 * Register Map (offset from base address 0x2000_1000):
 *   0x00 LOAD       [R/W]   Reload value
 *   0x04 VALUE      [R]     Current counter value
 *   0x08 CTRL       [R/W]   Control register
 *                           [0]    one_shot   - 0: wrapping, 1: one-shot
 *                           [1]    timer_size - 0: 16-bit, 1: 32-bit
 *                           [3:2]  prescale   - 00: ÷1, 01: ÷16, 10: ÷256
 *                           [5]    int_en     - Interrupt enable
 *                           [6]    mode       - 0: free-running, 1: periodic
 *                           [7]    enable     - Timer enable
 *   0x0C INTCLR     [W]     Write any value to clear interrupt
 *   0x10 RIS        [R]     Raw interrupt status
 *   0x14 MIS        [R]     Masked interrupt status
 *   0x18 BGLOAD     [R/W]   Background load (update reload w/o reset)
 *   0x1C PRESCALE_CNT [R]   Current prescaler counter (debug)
 */

module timer_apb (
    input  logic        clk,
    input  logic        resetn,

    // APB4 Slave Interface
    input  logic        psel,
    input  logic        penable,
    input  logic        pwrite,
    input  logic [31:0] paddr,
    input  logic [31:0] pwdata,
    input  logic [3:0]  pstrb,
    input  logic [2:0]  pprot,     // APB4: Protection type (unused)
    output logic [31:0] prdata,
    output logic        pready,
    output logic        pslverr,

    // Interrupt output
    output logic        timer_irq
);

    //==========================================================================
    //* Register address offsets — use bits [4:0] of address
    //==========================================================================
    localparam ADDR_LOAD         = 5'h00;
    localparam ADDR_VALUE        = 5'h04;
    localparam ADDR_CTRL         = 5'h08;
    localparam ADDR_INTCLR       = 5'h0C;
    localparam ADDR_RIS          = 5'h10;
    localparam ADDR_MIS          = 5'h14;
    localparam ADDR_BGLOAD       = 5'h18;
    localparam ADDR_PRESCALE_CNT = 5'h1C;

    //==========================================================================
    //* Control register fields
    //==========================================================================
    logic        ctrl_one_shot;    // [0]   One-shot mode
    logic        ctrl_timer_size;  // [1]   0=16-bit, 1=32-bit
    logic [1:0]  ctrl_prescale;    // [3:2] Prescale: 00=÷1, 01=÷16, 10=÷256
    logic        ctrl_int_en;      // [5]   Interrupt enable
    logic        ctrl_mode;        // [6]   0=free-running, 1=periodic
    logic        ctrl_enable;      // [7]   Timer enable

    //==========================================================================
    //* Internal registers
    //==========================================================================
    logic [31:0] load_reg;         // Reload value
    logic [31:0] bgload_reg;       // Background load value
    logic [31:0] counter;          // Main down-counter
    logic        raw_int;          // Raw interrupt status (sticky)
    logic        timer_stopped;    // One-shot: counter has reached zero


    //===============================================================================================================================
    // TODO :  Prescaler
    //? Purpose : Divide the input clock to achieve slower timer tick rates. This allows
    // the timer to count down at a slower rate than the system clock,
    // which is useful for longer timing intervals without needing a large counter width.
    //------------------------------------------------------------------------------------------------------------------------------
    //? Implementation: A simple binary counter that counts up on each clock cycle when the timer is enabled.
    // When the counter reaches the value specified by the prescale setting, it resets to zero and generates a "prescale tick". 
    // The main timer counter only decrements on these prescale ticks,effectively dividing the input clock by the prescale factor.
    //==============================================================================================================================

    logic [7:0]  prescale_counter;
    logic        prescale_tick;    // Tick at the divided rate

    // Determine prescale modulus - how many input clock cycles per timer tick based on ctrl_prescale
    logic [7:0]  prescale_mod;

    always_comb 
    begin
        case (ctrl_prescale)
            2'b00:   prescale_mod = 8'd0;    // ÷1  (tick every cycle)
            2'b01:   prescale_mod = 8'd15;   // ÷16
            2'b10:   prescale_mod = 8'd255;  // ÷256
            default: prescale_mod = 8'd0;    // Reserved → ÷1
        endcase
    end

    always_ff @(posedge clk) 
    begin
        if (!resetn) 
        begin
            prescale_counter <= 8'd0;
            prescale_tick    <= 1'b0;
        end 
        else 
        begin
            prescale_tick <= 1'b0;

            if (!ctrl_enable) 
            begin
                // Hold prescaler in reset while timer is disabled
                prescale_counter <= 8'd0;
            end 
            else 
            begin
                if (prescale_counter >= prescale_mod) 
                begin
                    prescale_counter <= 8'd0;
                    prescale_tick    <= 1'b1;
                end 
                else 
                begin
                    prescale_counter <= prescale_counter + 8'd1;
                end
            end
        end
    end

    //=========================================================================================
    //? Counter mask for 16/32-bit mode
    // this ensures that in 16-bit mode, the upper 16 bits of the counter are always zero 
    // and the counter wraps at 0x0000_0000 instead of 0xFFFF_FFFF.
    //=========================================================================================
    logic [31:0] counter_mask;
    assign counter_mask = ctrl_timer_size ? 32'hFFFF_FFFF : 32'h0000_FFFF;

    // Masked counter value for reads
    logic [31:0] counter_value;
    assign counter_value = counter & counter_mask;

    //==========================================================================
    // TODO : Main down-counter logic
    //==========================================================================
    logic        counter_zero;     // Counter has reached zero (for interrupt and reload logic)
    logic        load_write;       // LOAD register was written
    logic        bgload_write;     // BGLOAD register was written
    logic        intclr_write;     // INTCLR was written
    logic        ctrl_write;       // CTRL was written

    assign counter_zero = (counter_value == 32'd0);

    always_ff @(posedge clk) 
    begin
        if (!resetn) 
        begin
            counter       <= 32'hFFFF_FFFF;
            timer_stopped <= 1'b0;
        end 
        else 
        begin
            // Writing LOAD resets the counter immediately
            if (load_write) 
            begin
                counter       <= pwdata & counter_mask;
                timer_stopped <= 1'b0;
            end 

            // Enabling the timer with CTRL[7] = 1 also resets the counter to the LOAD value if it was previously stopped
            // (e.g. after reaching zero in one-shot mode).            
            else if (ctrl_write && pwdata[7] && !ctrl_enable) 
            begin
                counter       <= load_reg & counter_mask;
                timer_stopped <= 1'b0;

            // Normal counting
            end 
            else if (ctrl_enable && prescale_tick && !timer_stopped) 
            begin
                if (counter_zero) 
                begin
                    // Counter wrapped to zero
                    if (ctrl_one_shot) 
                    begin
                        // One-shot: stop
                        timer_stopped <= 1'b1;
                    end 
                    else if (ctrl_mode) 
                    begin
                        // Periodic: reload from LOAD register
                        counter <= load_reg & counter_mask;
                    end else begin
                        // Free-running: wrap to max
                        counter <= counter_mask;
                    end
                end 
                else 
                begin
                    counter <= (counter - 32'd1) & counter_mask;
                end
            end

            // Background load: update load_reg value, counter keeps running.
            // The new value takes effect on the NEXT reload (periodic wrap).
            // This is handled in the load_reg update below.
        end
    end

    //==========================================================================
    // TODO : Interrupt logic
    //==========================================================================
    always_ff @(posedge clk) 
    begin
        if (!resetn) 
        begin
            raw_int <= 1'b0;
        end 
        else 
        begin
            if (intclr_write) 
            begin
                raw_int <= 1'b0;
            end 
            else if (ctrl_enable && prescale_tick && counter_zero && !timer_stopped) 
            begin
                raw_int <= 1'b1;
            end
        end
    end

    // Masked interrupt = raw AND enabled
    logic masked_int;
    assign masked_int = raw_int & ctrl_int_en;
    assign timer_irq  = masked_int;

    //==========================================================================
    // TODO : APB4 Slave Interface
    //
    //  SETUP phase:  PSEL=1, PENABLE=0
    //  ACCESS phase: PSEL=1, PENABLE=1  → execute transaction
    //==========================================================================

    // No wait states for this peripheral
    assign pready  = 1'b1;
    assign pslverr = 1'b0;

    // Detect APB write on ACCESS phase
    logic apb_write;
    assign apb_write = psel && penable && pwrite;

    // Per-register write strobes
    assign load_write   = apb_write && (paddr[4:0] == ADDR_LOAD);
    assign bgload_write = apb_write && (paddr[4:0] == ADDR_BGLOAD);
    assign intclr_write = apb_write && (paddr[4:0] == ADDR_INTCLR);
    assign ctrl_write   = apb_write && (paddr[4:0] == ADDR_CTRL);

    //==========================================================================
    // TODO :Register writes
    //==========================================================================
    always_ff @(posedge clk) 
    begin
        if (!resetn) 
        begin
            load_reg       <= 32'h0000_0000;
            bgload_reg     <= 32'h0000_0000;
            ctrl_one_shot  <= 1'b0;
            ctrl_timer_size<= 1'b0;
            ctrl_prescale  <= 2'b00;
            ctrl_int_en    <= 1'b0;
            ctrl_mode      <= 1'b0;
            ctrl_enable    <= 1'b0;
        end 
        else 
        begin
            // LOAD register write
            if (load_write) 
            begin
                load_reg <= pwdata;
            end

            // BGLOAD register write — updates load_reg without resetting counter
            if (bgload_write) 
            begin
                load_reg   <= pwdata;
                bgload_reg <= pwdata;
            end

            // CTRL register write
            if (ctrl_write) 
            begin
                ctrl_one_shot   <= pwdata[0];
                ctrl_timer_size <= pwdata[1];
                ctrl_prescale   <= pwdata[3:2];
                ctrl_int_en     <= pwdata[5];
                ctrl_mode       <= pwdata[6];
                ctrl_enable     <= pwdata[7];
            end
        end
    end

    //==========================================================================
    // TODO : Register reads
    //==========================================================================
    always_comb 
    begin
        prdata = 32'h0000_0000;

        if (psel) 
        begin
            case (paddr[4:0])
                ADDR_LOAD:         prdata = load_reg;
                ADDR_VALUE:        prdata = counter_value;
                ADDR_CTRL:         prdata = {24'd0,
                                              ctrl_enable,
                                              ctrl_mode,
                                              ctrl_int_en,
                                              1'b0,           // bit[4] reserved
                                              ctrl_prescale,
                                              ctrl_timer_size,
                                              ctrl_one_shot};
                ADDR_INTCLR:       prdata = 32'h0000_0000;     // Write-only
                ADDR_RIS:          prdata = {31'd0, raw_int}; // Unmasked interrupt status
                ADDR_MIS:          prdata = {31'd0, masked_int}; // Masked interrupt status
                ADDR_BGLOAD:       prdata = bgload_reg;
                ADDR_PRESCALE_CNT: prdata = {24'd0, prescale_counter};
                default:           prdata = 32'h0000_0000;
            endcase
        end
    end

endmodule
