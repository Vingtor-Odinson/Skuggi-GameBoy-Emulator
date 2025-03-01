#include<CPU.hpp>
#include<Memoria/Memory.hpp>

CPU::CPU(){
    memory = new Memory();
}

CPU::~CPU(){
    delete memory;
}