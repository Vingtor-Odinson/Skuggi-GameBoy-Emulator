#pragma once
#include<array>
#include "MemoryParts.hpp"

class OAM : public MemoryPart
{
public:
    uint16_t memoryOffset = 0xFE00;
    static constexpr uint16_t memorySize = 0xA0;
    std::array<uint8_t, memorySize> memory;

    OAM();
    uint8_t read(uint16_t address) override;
    void write(uint16_t address, uint8_t value) override;
};
