
// AXI4-Lite RAM Slave - 128KB Memory
// Supports byte-granular writes with proper FSM-based AXI handshaking.
// Write channel tracks AW/W independently with backpressure.
// Read channel deasserts arready while response is pending.

module axi_ram #(
    parameter ADDR_WIDTH = 17,     // 128KB (2^17 bytes)
    parameter DATA_WIDTH = 32,
    parameter MEM_INIT_FILE = ""   // Optional: boot code initialization
)(
    input  logic clk,
    input  logic resetn,

    // AXI4-Lite Slave Write Address Channel
    input  logic [ADDR_WIDTH-1:0] axi_awaddr,
    input  logic        [ 2:0] axi_awprot,
    input  logic                  axi_awvalid,
    output logic                  axi_awready,

    // AXI4-Lite Slave Write Data Channel
    input  logic [DATA_WIDTH-1:0] axi_wdata,
    input  logic                  axi_wvalid,
    output logic                  axi_wready,
    input  logic [DATA_WIDTH/8-1:0] axi_wstrb,

    // AXI4-Lite Slave Write Response Channel
    output logic                  axi_bvalid,
    input  logic                  axi_bready,
    output logic [1:0]            axi_bresp,
    
    // AXI4-Lite Slave Read Address Channel
    input  logic [ADDR_WIDTH-1:0] axi_araddr,
    input  logic        [ 2:0] axi_arprot,
    input  logic                  axi_arvalid,
    output logic                  axi_arready,
    
    // AXI4-Lite Slave Read Data Channel
    output logic [DATA_WIDTH-1:0] axi_rdata,
    output logic                  axi_rvalid,
    input  logic                  axi_rready,
    output logic [1:0]            axi_rresp
);

    // Response: always OKAY for normal RAM
    assign axi_bresp = 2'b00;
    assign axi_rresp = 2'b00;

    // Parameter validation (simulation-only, ignored by synthesis)
    initial begin
        if (DATA_WIDTH % 8 != 0) begin
            $error("axi_ram: DATA_WIDTH must be a multiple of 8 (got %0d)", DATA_WIDTH);
            $finish;
        end
    end

    // Memory: 128KB / 4 bytes = 32K words (32Kx32-bit)
    localparam MEM_DEPTH = 2 ** (ADDR_WIDTH - 2);
    logic [DATA_WIDTH-1:0] memory [0:MEM_DEPTH-1];

    // Initialize memory (optional: load from file)
    initial begin
        for (int i = 0; i < MEM_DEPTH; i++) begin
            memory[i] = 32'b0;
        end
        if (MEM_INIT_FILE != "")
            $readmemh(MEM_INIT_FILE, memory);
    end

    //==========================================================================
    // Write Channel — FSM with independent AW/W tracking
    //==========================================================================
    logic                  aw_done;          // Address received for current txn
    logic                  w_done;           // Data received for current txn
    logic                  bvalid_reg;
    logic [ADDR_WIDTH-3:0] aw_addr_reg;      // Captured write word address
    logic [DATA_WIDTH-1:0] w_data_reg;       // Captured write data
    logic [DATA_WIDTH/8-1:0] w_strb_reg;     // Captured write strobes

    // Combinational ready: accept if not yet received and no pending response
    assign axi_awready = !aw_done && !bvalid_reg;
    assign axi_wready  = !w_done  && !bvalid_reg;
    assign axi_bvalid  = bvalid_reg;

    always_ff @(posedge clk) begin
        if (!resetn) begin
            aw_done    <= 1'b0;
            w_done     <= 1'b0;
            bvalid_reg <= 1'b0;
            aw_addr_reg <= '0;
            w_data_reg  <= '0;
            w_strb_reg  <= '0;
        end else begin
            // Capture write address
            if (axi_awvalid && axi_awready) begin
                aw_addr_reg <= axi_awaddr[ADDR_WIDTH-1:2];
                aw_done     <= 1'b1;
            end

            // Capture write data
            if (axi_wvalid && axi_wready) begin
                w_data_reg <= axi_wdata;
                w_strb_reg <= axi_wstrb;
                w_done     <= 1'b1;
            end

            // Both received: perform memory write and generate response
            if (aw_done && w_done && !bvalid_reg) begin
                if (w_strb_reg[0])
                    memory[aw_addr_reg][7:0]   <= w_data_reg[7:0];
                if (w_strb_reg[1])
                    memory[aw_addr_reg][15:8]  <= w_data_reg[15:8];
                if (w_strb_reg[2])
                    memory[aw_addr_reg][23:16] <= w_data_reg[23:16];
                if (w_strb_reg[3])
                    memory[aw_addr_reg][31:24] <= w_data_reg[31:24];
                bvalid_reg <= 1'b1;
            end

            // Response accepted: clear for next transaction
            if (bvalid_reg && axi_bready) begin
                bvalid_reg <= 1'b0;
                aw_done    <= 1'b0;
                w_done     <= 1'b0;
            end
        end
    end

    //==========================================================================
    // Read Channel — FSM with backpressure
    //==========================================================================
    logic [DATA_WIDTH-1:0] rdata_reg;
    logic                  rvalid_reg;

    // Combinational ready: accept if no pending response
    assign axi_arready = !rvalid_reg;
    assign axi_rvalid  = rvalid_reg;
    assign axi_rdata   = rdata_reg;

    always_ff @(posedge clk) begin
        if (!resetn) begin
            rvalid_reg <= 1'b0;
            rdata_reg  <= '0;
        end else begin
            // Accept read address and fetch from memory
            if (axi_arvalid && axi_arready) begin
                rdata_reg  <= memory[axi_araddr[ADDR_WIDTH-1:2]];
                rvalid_reg <= 1'b1;
            end

            // Response accepted: ready for next read
            if (rvalid_reg && axi_rready)
                rvalid_reg <= 1'b0;
        end
    end

endmodule