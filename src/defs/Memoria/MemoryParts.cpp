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

void BANK00::MostraPrimeiros16()
{
    std::cout << "Primeiros 16 bytes da ROM" << std::endl;
    
    for(int i = 0; i < 16; i++)
    {
        printf("%02X ", memory[i]);
    }

    std::cout << std::endl << std::endl  << std::endl;
}

void BANK00::PrintaLogoNintendo()
{
    std::cout << "Logo da Nintendo" << std::endl;
    
    for(int i = 0x0104; i < 0x0134; i++)
    {
        printf("%02X ", memory[i]);
    }

    std::cout << std::endl << std::endl  << std::endl;
}

void BANK00::PrintaTituloJogo()
{
    std::cout << "Título do jogo" << std::endl;
    
    for(int i = 0x0134; i < 0x0145; i++)
    {
        std::cout << static_cast<char>(memory[i]);
    }

    std::cout << std::endl << std::endl  << std::endl;
}