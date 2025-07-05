#pragma once

#include <stdint.h>
#include <unordered_map>
#include <functional>

#include<CPU/Instructions/Instructions.hpp>


using InstructionHandler = std::function<void(InstructionParameters, CPU*)>;

class Memory;

class ROMLoader;

class Registers;

class Operand;

class InstructionResolver;

class CPU
{   

    private:
        std::unordered_map<uint8_t, Instruction> Instructions;
        std::unordered_map<std::string, InstructionHandler> opcodeTable;

    public:
        ROMLoader* romLoader;
        Memory* memory;
        Registers* regs;
        InstructionResolver* instResolver;
        Flags* flags;

        CPU();
        ~CPU();

        uint8_t getOpcode( uint16_t address );
        uint8_t fetchMemory( uint16_t& address ) const;
        Instruction getInstruction( uint8_t opcode );
        void operateByte();
        void instructionLoop();
        void executeInstruction( Instruction Inst );
        void setupCPU();
        void loadOpcodeTable();
};