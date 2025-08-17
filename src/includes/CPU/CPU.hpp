#pragma once

#include <stdint.h>
#include <unordered_map>
#include <functional>

#include "CPU/Instructions/Instructions.hpp"
#include "Bus.hpp"
#include "CPU/Registers.hpp"

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
        Bus* bus;

    public:
        ROMLoader* romLoader;
        Memory* memory;
        Registers* regs;
        InstructionResolver* instResolver;

        CPU();
        ~CPU();

        uint8_t getOpcode( uint16_t address );
        uint8_t fetchMemory() const;
        uint8_t fetchMemory( uint16_t& address ) const;
        Instruction getInstruction( uint8_t opcode );
        void operateByte();
        void instructionLoop();
        void executeInstruction( Instruction Inst );
        void setupCPU();
        void loadOpcodeTable();
        Bus *getBus() const;

        template<typename T>
        T getRegister(const RegistersEnum& reg);
        //todo: evaluate if the gains from template especialization are relevant and real (other option is using especific functions | maybe greater gain 'cause of compilation optimization)
};