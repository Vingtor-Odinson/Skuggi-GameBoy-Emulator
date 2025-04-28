#pragma once

#include <stdint.h>
#include <Memoria/BANK00.hpp>
#include <Memoria/BANKNN.hpp>
#include <Memoria/VRAM.hpp>

class CPU;

class Memory
{   
    public:

        CPU* cpu;
        BANK00* bank00;
        BANKNN* banknn;
        VRAM* vram;
    
        Memory( CPU* pCPU );
        ~Memory();

        static uint8_t GetMemoryCategory( uint16_t address );
        uint8_t ReadMemory(uint16_t address);
        void WriteMemory( uint16_t address, uint8_t value );
        MemoryPart* GetMemoryPart(uint16_t address);
};

