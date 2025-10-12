#pragma once

#include <stdint.h>
#include <Memoria/BANK00.hpp>
#include <Memoria/BANKNN.hpp>
#include <Memoria/IORegisters.hpp>
#include <Memoria/VRAM.hpp>

#include "Memoria/HRAM.hpp"
#include "Memoria/OAM.hpp"
#include "Memoria/WRAM.hpp"
#include "CPU/Device.hpp"

class Bus;

class CPU;

class Memory : public Device
{
private:
    Bus* bus;
    BANK00* bank00;
    BANKNN* banknn;
    OAM* oam;
    WRAM* wram1;
    WRAM* wram2;
    VRAM* vram;
    HRAM* hram;
    IORegisters* ioRegs;

    MemoryPart* GetMemoryPart(uint16_t address);

public:
    uint8_t interruptEnableReg;
    explicit Memory(Bus* bus);
    ~Memory();

    uint8_t read(const uint16_t& address) override;
    void write(const uint16_t& address, const uint8_t& value) override;

    // 0x0000 - 0xFFFF
};
