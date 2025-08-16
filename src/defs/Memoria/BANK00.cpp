#include<iostream>
#include<CPU/CPU.hpp>
#include<ROM/ROMLoader.hpp>
#include<Memoria/MemoryParts.hpp>
#include<Memoria/BANK00.hpp>

BANK00::BANK00( Bus* pBus )
{   
    bus = pBus;
}

void BANK00::Write( uint16_t address, uint8_t value ){
    bus->write(DeviceEnum::Cartridge, address, value); //manda para o cartucho lidar com a escrita...
}

uint8_t BANK00::Read( uint16_t address )
{   
    return bus->read(DeviceEnum::Cartridge, address); //Lê do banco fixo do cartucho (pode alterar de acordo com o MBC)
}

void BANK00::MostraPrimeiros16()
{
    std::cout << "Primeiros 16 bytes da ROM" << std::endl;
    
    for(int i = 0; i < 16; i++)
    {
        printf("%02X ", Read(i));
    }

    std::cout << std::endl << std::endl  << std::endl   ;
}

void BANK00::PrintaLogoNintendo()
{
    std::cout << "Logo da Nintendo" << std::endl;
    
    for(int i = 0x0104; i < 0x0134; i++)
    {
        printf("%02X ", Read(i));
    }

    std::cout << std::endl << std::endl  << std::endl;
}

void BANK00::PrintaTituloJogo()
{
    std::cout << "Título do jogo" << std::endl;
    
    for(int i = 0x0134; i < 0x0145; i++)
    {
        std::cout << static_cast<char>(Read(i));
    }

    std::cout << std::endl << std::endl  << std::endl;
}
