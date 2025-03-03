#pragma once

#include <stdint.h>
#include <unordered_map>

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

    public:
        ROMLoader* romLoader;
        Memory* memory;
        Registers* regs;
        InstructionLoader* instLoader;

        CPU();
        ~CPU();

        uint8_t getOpcode( uint16_t address );
        void operateByte();

        friend class InstructionLoader;
};