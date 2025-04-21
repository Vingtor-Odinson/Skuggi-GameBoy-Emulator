#pragma once

#include <stdint.h>
#include <Memoria/BANK00.hpp>

class CPU;

class Memory
{   
    public:

        CPU* cpu;
        BANK00* bank00;
    
        Memory( CPU* pCPU );
        ~Memory();

        static uint8_t GetMemoryCategory( uint16_t address );
        uint8_t ReadMemory(uint16_t address);
        void WriteMemory( uint16_t address, uint8_t value );
};

