rom = bytes([
    0x00,       # NOP
    0x00,       # NOP
    0x00        # NOP (nunca executado)
])

with open("testNOP.gb", "wb") as f:
    f.write(rom)