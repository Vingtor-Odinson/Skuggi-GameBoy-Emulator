#include<CPU/CPU.hpp>
#include<CPU/Instructions/InstructionResolver.hpp>
#include "CPU/Instructions/InstructionLoader.hpp"
#include<CPU/Registers.hpp>
#include<Memoria/Memory.hpp>
#include<ROM/ROMLoader.hpp>

CPU::CPU(Bus* bus){
    Instructions = InstructionLoader::LoadInstructions();
    loadOpcodeTable();

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
    write(*this->get16bitRegister(RegistersEnum::SP), value);
}

uint8_t CPU::getOpcode( uint16_t address )
{
    return bus->read(DeviceEnum::Memory, address);
}

void CPU::executeInstruction( Instruction Inst )
{   
    std::string mnemonic = Inst.GetMnemonic();
    InstructionParameters* param = new InstructionParameters();

    instResolver->ConfigParams( &Inst, *param );
    opcodeTable[mnemonic](*param, this);

    delete param;
}

void CPU::setupCPU()
{
    *get16bitRegister(RegistersEnum::PC) = 0x00;
}

Instruction CPU::getInstruction(uint8_t opcode) {
    return Instructions[opcode];
}

void CPU::loadOpcodeTable() {
    opcodeTable["NOP"] = Instructions::nop;
    opcodeTable["INC"] = Instructions::inc;
    opcodeTable["DEC"] = Instructions::dec;
    opcodeTable["SUB"] = Instructions::sub;
    opcodeTable["SBC"] = Instructions::sbc;
    opcodeTable["CP"] = Instructions::cp;
    opcodeTable["CPL"] = Instructions::cpl;
    opcodeTable["LD"]  = Instructions::ld;
    opcodeTable["ADC"] = Instructions::adc;
    opcodeTable["ADD"] = Instructions::add;

    opcodeTable["OR"] = Instructions::orInst;
    opcodeTable["AND"] = Instructions::andInst;

    opcodeTable["CALL"] = Instructions::call;
    opcodeTable["JP"] = Instructions::jp;
    opcodeTable["JR"] = Instructions::jr;

    opcodeTable["CCF"] = Instructions::ccf;
    opcodeTable["SCF"] = Instructions::scf;
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

