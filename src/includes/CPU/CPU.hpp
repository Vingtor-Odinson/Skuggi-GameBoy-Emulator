#pragma once

#include <stdint.h>
#include <unordered_map>

#include<CPU/Instructions.hpp>
#include<CPU/InstructionResolver.hpp>

using InstructionHandler = std::function<void(InstructionParameters, CPU*)>;

class Memory;

class ROMLoader;

class InstructionLoader;

class Registers;

class Instruction;

class Operand;

class CPU
{   

    private:
        std::unordered_map<uint8_t, Instruction> Instructions;
        std::unordered_map<std::string, InstructionHandler> InstructionMap;

    public:
        ROMLoader* romLoader;
        Memory* memory;
        Registers* regs;
        InstructionLoader* instLoader;
        Flags* flags;

        CPU();
        ~CPU();

        uint8_t getOpcode( uint16_t address );
        uint8_t fetchMemory( uint16_t address );
        void operateByte();

        friend class InstructionLoader;
};