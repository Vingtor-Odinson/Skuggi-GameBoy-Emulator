#pragma once

#include <array>
#include<Memoria/MemoryParts.hpp>

class HRAM : public MemoryPart //Implementação da primeira parte da memória: O BANK00 que conterá o HEADER do jogo
{   
public:

    uint16_t memoryOffset = 0xFF80; //O offset para que possamos lidar com acesso externo a memória (Normalmente o último bit anterior + 1)
    static constexpr uint16_t memorySize = 0x2000;
    std::array<uint8_t, memorySize> memory;

    HRAM();
    uint8_t read(uint16_t address) override;
    void write(uint16_t address, uint8_t value) override;
};