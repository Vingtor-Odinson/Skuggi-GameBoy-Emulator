#include<iostream>
#include <Memoria/MemoryParts.hpp>

void MemoryPart::Write( uint16_t address, uint8_t value )
{   
    memory[address] = value;
}

uint8_t MemoryPart::Read( uint16_t address )
{   
    return memory[address];
}

BANK00::BANK00()
{   
    memoryOffset = 0x0000;
    memory = new uint8_t[0x4000];
    for(int i = 0x0000; i < 0x4000; i++)
    {
        memory[i] = 0x0;
    }
}

BANK00::~BANK00()
{
    delete[] memory;
}