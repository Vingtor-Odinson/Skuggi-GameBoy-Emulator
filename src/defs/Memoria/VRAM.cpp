#include<Memoria/VRAM.hpp>

VRAM::VRAM()
{
    memory = new uint8_t[memorySize];
}

VRAM::~VRAM()
{
    delete[] memory;
}

void VRAM::Write( uint16_t address, uint8_t value )
{
    //This address is coming from the memory and has a offset, that's the reason behind the "minus" operation here
    memory[address - memoryOffset] = value;
} 

uint8_t VRAM::Read(uint16_t address)
{   
    //This address is coming from the memory and has a offset, that's the reason behind the "minus" operation here
    return memory[address - memoryOffset];
}