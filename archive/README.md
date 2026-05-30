# Archive

Files kept for reference but not part of the active build or test flows.

## tb/axi_interconect_tb.sv
Standalone unit testbench for `rtl/interconnect/axi_interconnect.sv`. It is not
wired into any `make` target and its filename is misspelled
("interconect"). The module it exercises is still in use (instantiated inside
`axi_interconnect_2m`), so the test is retained here rather than deleted. To run
it, compile it with Icarus against `rtl/interconnect/axi_interconnect.sv`.
