#pragma once

#include <cstdint>
#include <unordered_map>
#include <functional>

#include "CPU/Instructions/Instructions.hpp"
#include "Bus.hpp"
#include "CPU/Registers.hpp"
#include "enum/RegistersEnum.hpp"
#include "enum/CPUStates.hpp"

using InstructionHandler = std::function<void(InstructionParameters, CPU*)>;

class OpcodeTable;

class Registers;

class InstructionResolver;

class CPU
{
private:
    std::unordered_map<uint8_t, Instruction> Instructions;
    std::unordered_map<std::string, InstructionHandler> opcodeTable;
    OpcodeTable* opTable;

    Registers* regs;
    InstructionResolver* instResolver;

    Bus* bus;
    bool IME;

    void setupCPU();
    void loadOpcodeTable();

public:
    CPUStates cpuState;
    explicit CPU(Bus* bus);
    ~CPU();

    uint8_t getOpcode(uint16_t address);
    uint8_t fetchMemory() const;
    uint8_t fetchMemory(uint16_t& address) const;
    void pushToStack(const uint8_t& value);
    uint8_t popStack();

    Instruction getInstruction(uint8_t opcode);
    void executeInstruction(Instruction Inst);

    void setFlag(const FlagsEnum&, const bool&);
    bool getFlag(const FlagsEnum&) const;

    uint8_t read(const uint16_t& addr) const;
    void write(const uint16_t& addr, const uint8_t& val);

    uint8_t* get8bitRegister(const RegistersEnum& reg) const;
    uint16_t* get16bitRegister(const RegistersEnum& reg) const;

    void set8bitRegister(const RegistersEnum&, const uint8_t&);
    void set16bitRegister(const RegistersEnum&, const uint16_t&);

    uint8_t get8bitRegisterValue(const RegistersEnum& reg) const;
    uint16_t get16bitRegisterValue(const RegistersEnum& reg) const;


    bool shallSetIME;
    void disableIME() { IME = false; };
    void setIME() { IME = true; };
    bool getIME() { return IME; };
};
