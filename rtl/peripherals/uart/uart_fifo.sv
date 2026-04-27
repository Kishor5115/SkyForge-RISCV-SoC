/*
 * Parameterized Synchronous FIFO
 * Used for UART TX and RX buffers
 * 
 * Parameters:
 *   DATA_WIDTH - Width of data words (default: 8)
 *   DEPTH      - Number of entries (default: 8, must be power of 2)
 */

module uart_fifo #(
    parameter DATA_WIDTH = 8,
    parameter DEPTH      = 8,
    parameter ADDR_WIDTH = $clog2(DEPTH)
)(
    input logic                   clk,
    input logic                   resetn,

    // Write interface
    input logic                   wr_en,
    input logic [DATA_WIDTH-1:0]  wr_data,

    // Read interface
    input logic                   rd_en,
    output logic [DATA_WIDTH-1:0] rd_data,

    // Status flags
    output logic                  full,
    output logic                  empty,
    output logic [ADDR_WIDTH:0]   count
);

    // Memory array for FIFO storage
    logic [DATA_WIDTH-1:0] mem [0:DEPTH-1];

    // Pointers (extra bit for full/empty distinction)
    logic [ADDR_WIDTH:0] wr_ptr;
    logic [ADDR_WIDTH:0] rd_ptr;

    // Address Extraction
    wire [ADDR_WIDTH-1:0] wr_addr = wr_ptr[ADDR_WIDTH-1:0];
    wire [ADDR_WIDTH-1:0] rd_addr = rd_ptr[ADDR_WIDTH-1:0];

    // Status Flags
    assign empty = (wr_ptr == rd_ptr);
    assign full  = (wr_ptr[ADDR_WIDTH] != rd_ptr[ADDR_WIDTH] &&
                    wr_ptr[ADDR_WIDTH-1:0] == rd_ptr[ADDR_WIDTH-1:0]);
    assign count = (wr_ptr - rd_ptr);

    // Read data (combinational, always presents head of FIFO)
    assign rd_data = mem[rd_addr];

    // Write logic
    always_ff @(posedge clk)
    begin
        if(!resetn)
        begin
            wr_ptr = '0;
        end
        else if(wr_en && !full)
        begin
            mem[wr_addr] = wr_data;
            wr_ptr <= wr_ptr + 1;
        end
    end

    // Read logic
    always_ff @(posedge clk)
    begin
        if(!resetn)
        begin
            rd_ptr = '0;
        end
        else if(rd_en && !empty)
        begin
            rd_ptr <= rd_ptr + 1;
        end
    end


endmodule