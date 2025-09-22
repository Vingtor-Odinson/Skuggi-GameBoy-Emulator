#include<iostream>
#include "Memoria/MemoryParts.hpp"
#include "Memoria/IORegisters.hpp"

void IORegisters::Write( uint16_t address, uint8_t value ){
    registers[address - offset] = value; //manda para o cartucho lidar com a escrita...
}

uint8_t IORegisters::Read( uint16_t address )
{
    return registers[address - offset]; //Lê do banco fixo do cartucho (pode alterar de acordo com o MBC)
}