/*
 * OpenRAM SKY130 4KB 1RW SRAM macro declaration.
 *
 * Synced with the latest OpenRAM build in openram/build.
 * The macro includes one spare column, so din0/dout0 are 33 bits wide and
 * spare_wen0 controls the spare bit. The SoC wrapper ties spare_wen0 low and
 * uses only dout0[31:0].
 */
(* blackbox *)
module sky130_sram_4kbyte_1rw_32x1024_8(
`ifdef USE_POWER_PINS
    inout vccd1,
    inout vssd1,
`endif
    input  clk0,
    input  csb0,
    input  web0,
    input  [3:0]  wmask0,
    input  spare_wen0,
    input  [10:0] addr0,
    input  [32:0] din0,
    output [32:0] dout0
  );

  parameter NUM_WMASKS = 4;
  parameter DATA_WIDTH = 33;
  parameter ADDR_WIDTH = 11;
  parameter RAM_DEPTH = 1 << ADDR_WIDTH;
  parameter DELAY = 3;
  parameter VERBOSE = 1;
  parameter T_HOLD = 1;

endmodule
