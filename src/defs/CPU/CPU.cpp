#include<CPU/CPU.hpp>
#include<CPU/Registers.hpp>
#include<CPU/Instructions.hpp>
#include<Memoria/Memory.hpp>
#include<ROM/ROMLoader.hpp>

CPU::CPU(){
    memory = new Memory();
    romLoader = new ROMLoader( this );
    instLoader = new InstructionLoader( this );
    regs = new Registers();

    instLoader->LoadInstructions();
}

CPU::~CPU(){
    delete memory;
    delete romLoader;
    delete instLoader;
    delete regs;
}

uint8_t CPU::getOpcode( uint16_t address )
{
    return this->memory->ReadMemory(address);
}


