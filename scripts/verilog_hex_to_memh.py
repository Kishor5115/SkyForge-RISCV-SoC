#!/usr/bin/env python3
import sys

def convert(infile, offset_hex, outfile):
    offset = int(offset_hex, 16)
    
    # Read the verilog hex file (byte-wise)
    memory = {}
    current_addr = 0
    with open(infile, 'r') as f:
        for line in f:
            line = line.split('//')[0].strip()
            if not line: continue
            
            tokens = line.split()
            for token in tokens:
                if token.startswith('@'):
                    current_addr = int(token[1:], 16)
                else:
                    # It's a hex byte
                    memory[current_addr] = int(token, 16)
                    current_addr += 1
                    
    if not memory:
        open(outfile, 'w').close()
        return
        
    # Write to outfile as 32-bit words
    start_addr = offset
    max_addr = max(memory.keys())
    
    bytes_written = (max_addr - start_addr) + 1
    words_written = bytes_written // 4 + (1 if bytes_written % 4 else 0)
    
    print(f"Written {bytes_written} bytes ({words_written} words) to {outfile}")
    
    with open(outfile, 'w') as f:
        for addr in range(start_addr, max_addr + 1, 4):
            b0 = memory.get(addr, 0)
            b1 = memory.get(addr + 1, 0)
            b2 = memory.get(addr + 2, 0)
            b3 = memory.get(addr + 3, 0)
            
            # Little endian formatting
            word = (b3 << 24) | (b2 << 16) | (b1 << 8) | b0
            f.write(f"{word:08x}\n")

if __name__ == '__main__':
    if len(sys.argv) != 4:
        print("Usage: python3 verilog_hex_to_memh.py <infile> <offset> <outfile>")
        sys.exit(1)
    convert(sys.argv[1], sys.argv[2], sys.argv[3])
