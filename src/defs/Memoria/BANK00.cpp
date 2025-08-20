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