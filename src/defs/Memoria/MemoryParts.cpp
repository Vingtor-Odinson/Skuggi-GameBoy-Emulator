#include<CPU/CPU.hpp>
#include<Memoria/MemoryParts.hpp>

void MemoryPart::Write( uint16_t address, uint8_t value )
{   
    memory[address] = value;
}

uint8_t MemoryPart::Read( uint16_t address )
{   
    return memory[address];
}