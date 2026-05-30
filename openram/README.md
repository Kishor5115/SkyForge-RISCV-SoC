# OpenRAM SKY130 SRAM Generation

This directory targets a 4KB, 32-bit x 1024, byte-write, single-port SKY130
SRAM macro:

```sh
OPENRAM_ROOT=/home/kishor/OpenRAM \
PDK_ROOT=/home/kishor/pdk/ciel/sky130/versions/0fe599b2afb6708d281543108caf8310912f54af \
OPENRAM_TMP=/tmp/openram_kishor_riscv_retry \
./openram/generate_views.py openram/config.py
```

Expected outputs land in `openram/build/`:

- `sky130_sram_4kbyte_1rw_32x1024_8.sp`
- `sky130_sram_4kbyte_1rw_32x1024_8.lvs.sp`
- `sky130_sram_4kbyte_1rw_32x1024_8.lvs`
- `sky130_sram_4kbyte_1rw_32x1024_8.gds`
- `sky130_sram_4kbyte_1rw_32x1024_8.lef`
- `sky130_sram_4kbyte_1rw_32x1024_8.v`
- `sky130_sram_4kbyte_1rw_32x1024_8_TT_1p8V_25C.lib`
- `sky130_sram_4kbyte_1rw_32x1024_8.lib`

The custom driver writes the physical/frontend views before the delay-stimulus
or Liberty path. This avoids losing an otherwise completed layout when OpenRAM
v1.2.49 hits the SKY130 spare-column timing-path issue.
