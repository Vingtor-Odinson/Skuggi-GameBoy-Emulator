#include<Memoria/HRAM.hpp>
#include <stdexcept>

HRAM::HRAM() {
    memory.fill(0);
}

void HRAM::write( uint16_t address, uint8_t value )
{
    //This address is coming from the memory and has a offset, that's the reason behind the "minus" operation here
    if( address >= memoryOffset && address < (memoryOffset + memorySize) ) {
        memory[address - memoryOffset] = value;
    }
    else {
        throw std::out_of_range("Foi tentado acessar memória fora da região da HRAM.");
    }

}

uint8_t HRAM::read(uint16_t address)
{   
    //This address is coming from the memory and has a offset, that's the reason behind the "minus" operation here
    if( address < memoryOffset || address >= (memoryOffset + memorySize) ) {
        throw std::out_of_range("Foi tentado acessar memória fora da região da HRAM.");
    }

    return memory[address - memoryOffset];
}