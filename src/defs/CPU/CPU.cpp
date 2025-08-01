#include<CPU/CPU.hpp>
#include<CPU/Instructions/InstructionResolver.hpp>
#include "CPU/Instructions/InstructionLoader.hpp"
#include<CPU/Registers.hpp>
#include<Memoria/Memory.hpp>
#include<ROM/ROMLoader.hpp>

CPU::CPU(){
    Instructions = InstructionLoader::LoadInstructions();
    loadOpcodeTable();

    memory = new Memory( this );
    romLoader = new ROMLoader( this );
    instResolver = new InstructionResolver();
    regs = new Registers();
}

CPU::~CPU(){
    delete memory;
    delete romLoader;
    delete instResolver;
    delete regs;
}

uint8_t CPU::fetchMemory() const {
    uint8_t value = this->memory->ReadMemory(this->regs->PC);
    this->regs->PC++;
    return value;
}

uint8_t CPU::fetchMemory( uint16_t& address ) const
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
    opcodeTable[mnemonic](*param, this);

    delete param;
}

void CPU::setupCPU()
{
    this->regs->PC = 0x00;
}

void CPU::instructionLoop()
{
    uint8_t opCode = fetchMemory( this->regs->PC );
    Instruction inst = Instructions[opCode];
    executeInstruction( inst );
}

Instruction CPU::getInstruction(uint8_t opcode) {
    return Instructions[opcode];
}

void CPU::loadOpcodeTable() {
    opcodeTable["NOP"] = Instructions::nop;
    opcodeTable["INC"] = Instructions::inc;
    opcodeTable["DEC"] = Instructions::dec;
    opcodeTable["LD"]  = Instructions::ld;
    opcodeTable["OR"] = Instructions::orInst;
}

