#include<CPU/CPU.hpp>
#include<CPU/Instructions/InstructionResolver.hpp>
#include "CPU/Instructions/InstructionLoader.hpp"
#include "CPU/Instructions/OpcodeTable.hpp"
#include<CPU/Registers.hpp>
#include<Memoria/Memory.hpp>

CPU::CPU(Bus* bus){
    opTable = OpcodeTable::getInstance();
    this->bus = bus;
    instResolver = new InstructionResolver();
    regs = new Registers();
}

CPU::~CPU(){
    delete instResolver;
    delete regs;
}

uint8_t CPU::fetchMemory() const {
    uint8_t value = bus->read(DeviceEnum::Memory, *get16bitRegister(RegistersEnum::PC));
    *get16bitRegister(RegistersEnum::PC) += 1;
    return value;
}

uint8_t CPU::fetchMemory( uint16_t& address ) const
{
    uint8_t value = bus->read(DeviceEnum::Memory, address);
    address++;
    return value;
}

void CPU::pushToStack(const uint8_t& value) {
    *get16bitRegister(RegistersEnum::SP) -= 1;
    write(this->get16bitRegisterValue(RegistersEnum::SP), value);
}

uint8_t CPU::popStack() {
    uint8_t value = read(this->get16bitRegisterValue(RegistersEnum::SP));
    *get16bitRegister(RegistersEnum::SP) += 1;
    return value;
}

uint8_t CPU::getOpcode( uint16_t address )
{
    return bus->read(DeviceEnum::Memory, address);
}

void CPU::executeInstruction( Instruction Inst )
{
    bool willSetIME = this->shallSetIME;
    std::string mnemonic = Inst.GetMnemonic();
    InstructionParameters* param = new InstructionParameters();

    instResolver->ConfigParams( &Inst, *param );
    opTable->getInstructionImplement(mnemonic)(*param, this);

    if(willSetIME) {
        this->setIME();
        this->shallSetIME = false;
    }

    delete param;
}

void CPU::setupCPU()
{
    *get16bitRegister(RegistersEnum::PC) = 0x00;
}

Instruction CPU::getInstruction(uint8_t opcode) {
    return opTable->getInstruction(opcode);
}

bool CPU::getFlag(const FlagsEnum& flag) const {
    return regs->getFlag(flag);
}

void CPU::setFlag(const FlagsEnum &flag, const bool &value) {
    regs->setFlag(flag, value);
}

uint8_t CPU::read(const uint16_t &addr) const {
    return bus->read(DeviceEnum::Memory, addr);
}

void CPU::write(const uint16_t &addr, const uint8_t &val) {
    bus->write(DeviceEnum::Memory, addr, val);
}

uint8_t* CPU::get8bitRegister(const RegistersEnum& reg) const {
    return regs->get8bitRegister(reg);
}

uint16_t* CPU::get16bitRegister(const RegistersEnum& reg) const {
    return regs->get16bitRegister(reg);
}

void CPU::set8bitRegister(const RegistersEnum &reg, const uint8_t &value) {
    regs->set8bitRegister(reg, value);
}

void CPU::set16bitRegister(const RegistersEnum &reg, const uint16_t &value) {
    regs->set16bitRegister(reg, value);
}

uint8_t CPU::get8bitRegisterValue(const RegistersEnum &reg) const {
    try {
        return regs->get8bitRegisterValue(reg);
    } catch (std::exception ex) {
        throw;
    }
}

uint16_t CPU::get16bitRegisterValue(const RegistersEnum &reg) const {
    return regs->get16bitRegisterValue(reg);
}

