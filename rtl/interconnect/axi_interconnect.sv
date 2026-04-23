/*
 * AXI4-Lite Interconnect/Crossbar 
 * Routes single AXI master (CPU) to 4 slaves with address-based multiplexing
 *
 * Address Map:
 *   Slave 0 (Boot ROM): 0x00000000 - 0x0000FFFF
 *   Slave 1 (SRAM)    : 0x00010000 - 0x0002FFFF
 *   Slave 2 (Flash)   : 0x40000000 - 0x40FFFFFF
 *   Slave 3 (APB)     : 0x20000000 - 0x2000FFFF
 *
 */

module axi_interconnect (
    input logic clk,
    input logic resetn,

    //--------------------------------------------------------
    //? AXI Master Interface (from CPU)
    //--------------------------------------------------------

    // Write Address Channel
    input  logic        m_axi_awvalid,
    output logic        m_axi_awready,
    input  logic [31:0] m_axi_awaddr,
    input  logic [ 2:0] m_axi_awprot,

    // Write Data Channel
    input  logic        m_axi_wvalid,
    output logic        m_axi_wready,
    input  logic [31:0] m_axi_wdata,
    input  logic [ 3:0] m_axi_wstrb,

    // Write Response Channel
    output logic [1:0]  m_axi_bresp,
    output logic        m_axi_bvalid,
    input  logic        m_axi_bready,

    // Read Address Channel
    input  logic        m_axi_arvalid,
    output logic        m_axi_arready,
    input  logic [31:0] m_axi_araddr,
    input  logic [ 2:0] m_axi_arprot,

    // Read Data Channel
    output logic        m_axi_rvalid,
    input  logic        m_axi_rready,
    output logic [1:0]  m_axi_rresp,
    output logic [31:0] m_axi_rdata,

    //--------------------------------------------------------
    //? Slave 0 : Boot ROM ( 0x00000000 - 0x0000FFFF )
    //--------------------------------------------------------

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

    //--------------------------------------------------------
    //? Slave 1 : SRAM ( 0x00010000 - 0x0002FFFF )
    //--------------------------------------------------------

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

    //--------------------------------------------------------
    //? Slave 2 : Flash ( 0x40000000 - 0x40FFFFFF )
    //--------------------------------------------------------

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

    //--------------------------------------------------------
    //? Slave 3 : APB Subsystem ( 0x20000000 - 0x2000FFFF )
    //--------------------------------------------------------

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

    //--------------------------------------------------------
    //?  Slave Encoding
    //--------------------------------------------------------

    localparam logic [1:0] SEL_S0 = 2'b00; // 0x00000000 - 0x0000FFFF
    localparam logic [1:0] SEL_S1 = 2'b01; // 0x00010000 - 0x0002FFFF
    localparam logic [1:0] SEL_S2 = 2'b10; // 0x40000000 - 0x40FFFFFF
    localparam logic [1:0] SEL_S3 = 2'b11; // 0x20000000 - 0x2000FFFF


    //------------------------------------------------------------------------------
    // Address Decoding (combinational)
    //
    // ? Using plain assigns instead of function return for Yosys compatibility.
    // ? Yosys SV frontend does not support `return` inside `function automatic`.
    //------------------------------------------------------------------------------

    logic [1:0] aw_slave_sel, ar_slave_sel;
    logic       aw_decerr,    ar_decerr;

    // Write address decode
    assign aw_slave_sel = (m_axi_awaddr >= 32'h00000000 && m_axi_awaddr < 32'h00010000) ? SEL_S0 :
                          (m_axi_awaddr >= 32'h00010000 && m_axi_awaddr < 32'h00030000) ? SEL_S1 :
                          (m_axi_awaddr >= 32'h40000000 && m_axi_awaddr < 32'h41000000) ? SEL_S2 :
                          (m_axi_awaddr >= 32'h20000000 && m_axi_awaddr < 32'h20010000) ? SEL_S3 :
                                                                                           SEL_S0;

    assign aw_decerr    = !((m_axi_awaddr >= 32'h00000000 && m_axi_awaddr < 32'h00010000) ||
                            (m_axi_awaddr >= 32'h00010000 && m_axi_awaddr < 32'h00030000) ||
                            (m_axi_awaddr >= 32'h40000000 && m_axi_awaddr < 32'h41000000) ||
                            (m_axi_awaddr >= 32'h20000000 && m_axi_awaddr < 32'h20010000));

    // Read address decode
    assign ar_slave_sel = (m_axi_araddr >= 32'h00000000 && m_axi_araddr < 32'h00010000) ? SEL_S0 :
                          (m_axi_araddr >= 32'h00010000 && m_axi_araddr < 32'h00030000) ? SEL_S1 :
                          (m_axi_araddr >= 32'h40000000 && m_axi_araddr < 32'h41000000) ? SEL_S2 :
                          (m_axi_araddr >= 32'h20000000 && m_axi_araddr < 32'h20010000) ? SEL_S3 :
                                                                                           SEL_S0;

    assign ar_decerr    = !((m_axi_araddr >= 32'h00000000 && m_axi_araddr < 32'h00010000) ||
                            (m_axi_araddr >= 32'h00010000 && m_axi_araddr < 32'h00030000) ||
                            (m_axi_araddr >= 32'h40000000 && m_axi_araddr < 32'h41000000) ||
                            (m_axi_araddr >= 32'h20000000 && m_axi_araddr < 32'h20010000));

//-------------------------------------------------------------------------------------------------------

    //-----------------------------------------------------------------------------------
    //? Write Transaction FSM
    //------------------------------------------------------------------------------------

    typedef enum logic [1:0] {
        W_IDLE,     // waiting for new write transaction
        W_DATA,     // Address accepted, waiting for write data
        W_RESP,     // Write data accepted, waiting for slave response
        W_DECERR    // invalid address received, generate error response
    } write_state_t;

    write_state_t w_state;
    logic [1:0]  w_slave_reg; // which slave is this transaction for? (registered at address acceptance)
    logic [31:0] w_addr_reg;  // captured address for write transaction
    logic [2:0]  w_prot_reg;  // captured protection bits for write transaction

    //-------------------------------------------------------------------------------
    //? WRITE  FSM LOGIC
    //-------------------------------------------------------------------------------

    always_ff @(posedge clk)
    begin
        if(!resetn)
            begin
                w_state <= W_IDLE;
                w_slave_reg <= SEL_S0;
                w_addr_reg <= '0;
                w_prot_reg <= '0;
            end
        else
            begin
                case(w_state)

                W_IDLE : begin
                            if(m_axi_awready && m_axi_awvalid)
                            begin
                                w_slave_reg <= aw_slave_sel;
                                w_addr_reg  <= m_axi_awaddr;
                                w_prot_reg  <= m_axi_awprot;

                                if(aw_decerr)
                                    w_state <= W_DECERR;
                                else
                                    w_state <= W_DATA;
                            end
                         end

                W_DATA : begin
                            if(m_axi_wready && m_axi_wvalid)
                                w_state <= W_RESP;
                         end

                W_RESP : begin
                            // Wait for the selected slave to assert bvalid
                            if(m_axi_bvalid && m_axi_bready)
                                w_state <= W_IDLE;
                         end


                W_DECERR : begin
                            // Generate write response with decode error
                            if(m_axi_bready)
                                w_state <= W_IDLE; // DECERR response accepted, return to idle
                         end
                endcase
            end

    end
//-------------------------------------------------------------------------------------------------------

    //-----------------------------------------------------------------------------------
    //? Read Transaction FSM
    //------------------------------------------------------------------------------------

    typedef enum logic [1:0] {
        R_IDLE,     // waiting for new read transaction
        R_WAIT,     // Address accepted, waiting for data from slave
        R_DECERR    // invalid address received, generate error response
    } read_state_t;

    read_state_t r_state;
    logic [1:0]  r_slave_reg; // which slave is this transaction for? (registered at address acceptance)
    logic [31:0] r_addr_reg;  // captured address for read transaction
    logic [2:0]  r_prot_reg;  // captured protection bits for read transaction

    //-------------------------------------------------------------------------------
    //? READ FSM LOGIC
    //-------------------------------------------------------------------------------

    always_ff @(posedge clk)
    begin
        if(!resetn)
            begin
                r_state <= R_IDLE;
                r_slave_reg <= SEL_S0;
                r_addr_reg <= '0;
                r_prot_reg <= '0;
            end
        else
            begin
                case(r_state)

                R_IDLE : begin
                            if(m_axi_arready && m_axi_arvalid)
                            begin
                                r_slave_reg <= ar_slave_sel;
                                r_addr_reg  <= m_axi_araddr;
                                r_prot_reg  <= m_axi_arprot;

                                if(ar_decerr)
                                    r_state <= R_DECERR;
                                else
                                    r_state <= R_WAIT;
                            end
                         end

                R_WAIT : begin
                            // Wait for the selected slave to assert rvalid
                            if(m_axi_rvalid && m_axi_rready)
                                r_state <= R_IDLE;
                         end

                R_DECERR : begin
                            // Generate read response with decode error
                            if(m_axi_rready)
                                r_state <= R_IDLE;
                         end

                endcase
            end

    end
//-------------------------------------------------------------------------------------------------------


    //------------------------------------------------------------------------------
    //? WRITE ADDRESS CHANNEL
    //* only accepts new address when in IDLE state
    //------------------------------------------------------------------------------

    always_comb begin

        // DEFAULT : deassert all
        s0_axi_awvalid = 1'b0; s0_axi_awaddr = '0; s0_axi_awprot = '0;
        s1_axi_awvalid = 1'b0; s1_axi_awaddr = '0; s1_axi_awprot = '0;
        s2_axi_awvalid = 1'b0; s2_axi_awaddr = '0; s2_axi_awprot = '0;
        s3_axi_awvalid = 1'b0; s3_axi_awaddr = '0; s3_axi_awprot = '0;
        m_axi_awready = 1'b0;

        // Only accept write address in IDLE state
        if(w_state==W_IDLE && m_axi_awvalid && !aw_decerr)
        begin
            case (aw_slave_sel)
                SEL_S0 : begin
                    s0_axi_awvalid = 1'b1;
                    s0_axi_awaddr  = m_axi_awaddr;
                    s0_axi_awprot  = m_axi_awprot;
                    m_axi_awready = s0_axi_awready;
                end
                SEL_S1 : begin
                    s1_axi_awvalid = 1'b1;
                    s1_axi_awaddr  = m_axi_awaddr;
                    s1_axi_awprot  = m_axi_awprot;
                    m_axi_awready = s1_axi_awready;
                end
                SEL_S2 : begin
                    s2_axi_awvalid = 1'b1;
                    s2_axi_awaddr  = m_axi_awaddr;
                    s2_axi_awprot  = m_axi_awprot;
                    m_axi_awready = s2_axi_awready;
                end
                SEL_S3 : begin
                    s3_axi_awvalid = 1'b1;
                    s3_axi_awaddr  = m_axi_awaddr;
                    s3_axi_awprot  = m_axi_awprot;
                    m_axi_awready = s3_axi_awready;
                end
            endcase
        end
        else if (w_state == W_IDLE && m_axi_awvalid && aw_decerr)
        begin
            // Accept address for decode error (no slave selected)
            m_axi_awready = 1'b1;
        end
    end

    // =========================================================
    //? WRITE DATA CHANNEL
    // Route using w_slave_reg (captured when addr accepted)
    // =========================================================
    always_comb begin
        // Default: deassert all
        s0_axi_wvalid = 1'b0; s0_axi_wdata = '0; s0_axi_wstrb = '0;
        s1_axi_wvalid = 1'b0; s1_axi_wdata = '0; s1_axi_wstrb = '0;
        s2_axi_wvalid = 1'b0; s2_axi_wdata = '0; s2_axi_wstrb = '0;
        s3_axi_wvalid = 1'b0; s3_axi_wdata = '0; s3_axi_wstrb = '0;
        m_axi_wready  = 1'b0;

        // Only route data when in W_DATA state (address already captured)
        if (w_state == W_DATA)
        begin
            case (w_slave_reg)
                SEL_S0: begin
                    s0_axi_wvalid = m_axi_wvalid;
                    s0_axi_wdata  = m_axi_wdata;
                    s0_axi_wstrb  = m_axi_wstrb;
                    m_axi_wready  = s0_axi_wready;
                end
                SEL_S1: begin
                    s1_axi_wvalid = m_axi_wvalid;
                    s1_axi_wdata  = m_axi_wdata;
                    s1_axi_wstrb  = m_axi_wstrb;
                    m_axi_wready  = s1_axi_wready;
                end
                SEL_S2: begin
                    s2_axi_wvalid = m_axi_wvalid;
                    s2_axi_wdata  = m_axi_wdata;
                    s2_axi_wstrb  = m_axi_wstrb;
                    m_axi_wready  = s2_axi_wready;
                end
                SEL_S3: begin
                    s3_axi_wvalid = m_axi_wvalid;
                    s3_axi_wdata  = m_axi_wdata;
                    s3_axi_wstrb  = m_axi_wstrb;
                    m_axi_wready  = s3_axi_wready;
                end
            endcase
        end
        else if (w_state == W_DECERR)
        begin
            // Absorb data quietly for decode error
            m_axi_wready = m_axi_wvalid; // Accept immediately
        end
    end

    // =========================================================
    //? WRITE RESPONSE CHANNEL
    // =========================================================
    always_comb begin
        m_axi_bvalid  = 1'b0;
        m_axi_bresp   = 2'b00; // OKAY
        s0_axi_bready = 1'b0;
        s1_axi_bready = 1'b0;
        s2_axi_bready = 1'b0;
        s3_axi_bready = 1'b0;

        if (w_state == W_RESP)
        begin
            case (w_slave_reg)
                SEL_S0: begin
                    m_axi_bvalid  = s0_axi_bvalid;
                    m_axi_bresp   = s0_axi_bresp;
                    s0_axi_bready = m_axi_bready;
                end
                SEL_S1: begin
                    m_axi_bvalid  = s1_axi_bvalid;
                    m_axi_bresp   = s1_axi_bresp;
                    s1_axi_bready = m_axi_bready;
                end
                SEL_S2: begin
                    m_axi_bvalid  = s2_axi_bvalid;
                    m_axi_bresp   = s2_axi_bresp;
                    s2_axi_bready = m_axi_bready;
                end
                SEL_S3: begin
                    m_axi_bvalid  = s3_axi_bvalid;
                    m_axi_bresp   = s3_axi_bresp;
                    s3_axi_bready = m_axi_bready;
                end
            endcase
        end
        else if (w_state == W_DECERR)
        begin
            // Return DECERR for unmapped addresses
            m_axi_bvalid = 1'b1;
            m_axi_bresp  = 2'b11; // DECERR
        end
    end

    // =========================================================
    //? READ ADDRESS CHANNEL
    // =========================================================
    always_comb begin
        s0_axi_arvalid = 1'b0; s0_axi_araddr = '0; s0_axi_arprot = '0;
        s1_axi_arvalid = 1'b0; s1_axi_araddr = '0; s1_axi_arprot = '0;
        s2_axi_arvalid = 1'b0; s2_axi_araddr = '0; s2_axi_arprot = '0;
        s3_axi_arvalid = 1'b0; s3_axi_araddr = '0; s3_axi_arprot = '0;
        m_axi_arready  = 1'b0;

        if (r_state == R_IDLE && m_axi_arvalid && !ar_decerr)
        begin
            case (ar_slave_sel)
                SEL_S0: begin
                    s0_axi_arvalid = 1'b1;
                    s0_axi_araddr  = m_axi_araddr;
                    s0_axi_arprot  = m_axi_arprot;
                    m_axi_arready  = s0_axi_arready;
                end
                SEL_S1: begin
                    s1_axi_arvalid = 1'b1;
                    s1_axi_araddr  = m_axi_araddr;
                    s1_axi_arprot  = m_axi_arprot;
                    m_axi_arready  = s1_axi_arready;
                end
                SEL_S2: begin
                    s2_axi_arvalid = 1'b1;
                    s2_axi_araddr  = m_axi_araddr;
                    s2_axi_arprot  = m_axi_arprot;
                    m_axi_arready  = s2_axi_arready;
                end
                SEL_S3: begin
                    s3_axi_arvalid = 1'b1;
                    s3_axi_araddr  = m_axi_araddr;
                    s3_axi_arprot  = m_axi_arprot;
                    m_axi_arready  = s3_axi_arready;
                end
            endcase

        end
        else if (r_state == R_WAIT)
        begin
            case (r_slave_reg)
                SEL_S0: s0_axi_arprot = r_prot_reg;
                SEL_S1: s1_axi_arprot = r_prot_reg;
                SEL_S2: s2_axi_arprot = r_prot_reg;
                SEL_S3: s3_axi_arprot = r_prot_reg;
            endcase

        end
        else if (r_state == R_IDLE && m_axi_arvalid && ar_decerr)
        begin
            // Accept address even for decode error
            m_axi_arready = 1'b1;
        end
    end

    // =========================================================
    //? READ DATA CHANNEL
    // =========================================================
    always_comb begin
        m_axi_rdata   = 32'hDEAD_BEEF; // Obvious bad value for debug
        m_axi_rresp   = 2'b00;
        m_axi_rvalid  = 1'b0;
        s0_axi_rready = 1'b0;
        s1_axi_rready = 1'b0;
        s2_axi_rready = 1'b0;
        s3_axi_rready = 1'b0;

        if (r_state == R_WAIT)
        begin
            case (r_slave_reg)
                SEL_S0: begin
                    m_axi_rdata   = s0_axi_rdata;
                    m_axi_rresp   = s0_axi_rresp;
                    m_axi_rvalid  = s0_axi_rvalid;
                    s0_axi_rready = m_axi_rready;
                end
                SEL_S1: begin
                    m_axi_rdata   = s1_axi_rdata;
                    m_axi_rresp   = s1_axi_rresp;
                    m_axi_rvalid  = s1_axi_rvalid;
                    s1_axi_rready = m_axi_rready;
                end
                SEL_S2: begin
                    m_axi_rdata   = s2_axi_rdata;
                    m_axi_rresp   = s2_axi_rresp;
                    m_axi_rvalid  = s2_axi_rvalid;
                    s2_axi_rready = m_axi_rready;
                end
                SEL_S3: begin
                    m_axi_rdata   = s3_axi_rdata;
                    m_axi_rresp   = s3_axi_rresp;
                    m_axi_rvalid  = s3_axi_rvalid;
                    s3_axi_rready = m_axi_rready;
                end
            endcase
        end
        else if (r_state == R_DECERR)
        begin
            m_axi_rdata  = 32'hDEADDEAD;
            m_axi_rresp  = 2'b11; // DECERR
            m_axi_rvalid = 1'b1;
        end
    end

endmodule
