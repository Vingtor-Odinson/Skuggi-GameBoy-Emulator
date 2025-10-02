//
// Created by Glauco on 05/07/25.
//

#ifndef GBEMU_INSTRUCTIONLOADER_HPP
#define GBEMU_INSTRUCTIONLOADER_HPP

#include <string>
#include <stdint.h>
#include <unordered_map>
#include <CPU/Instructions/InstructionsParameters.hpp>
#include "enum/OperatorMnemonicEnum.hpp"
#include "Instructions.hpp"

class InstructionLoader
{
private:
    static const std::string fileLocation;
    static std::unordered_map <std::string, OperatorMnemonicEnum> registerNameEnumMap;
    static OperatorMnemonicEnum getRegisterEnum(const std::string& name);

public:

    static std::unordered_map<uint8_t, Instruction> loadInstructions();
    static std::unordered_map<uint8_t, Instruction> loadCbInstructions();

private:
    static std::unordered_map<uint8_t, Instruction> parseInstructionsFile(const std::string& prefix);
};

#endif //GBEMU_INSTRUCTIONLOADER_HPP
