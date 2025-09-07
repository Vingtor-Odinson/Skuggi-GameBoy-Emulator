#include<CPU/CPU.hpp>
#include<CPU/Instructions/InstructionResolver.hpp>
#include "CPU/Instructions/InstructionLoader.hpp"
#include<CPU/Registers.hpp>
#include<Memoria/Memory.hpp>
#include<ROM/ROMLoader.hpp>

CPU::CPU(){
    Instructions = InstructionLoader::LoadInstructions();
    loadOpcodeTable();

    bus = new Bus();
    memory = new Memory( bus );
    romLoader = new ROMLoader();
    instResolver = new InstructionResolver();
    regs = new Registers();

    bus->addDevice(DeviceEnum::Memory, memory);
    bus->addDevice(DeviceEnum::Cartridge, romLoader);
}

CPU::~CPU(){
    delete bus;
    delete memory;
    delete romLoader;
    delete instResolver;
    delete regs;
}

uint8_t CPU::fetchMemory() const {
    uint8_t value = bus->read(DeviceEnum::Memory, *get16bitRegister(RegistersEnum::PC));//this->memory->read(this->regs->PC);
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
    opcodeTable["LD"]  = Instructions::ld;
    opcodeTable["ADC"] = Instructions::adc;
    opcodeTable["ADD"] = Instructions::add;

    opcodeTable["OR"] = Instructions::orInst;
    opcodeTable["AND"] = Instructions::andInst;

    opcodeTable["CALL"] = Instructions::call;
    opcodeTable["JP"] = Instructions::jp;
    opcodeTable["JR"] = Instructions::jr;
}

bool CPU::getFlag(const FlagsEnum& flag) const {
    return regs->getFlag(flag);
}

void CPU::setFlag(const FlagsEnum &flag, const bool &value) {
    regs->setFlag(flag, value);
}

void CPU::setROM(const std::string &Path) const {
    romLoader->SetROM(Path);
}

void CPU::loadROM() const {
    romLoader->LoadROM();
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

