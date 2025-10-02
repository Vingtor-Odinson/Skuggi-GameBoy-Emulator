#include <stdexcept>

#include "CPU/Instructions/OpcodeTable.hpp"
#include "CPU/Instructions/InstructionLoader.hpp"

OpcodeTable* OpcodeTable::instance = nullptr;

OpcodeTable* OpcodeTable::getInstance()
{
    if (instance == nullptr)
    {
        instance = new OpcodeTable();
    }
    return instance;
}

OpcodeTable::OpcodeTable()
{
    Instructions = InstructionLoader::loadInstructions();
    CbInstructions = InstructionLoader::loadCbInstructions();
    loadOpcodeTable();
}


InstructionHandler OpcodeTable::getInstructionImplement(const std::string& mnemonic)
{
    const auto it = opcodeTable.find(mnemonic);
    if (it == opcodeTable.end())
    {
        throw std::runtime_error("The specified Instruction: [" + mnemonic + "] is not implemented.");
    }
    return it->second;
}

Instruction OpcodeTable::getCbInstruction(const uint8_t& opcode)
{
    const auto it = CbInstructions.find(opcode);
    if (it == CbInstructions.end())
    {
        throw std::runtime_error("Unknown Instruction.");
    }
    return it->second;
}

Instruction OpcodeTable::getInstruction(const uint8_t& opcode)
{
    const auto it = Instructions.find(opcode);
    if (it == Instructions.end())
    {
        throw std::runtime_error("Unknown Instruction.");
    }
    return it->second;
}

void OpcodeTable::loadOpcodeTable() {
    opcodeTable["NOP"] = Instructions::nop;
    opcodeTable["INC"] = Instructions::inc;
    opcodeTable["DEC"] = Instructions::dec;
    opcodeTable["SUB"] = Instructions::sub;
    opcodeTable["SBC"] = Instructions::sbc;
    opcodeTable["CP"] = Instructions::cp;
    opcodeTable["CPL"] = Instructions::cpl;
    opcodeTable["LD"]  = Instructions::ld;
    opcodeTable["ADC"] = Instructions::adc;
    opcodeTable["ADD"] = Instructions::add;
    opcodeTable["DAA"] = Instructions::daa;
    opcodeTable["XOR"] = Instructions::xorInst;
    opcodeTable["OR"] = Instructions::orInst;
    opcodeTable["AND"] = Instructions::andInst;
    opcodeTable["CALL"] = Instructions::call;
    opcodeTable["JP"] = Instructions::jp;
    opcodeTable["JR"] = Instructions::jr;
    opcodeTable["CCF"] = Instructions::ccf;
    opcodeTable["SCF"] = Instructions::scf;
    opcodeTable["RLA"] = Instructions::rla;
    opcodeTable["RL"] = Instructions::rl;
    opcodeTable["RRA"] = Instructions::rra;
    opcodeTable["RR"] = Instructions::rr;
    opcodeTable["RLCA"] = Instructions::rlca;
    opcodeTable["RLC"] = Instructions::rlc;
    opcodeTable["RRCA"] = Instructions::rrca;
    opcodeTable["RRC"] = Instructions::rrc;
    opcodeTable["DI"] = Instructions::di;
    opcodeTable["EI"] = Instructions::ei;
    opcodeTable["PUSH"] = Instructions::push;
    opcodeTable["POP"] = Instructions::pop;
    opcodeTable["RET"] = Instructions::ret;
    opcodeTable["RETI"] = Instructions::reti;
    opcodeTable["RST"] = Instructions::rst;
    opcodeTable["HALT"] = Instructions::halt;
}