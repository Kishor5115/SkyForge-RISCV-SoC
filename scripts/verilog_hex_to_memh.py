#!/usr/bin/env python3
"""
Convert an objcopy Verilog hex dump (produced with
`objcopy --verilog-data-width=4 -O verilog`) into a flat $readmemh word file
suitable for preloading the behavioural SRAM model.

Input format (word-addressed, 32-bit big-endian-text word tokens):

    @00004000
    000000B7 00000137 000001B7 3340006F
    @00004004
    ...

Here the address after '@' is a WORD address (byte_addr >> 2) because the dump
was created with --verilog-data-width=4, and every token is the full 32-bit
word value as stored in memory (little-endian byte order on the target).

The output is one 8-hex-digit word per line, contiguous from the SRAM base
word up to the highest populated word; gaps are zero-filled. The behavioural
SRAM loads this with $readmemh into mem[0..], where mem[0] == SRAM base.

Usage:
    verilog_hex_to_memh.py <infile> <byte_offset_hex> <outfile>
        <byte_offset_hex>  SRAM base BYTE address, e.g. 0x00010000
"""
import sys


def convert(infile, offset_hex, outfile):
    byte_offset = int(offset_hex, 16)
    base_word = byte_offset >> 2          # objcopy emits word addresses

    words = {}                            # word_addr -> 32-bit value
    cur = 0
    with open(infile, "r") as f:
        for line in f:
            line = line.split("//")[0].strip()
            if not line:
                continue
            for tok in line.split():
                if tok.startswith("@"):
                    cur = int(tok[1:], 16)
                else:
                    words[cur] = int(tok, 16) & 0xFFFFFFFF
                    cur += 1

    if not words:
        open(outfile, "w").close()
        print(f"WARNING: no data parsed from {infile}; wrote empty {outfile}")
        return

    max_word = max(words.keys())
    if max_word < base_word:
        raise ValueError(
            f"highest word 0x{max_word:x} is below SRAM base word 0x{base_word:x}; "
            f"check the --verilog-data-width and offset arguments"
        )

    n = max_word - base_word + 1
    with open(outfile, "w") as f:
        for w in range(base_word, max_word + 1):
            f.write(f"{words.get(w, 0):08x}\n")

    print(f"Wrote {n} words ({n * 4} bytes) to {outfile} "
          f"(SRAM base 0x{byte_offset:08x}, base word 0x{base_word:x})")


if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Usage: verilog_hex_to_memh.py <infile> <byte_offset_hex> <outfile>")
        sys.exit(1)
    convert(sys.argv[1], sys.argv[2], sys.argv[3])
