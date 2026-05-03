`timescale 1ns / 1ps

module soc_core_tb;
    localparam CLK_PERIOD = 10;
    localparam UART_BAUD_DIV = 8;
    localparam UART_BIT_CYCLES = UART_BAUD_DIV * 16;

    logic        clk_i;
    logic        rst_ni;

    logic        uart_tx_o;
    logic        uart_rx_i;

    logic [31:0] gpio_in_i;
    logic [31:0] gpio_out_o;
    logic [31:0] gpio_oe_o;

    logic        spi_sclk_o;
    logic        spi_mosi_o;
    logic        spi_miso_i;
    logic [3:0]  spi_cs_n_o;

    logic        flash_sclk_o;
    logic        flash_cs_n_o;
    logic        flash_mosi_o;
    logic        flash_miso_i;

    logic        jtag_tck_i;
    logic        jtag_tms_i;
    logic        jtag_tdi_i;
    logic        jtag_tdo_o;

    logic        trap_o;

    integer pass_count = 0;
    integer fail_count = 0;
    integer uart_edge_count = 0;
    integer cycle_count = 0;

    soc_core #(
        .MEM_INIT_FILE("periph_test_boot.hex"),
        .BOOTROM_ADDR_WIDTH(14)
    ) dut (
        .clk_i        (clk_i),
        .rst_ni       (rst_ni),
        .uart_tx_o    (uart_tx_o),
        .uart_rx_i    (uart_rx_i),
        .gpio_in_i    (gpio_in_i),
        .gpio_out_o   (gpio_out_o),
        .gpio_oe_o    (gpio_oe_o),
        .spi_sclk_o   (spi_sclk_o),
        .spi_mosi_o   (spi_mosi_o),
        .spi_miso_i   (spi_miso_i),
        .spi_cs_n_o   (spi_cs_n_o),
        .flash_sclk_o (flash_sclk_o),
        .flash_cs_n_o (flash_cs_n_o),
        .flash_mosi_o (flash_mosi_o),
        .flash_miso_i (flash_miso_i),
        .jtag_tck_i   (jtag_tck_i),
        .jtag_tms_i   (jtag_tms_i),
        .jtag_tdi_i   (jtag_tdi_i),
        .jtag_tdo_o   (jtag_tdo_o),
        .trap_o       (trap_o)
    );

    assign spi_miso_i = spi_mosi_o;
    assign flash_miso_i = 1'b0;

    initial begin
        clk_i = 1'b0;
        forever #(CLK_PERIOD / 2) clk_i = ~clk_i;
    end

    initial begin
        uart_rx_i  = 1'b1;
        gpio_in_i  = 32'h0;
        jtag_tck_i = 1'b0;
        jtag_tms_i = 1'b1;
        jtag_tdi_i = 1'b0;
        rst_ni     = 1'b0;
        repeat (20) @(posedge clk_i);
        rst_ni     = 1'b1;
    end

    task uart_send_byte;
        input [7:0] data;
        integer i;
        begin
            uart_rx_i = 1'b0;
            repeat (UART_BIT_CYCLES) @(posedge clk_i);
            for (i = 0; i < 8; i = i + 1) begin
                uart_rx_i = data[i];
                repeat (UART_BIT_CYCLES) @(posedge clk_i);
            end
            uart_rx_i = 1'b1;
            repeat (UART_BIT_CYCLES) @(posedge clk_i);
        end
    endtask

    task uart_capture_byte;
        output [7:0] data;
        integer i;
        begin
            wait (uart_tx_o == 1'b0);
            repeat (UART_BIT_CYCLES / 2) @(posedge clk_i);
            if (uart_tx_o !== 1'b0) begin
                data = 8'h00;
                disable uart_capture_byte;
            end
            for (i = 0; i < 8; i = i + 1) begin
                repeat (UART_BIT_CYCLES) @(posedge clk_i);
                data[i] = uart_tx_o;
            end
            repeat (UART_BIT_CYCLES) @(posedge clk_i);
        end
    endtask

    task jtag_clock;
        input  logic tms_val;
        input  logic tdi_val;
        output logic tdo_val;
        begin
            jtag_tms_i = tms_val;
            jtag_tdi_i = tdi_val;
            #2;
            jtag_tck_i = 1'b1;
            #2;
            jtag_tck_i = 1'b0;
            #2;
            tdo_val = jtag_tdo_o;
        end
    endtask

    task jtag_reset;
        integer i;
        logic tdo;
        begin
            for (i = 0; i < 6; i = i + 1) begin
                jtag_clock(1'b1, 1'b0, tdo);
            end
            jtag_clock(1'b0, 1'b0, tdo);
        end
    endtask

    task jtag_shift_ir;
        input [3:0] ir;
        integer i;
        logic tdo;
        begin
            jtag_clock(1'b1, 1'b0, tdo);
            jtag_clock(1'b1, 1'b0, tdo);
            jtag_clock(1'b0, 1'b0, tdo);
            jtag_clock(1'b0, 1'b0, tdo);
            for (i = 0; i < 4; i = i + 1) begin
                jtag_clock((i == 3), ir[i], tdo);
            end
            jtag_clock(1'b1, 1'b0, tdo);
            jtag_clock(1'b0, 1'b0, tdo);
        end
    endtask

    task jtag_shift_dr;
        input  logic        write;
        input  logic [7:0]  addr;
        input  logic [31:0] wdata;
        output logic [40:0] rdata;
        integer i;
        logic tdo;
        logic tdi_bit;
        begin
            rdata = 41'b0;
            jtag_clock(1'b1, 1'b0, tdo);
            jtag_clock(1'b0, 1'b0, tdo);
            jtag_clock(1'b0, 1'b0, tdo);
            for (i = 0; i < 41; i = i + 1) begin
                if (i == 0)
                    tdi_bit = write;
                else if (i < 9)
                    tdi_bit = addr[i - 1];
                else
                    tdi_bit = wdata[i - 9];
                jtag_clock((i == 40), tdi_bit, tdo);
                rdata[i] = tdo;
            end
            jtag_clock(1'b1, 1'b0, tdo);
            jtag_clock(1'b0, 1'b0, tdo);
        end
    endtask

    task jtag_write_reg;
        input logic [7:0] addr;
        input logic [31:0] data;
        logic [40:0] rdata;
        begin
            jtag_shift_ir(4'b0010);
            jtag_shift_dr(1'b1, addr, data, rdata);
        end
    endtask

    task jtag_read_reg;
        input  logic [7:0] addr;
        output logic [31:0] data;
        logic [40:0] rdata;
        begin
            jtag_shift_ir(4'b0010);
            jtag_shift_dr(1'b0, addr, 32'h0, rdata);
            data = rdata[40:9];
        end
    endtask

    initial begin
        $dumpfile("sim/soc_core_tb.vcd");
        $dumpvars(0, soc_core_tb);
    end

    always @(negedge uart_tx_o) begin
        if (rst_ni) begin
            uart_edge_count = uart_edge_count + 1;
            $display("[INFO] UART start bit at t=%0t", $time);
        end
    end

    always @(posedge clk_i) begin
        if (!rst_ni) begin
            cycle_count <= 0;
        end else begin
            cycle_count <= cycle_count + 1;
            if ((cycle_count % 500000) == 0) begin
                $display("[INFO] heartbeat t=%0t trap=%0b gpio_out=0x%08h uart_edges=%0d", $time, trap_o, gpio_out_o, uart_edge_count);
            end
        end
    end

    always @(posedge trap_o) begin
        $display("[INFO] trap asserted at t=%0t", $time);
    end

    initial begin
        reg [7:0] ch;
        wait (rst_ni == 1'b1);
        forever begin
            uart_capture_byte(ch);
            if (ch != 8'h00)
                $write("%c", ch);
        end
    end

    initial begin
        reg [31:0] last_gpio;
        last_gpio = 32'h0;
        wait (rst_ni == 1'b1);
        forever begin
            @(posedge clk_i);
            if (gpio_out_o !== last_gpio) begin
                $display("[INFO] GPIO_OUT = 0x%08h", gpio_out_o);
                last_gpio = gpio_out_o;
            end
        end
    end

    initial begin
        wait (rst_ni == 1'b1);
        wait (gpio_out_o[7:4] == 4'h1);
        uart_send_byte(8'h55);
    end

    initial begin
        logic [31:0] rdata;
        wait (rst_ni == 1'b1);
        wait (gpio_out_o[7:4] == 4'h2);

        jtag_reset();
        jtag_write_reg(8'h08, 32'h0000_0002);
        jtag_write_reg(8'h0C, 32'h2000_3000);
        jtag_write_reg(8'h10, 32'h0000_0005);
        jtag_write_reg(8'h18, 32'h0000_0001);
        repeat (2000) @(posedge clk_i);

        jtag_write_reg(8'h08, 32'h0000_0001);
        jtag_write_reg(8'h0C, 32'h2000_3000);
        jtag_write_reg(8'h18, 32'h0000_0001);
        repeat (2000) @(posedge clk_i);

        jtag_read_reg(8'h14, rdata);
        if (rdata === 32'h0000_0005) begin
            $display("[PASS] JTAG readback matches SPI_SCKDIV");
            pass_count = pass_count + 1;
        end else begin
            $display("[FAIL] JTAG readback expected 0x00000005, got 0x%08h", rdata);
            fail_count = fail_count + 1;
        end
    end

    initial begin
        integer timeout;
        timeout = 0;
        wait (rst_ni == 1'b1);
        while (gpio_out_o[1:0] == 2'b00 && timeout < 2000000) begin
            @(posedge clk_i);
            timeout = timeout + 1;
        end

        if (gpio_out_o[0]) begin
            $display("[PASS] Firmware reported PASS");
            pass_count = pass_count + 1;
        end else if (gpio_out_o[1]) begin
            $display("[FAIL] Firmware reported FAIL");
            fail_count = fail_count + 1;
        end else begin
            $display("[FAIL] Timeout waiting for firmware result");
            fail_count = fail_count + 1;
        end

        $display("[RESULT] pass=%0d fail=%0d", pass_count, fail_count);
        if (fail_count == 0)
            $display("[RESULT] SOC_CORE TEST PASSED");
        else
            $display("[RESULT] SOC_CORE TEST FAILED");

        $finish;
    end

endmodule
