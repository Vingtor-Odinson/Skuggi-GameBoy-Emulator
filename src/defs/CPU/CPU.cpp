#include<CPU/CPU.hpp>
#include<CPU/InstructionResolver.hpp>
#include<CPU/Registers.hpp>
#include<Memoria/Memory.hpp>
#include<ROM/ROMLoader.hpp>

CPU::CPU(){
    memory = new Memory();
    romLoader = new ROMLoader( this );
    instLoader = new InstructionLoader( this );
    instResolver = new InstructionResolver();
    regs = new Registers();
    flags = new Flags();

    instLoader->LoadInstructions();
}

CPU::~CPU(){
    delete memory;
    delete romLoader;
    delete instLoader;
    delete instResolver;
    delete regs;
    delete flags;
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

void CPU::executeInstruction( Instruction Inst )
{   
    std::string mnemonic = Inst.GetMnemonic();
    InstructionParameters* param = new InstructionParameters();

    instResolver->ConfigParams( &Inst, *param );
    InstructionMap[mnemonic]( *param, this);

    delete param;
}

void CPU::instructionLoop()
{
    uint8_t opCode = fetchMemory( this->regs->PC );
    Instruction inst = Instructions[opCode];
    executeInstruction( inst );
}

