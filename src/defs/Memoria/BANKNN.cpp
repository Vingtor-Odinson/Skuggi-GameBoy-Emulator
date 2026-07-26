#include<iostream>
#include<CPU/CPU.hpp>
#include<ROM/ROMLoader.hpp>
#include<Memoria/MemoryParts.hpp>
#include<Memoria/BANKNN.hpp>

BANKNN::BANKNN( Bus* pBus )
{   
    bus = pBus;
}

void BANKNN::write( uint16_t address, uint8_t value ){
    bus->write(DeviceEnum::Cartridge, address, value);
}

uint8_t BANKNN::read( uint16_t address )
{
    return bus->read(DeviceEnum::Cartridge, address);
}