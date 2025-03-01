#include<CPU.hpp>
#include<Registers/Registers.hpp>
#include<Memoria/Memory.hpp>
#include<ROM/ROMLoader.hpp>

CPU::CPU(){
    memory = new Memory();
    romLoader = new ROMLoader( this );
    regs = new Registers();
}

CPU::~CPU(){
    delete memory;
    delete romLoader;
}
