/*
 * AXI4-Lite to APB Bridge
 *
 * Converts AXI4-Lite transactions from the AXI interconnect into APB
 * transactions for the peripheral subsystem. This bridge sits as an
 * AXI slave (from the interconnect's perspective) and drives an APB
 * master interface towards the APB peripherals.
 *
 * AXI4-Lite has 5 independent channels (AW, W, B, AR, R).
 * APB has a simple 3-phase protocol: IDLE → SETUP → ACCESS.
 *
 * The bridge:
 *   1. Accepts AXI write (AW+W) or read (AR) requests
 *   2. Translates them into APB SETUP→ACCESS cycles
 *   3. Returns the APB response on the AXI B or R channel
 *
 * Priorities: Writes take priority over reads if both arrive simultaneously.
 */

module axi2apb_bridge (
    input  logic        clk,
    input  logic        resetn,

    // ============================================================
    //? AXI4-Lite Slave Interface (from AXI Interconnect)
    // ============================================================

    // Write Address Channel
    input  logic        axi_awvalid,
    output logic        axi_awready,
    input  logic [31:0] axi_awaddr,
    input  logic [2:0]  axi_awprot,

    // Write Data Channel
    input  logic        axi_wvalid,
    output logic        axi_wready,
    input  logic [31:0] axi_wdata,
    input  logic [3:0]  axi_wstrb,

    // Write Response Channel
    output logic        axi_bvalid,
    input  logic        axi_bready,
    output logic [1:0]  axi_bresp,

    // Read Address Channel
    input  logic        axi_arvalid,
    output logic        axi_arready,
    input  logic [31:0] axi_araddr,
    input  logic [2:0]  axi_arprot,

    // Read Data Channel
    output logic        axi_rvalid,
    input  logic        axi_rready,
    output logic [31:0] axi_rdata,
    output logic [1:0]  axi_rresp,

    // ============================================================
    //? APB Master Interface (to APB Interconnect)
    // ============================================================
    output logic        apb_psel,      // APB4: Slave select
    output logic        apb_penable,   // APB4: Enable
    output logic        apb_pwrite,    // APB4: Write
    output logic [31:0] apb_paddr,     // APB4: Address
    output logic [31:0] apb_pwdata,    // APB4: Write data
    output logic [3:0]  apb_pstrb,     // APB4: Byte strobes
    output logic [2:0]  apb_pprot,     // APB4: Protection type
    input  logic [31:0] apb_prdata,    // APB4: Read data
    input  logic        apb_pready,    // APB4: Ready
    input  logic        apb_pslverr
);

    // ============================================================
    //? Bridge FSM States
    // ============================================================

    typedef enum logic [2:0] {
        ST_IDLE,        // Waiting for AXI request
        ST_APB_SETUP,   // APB SETUP phase (PSEL=1, PENABLE=0)
        ST_APB_ACCESS,  // APB ACCESS phase (PSEL=1, PENABLE=1)
        ST_WR_RESP,     // Waiting to deliver AXI write response (B channel)
        ST_RD_RESP      // Waiting to deliver AXI read response (R channel)
    } bridge_state_t;
    bridge_state_t state;

    // ============================================================
    //? AXI Write Phase Tracking (AW and W can arrive independently)
    // ============================================================
    logic        aw_captured;       // AW address has been captured
    logic        w_captured;        // W data has been captured
    logic [31:0] aw_addr_reg;       // Captured write address
    logic [2:0]  aw_prot_reg;       // Captured write protection
    logic [31:0] w_data_reg;        // Captured write data
    logic [3:0]  w_strb_reg;        // Captured write strobe

    // ============================================================
    //? APB Response Capture
    // ============================================================
    logic [31:0] apb_rdata_reg;     // Captured read data from APB
    logic        apb_slverr_reg;    // Captured slave error from APB
    logic        is_write_txn;      // Current transaction is write (vs read)

    // ============================================================
    //? AXI Ready/Valid Outputs
    // ============================================================

    // AW/W ready: only accept when idle and not already captured
    assign axi_awready = (state == ST_IDLE) && !aw_captured;
    assign axi_wready  = (state == ST_IDLE) && !w_captured;

    // AR/R ready: only accept when idle and no write pending
    assign axi_arready = (state == ST_IDLE) && !aw_captured && !w_captured && !axi_awvalid;

    //=============================================================
                    // TODO : FSM
    //=============================================================

    always_ff @(posedge clk) 
    begin
        if ( !resetn )
        begin
            state         <= ST_IDLE;
            aw_captured   <= 1'b0;
            w_captured    <= 1'b0;
            aw_addr_reg   <= 32'h0;
            aw_prot_reg   <= 3'b0;
            w_data_reg    <= 32'h0;
            w_strb_reg    <= 4'h0;
            apb_rdata_reg <= 32'h0;
            apb_slverr_reg<= 1'b0;
            is_write_txn  <= 1'b0;
            // APB outputs (active only during SETUP/ACCESS)
            apb_psel      <= 1'b0;
            apb_penable   <= 1'b0;
            apb_pwrite    <= 1'b0;
            apb_paddr     <= 32'h0;
            apb_pwdata    <= 32'h0;
            apb_pstrb     <= 4'h0;
            apb_pprot     <= 3'b0;
            // AXI response outputs
            axi_bvalid    <= 1'b0;
            axi_bresp     <= 2'b00;
            axi_rvalid    <= 1'b0;
            axi_rdata     <= 32'h0;
            axi_rresp     <= 2'b00;              
        end

        else
        begin
            case (state)

                //-----------------------------------------------------
                //? IDLE : Capture AXI request and prepare APB signals
                //-----------------------------------------------------
                ST_IDLE: begin
                    // Capture AW if available
                    if(axi_awvalid && axi_awready)
                    begin
                        aw_captured <= 1'b1;
                        aw_addr_reg <= axi_awaddr;
                        aw_prot_reg <= axi_awprot;
                    end

                    // Capture W if available
                    if(axi_wvalid && axi_wready)
                    begin
                        w_captured <= 1'b1;
                        w_data_reg <= axi_wdata;
                        w_strb_reg <= axi_wstrb;
                    end

                    // Check if we can start APB transaction (write takes priority)
                    // Write : both AW and W must be captured
                    if ((aw_captured || (axi_awvalid && axi_awready)) &&  // Allow starting write if AW just captured
                        (w_captured || (axi_wvalid && axi_wready)))       // Allow starting write if W just captured
                    begin
                        state <= ST_APB_SETUP;
                        is_write_txn <= 1'b1;  // This is a write transaction
                        apb_psel    <= 1'b1;  // Start APB transaction
                        apb_penable <= 1'b0;  // SETUP phase
                        apb_pwrite  <= 1'b1;  // Write transaction
                        // use newly captured values if they arrived this cycle, otherwise stored reg
                        apb_paddr   <= (axi_awvalid && axi_awready) ? axi_awaddr : aw_addr_reg;
                        apb_pwdata  <= (axi_wvalid  && axi_wready)  ? axi_wdata  : w_data_reg;
                        apb_pstrb   <= (axi_wvalid  && axi_wready)  ? axi_wstrb  : w_strb_reg;
                        apb_pprot   <= (axi_awvalid && axi_awready)  ? axi_awprot : aw_prot_reg;
                    end

                    // Read: AR accepted when no write pending
                    else if (axi_arvalid && axi_arready)
                    begin
                        state <= ST_APB_SETUP;
                        is_write_txn <= 1'b0;  // This is a read transaction
                        apb_psel    <= 1'b1;
                        apb_penable <= 1'b0;
                        apb_pwrite  <= 1'b0;
                        apb_paddr   <= axi_araddr;
                        apb_pwdata  <= 32'h0;
                        apb_pstrb   <= 4'h0;
                        apb_pprot   <= axi_arprot;
                    end
                end

                //-----------------------------------------------------
                //? APB_SETUP : Assert PSEL, wait 1 cycle, then go to
                //-----------------------------------------------------
                ST_APB_SETUP: begin
                    // After one cycle in SETUP, move to ACCESS
                    state <= ST_APB_ACCESS;
                    apb_penable <= 1'b1;  // Move to ACCESS phase
                end

                //-----------------------------------------------------
                //? APB_ACCESS : Wait for APB ready, capture response
                //-----------------------------------------------------
                ST_APB_ACCESS: begin
                    if (apb_pready) 
                    begin
                        // capture APB response
                        apb_rdata_reg  <= apb_prdata;
                        apb_slverr_reg <= apb_pslverr;

                        // Deassert APB signals
                        apb_psel    <= 1'b0;
                        apb_penable <= 1'b0;

                        if (is_write_txn)
                        // Generate AXI write response (B channel)
                        begin
                            axi_bvalid <= 1'b1;
                            axi_bresp  <= apb_pslverr ? 2'b10 : 2'b00;  // SLVERR or OKAY response
                            state      <= ST_WR_RESP;

                            // clear captured flags to allow new transactions while waiting for AXI master to accept response
                            aw_captured <= 1'b0;
                            w_captured  <= 1'b0;
                        end
                        else
                        begin
                            // Generate AXI read response (R channel)
                            axi_rvalid <= 1'b1;
                            axi_rdata  <= apb_prdata;
                            axi_rresp  <= apb_pslverr ? 2'b10 : 2'b00;  // SLVERR or OKAY response
                            state     <= ST_RD_RESP;
                        end
                    end
                       // If PREADY is not asserted, we stay in ACCESS state and keep APB signals asserted until it is ready
                end

                // ---------------------------------------------------------
                //? Write Response: Wait for AXI master to accept B response
                // ---------------------------------------------------------
                ST_WR_RESP: begin
                    if (axi_bready && axi_bvalid)
                    begin
                        axi_bvalid <= 1'b0;  // Clear BVALID after response is accepted
                        state      <= ST_IDLE; // Go back to IDLE to accept next transaction
                    end
                end

                // ---------------------------------------------------------
                //? Read Response: Wait for AXI master to accept R response
                // ---------------------------------------------------------
                ST_RD_RESP: begin
                    if (axi_rready && axi_rvalid)
                    begin
                        axi_rvalid <= 1'b0;  // Clear RVALID after response is accepted
                        state      <= ST_IDLE; // Go back to IDLE to accept next transaction
                    end
                end

                default : state <= ST_IDLE;            
            endcase
        end
        
    end








endmodule
