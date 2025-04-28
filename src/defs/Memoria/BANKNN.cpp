#include<iostream>
#include<CPU/CPU.hpp>
#include<ROM/ROMLoader.hpp>
#include<Memoria/MemoryParts.hpp>
#include<Memoria/BANKNN.hpp>

BANKNN::BANKNN( CPU* pCpu )
{   
    cpu = pCpu;
    romLoader = cpu->romLoader;
}

void BANKNN::Write( uint16_t address, uint8_t value ){}

uint8_t BANKNN::Read( uint16_t address )
{   //TO-DO: After MBC implementation 
    return cpu->romLoader->ReadROM(address);
}

void BANKNN::MostraPrimeiros16()
{
    std::cout << "Primeiros 16 bytes da ROM" << std::endl;
    
    for(int i = 0; i < 16; i++)
    {
        printf("%02X ", Read(i));
    }

    std::cout << std::endl << std::endl  << std::endl;
}

void BANKNN::PrintaLogoNintendo()
{
    std::cout << "Logo da Nintendo" << std::endl;
    
    for(int i = 0x0104; i < 0x0134; i++)
    {
        printf("%02X ", Read(i));
    }

    std::cout << std::endl << std::endl  << std::endl;
}

void BANKNN::PrintaTituloJogo()
{
    std::cout << "Título do jogo" << std::endl;
    
    for(int i = 0x0134; i < 0x0145; i++)
    {
        std::cout << static_cast<char>(Read(i));
    }

    std::cout << std::endl << std::endl  << std::endl;
}
