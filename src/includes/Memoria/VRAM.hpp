#pragma once

#include<Memoria/MemoryParts.hpp>

class VRAM : public MemoryPart //Implementação da primeira parte da memória: O BANK00 que conterá o HEADER do jogo
{   
    public:
        VRAM();
        ~VRAM();

        uint32_t memoryOffset = 0x8000; //O offset para que possamos lidar com acesso externo a memória (Normalmente o último bit anterior + 1)
        uint8_t memorySize = 0x2000;
        uint8_t* memory;

        uint8_t Read(uint16_t address) override;
        void Write(uint16_t address, uint8_t value) override;
};