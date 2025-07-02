#pragma once

#include <stdint.h>
#include <unordered_map>
#include <functional>

#include<CPU/Instructions/Instructions.hpp>


using InstructionHandler = std::function<void(InstructionParameters, CPU*)>;

class Memory;

class ROMLoader;

class InstructionLoader;

class Registers;

class Operand;

class InstructionResolver;

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

        friend class InstructionLoader; //Para que a classe possa alterar o mapa Instructions
};