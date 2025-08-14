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
{
    return cpu->romLoader->readSwapBank(address);
}