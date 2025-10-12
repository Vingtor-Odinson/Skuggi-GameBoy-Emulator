#include<Memoria/WRAM.hpp>
#include <stdexcept>

WRAM::WRAM(const uint16_t& offset)
    : memoryOffset(offset)
{
    memory.fill(0);
}

void WRAM::write(uint16_t address, uint8_t value)
{
    //This address is coming from the memory and has a offset, that's the reason behind the "minus" operation here
    if (address >= memoryOffset && address < (memoryOffset + memorySize))
    {
        memory[address - memoryOffset] = value;
    }
    else
    {
        throw std::out_of_range("Foi tentado acessar memória fora da região da WRAM.");
    }
}

uint8_t WRAM::read(uint16_t address)
{
    //This address is coming from the memory and has a offset, that's the reason behind the "minus" operation here
    if (address < memoryOffset || address >= (memoryOffset + memorySize))
    {
        throw std::out_of_range("Foi tentado acessar memória fora da região da WRAM.");
    }

    return memory[address - memoryOffset];
}
