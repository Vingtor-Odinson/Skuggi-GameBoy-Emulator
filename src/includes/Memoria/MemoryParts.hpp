#pragma once

#include <stdint.h>

class CPU;

class MemoryPart
{     
    public:
        CPU* cpu;
        uint32_t memoryOffset; //O offset para que possamos lidar com acesso externo a memória (Normalmente o último bit anterior + 1)
        uint8_t* memory; //A memória para esse pedaço

        virtual void Write(uint16_t address, uint8_t value); //Funções básicas pra escrever e ler
        virtual uint8_t Read(uint16_t address);
};