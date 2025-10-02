#pragma once

#include <cstdint>
#include <unordered_map>
#include <functional>

#include "CPU/Instructions/Instructions.hpp"

using InstructionHandler = std::function<void(InstructionParameters, CPU*)>;

class OpcodeTable
{
private:
    OpcodeTable();
    static OpcodeTable* instance;
    std::unordered_map<uint8_t, Instruction> Instructions;
    std::unordered_map<uint8_t, Instruction> CbInstructions;
    std::unordered_map<std::string, InstructionHandler> opcodeTable;

public:
    static OpcodeTable* getInstance();
    Instruction getInstruction(const uint8_t& opcode);
    Instruction getCbInstruction(const uint8_t& opcode);
    InstructionHandler getInstructionImplement(const std::string& mnemonic);

private:
    void loadOpcodeTable();
};
