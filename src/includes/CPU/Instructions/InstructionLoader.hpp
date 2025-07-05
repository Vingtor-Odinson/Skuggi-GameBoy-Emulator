//
// Created by Glauco on 05/07/25.
//

#ifndef GBEMU_INSTRUCTIONLOADER_HPP
#define GBEMU_INSTRUCTIONLOADER_HPP

#include <string>
#include <stdint.h>
#include <unordered_map>
#include <CPU/Instructions/InstructionsParameters.hpp>
#include "enum/RegistersEnum.hpp"
#include "Instructions.hpp"

class InstructionLoader
{
private:
    static const std::string fileLocation;
    static std::unordered_map <std::string, RegistersEnum> registerNameEnumMap;
    static RegistersEnum getRegisterEnum(const std::string& name);

public:

    static std::unordered_map<uint8_t, Instruction> LoadInstructions();

};

#endif //GBEMU_INSTRUCTIONLOADER_HPP
