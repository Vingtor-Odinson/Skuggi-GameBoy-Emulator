#include<CPU/CPU.hpp>
#include<CPU/Registers.hpp>
#include<Memoria/Memory.hpp>
#include<ROM/ROMLoader.hpp>

CPU::CPU(){
    memory = new Memory();
    romLoader = new ROMLoader( this );
    instLoader = new InstructionLoader( this );
    regs = new Registers();
    flags = new Flags();

    instLoader->LoadInstructions();
}

CPU::~CPU(){
    delete memory;
    delete romLoader;
    delete instLoader;
    delete regs;
}

uint8_t CPU::fetchMemory( uint16_t address )
{
    uint8_t value = this->memory->ReadMemory(address);
    address++;
    return value;
}

uint8_t CPU::getOpcode( uint16_t address )
{
    return this->memory->ReadMemory(address);
}


