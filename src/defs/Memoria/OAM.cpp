#include<Memoria/OAM.hpp>
#include <stdexcept>

OAM::OAM() {
    memory.fill(0);
}

void OAM::write( uint16_t address, uint8_t value )
{
    //This address is coming from the memory and has a offset, that's the reason behind the "minus" operation here
    if( address >= memoryOffset && address < (memoryOffset + memorySize) ) {
        memory[address - memoryOffset] = value;
    }
    else {
        throw std::out_of_range("Foi tentado acessar memória fora da região da OAM.");
    }

}

uint8_t OAM::read(uint16_t address)
{   
    //This address is coming from the memory and has a offset, that's the reason behind the "minus" operation here
    if( address < memoryOffset || address >= (memoryOffset + memorySize) ) {
        throw std::out_of_range("Foi tentado acessar memória fora da região da OAM.");
    }

    return memory[address - memoryOffset];
}