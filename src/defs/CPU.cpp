#include<CPU.hpp>
#include<Memoria/Memory.hpp>
#include<ROM/ROMLoader.hpp>

CPU::CPU(){
    memory = new Memory();
    romLoader = new ROMLoader( this );
}

CPU::~CPU(){
    delete memory;
    delete romLoader;
}