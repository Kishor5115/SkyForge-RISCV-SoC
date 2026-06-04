// =============================================================================
// spi_seq.sv - SPI master exercise sequence
// Purpose : Configures clock divider / mode / CS, enables the controller,
//           pushes a TX frame and reads back the RX FIFO (loopback miso=mosi).
// Author  : <author placeholder>
// Date    : <date placeholder>
// =============================================================================

class spi_seq extends apb_base_seq;
    `uvm_object_utils(spi_seq)

    rand bit [15:0] sckdiv;
    rand bit [1:0]  sckmode;
    rand bit [1:0]  csid;
    rand bit [7:0]  tx_byte;

    constraint c_div { sckdiv inside {[16'd1 : 16'd8]}; }

    function new(string name = "spi_seq");
        super.new(name);
    endfunction

    task body();
        bit [31:0] rd; bit err;
        int unsigned guard;
        if (!this.randomize()) `uvm_error("SPI_SEQ", "randomize failed")
        write32(`SPI_SCKDIV,  {16'h0, sckdiv});
        read32 (`SPI_SCKDIV,  rd, err);   // scoreboard checks vs shadow
        write32(`SPI_SCKMODE, {30'h0, sckmode});
        write32(`SPI_CSID,    {30'h0, csid});
        write32(`SPI_FMT,     32'h0008_0000); // 8-bit frame, MSB-first
        write32(`SPI_CTRL,    32'h1);         // enable
        write32(`SPI_TXDATA,  {24'h0, tx_byte});
        // Poll until the transfer completes and RX FIFO is non-empty
        guard = 0;
        do begin
            read32(`SPI_STATUS, rd, err);
            guard++;
        end while (rd[30] && guard < 2000);   // bit[30] = rxempty
        read32(`SPI_RXDATA, rd, err);
        `uvm_info("SPI_SEQ", $sformatf("RX=0x%02h (tx=0x%02h)", rd[7:0], tx_byte), UVM_MEDIUM)
    endtask

endclass
