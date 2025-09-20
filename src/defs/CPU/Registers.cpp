#include "CPU/Registers.hpp"
#include "Exceptions/WrongCpuRegisterUsage.hpp"

Registers::Registers() {
    masks[FlagsEnum::Z] = 7; //0b10000000
    masks[FlagsEnum::N] = 6; //0b01000000
    masks[FlagsEnum::H] = 5; //0b00100000
    masks[FlagsEnum::C] = 4; //0b00010000

    setFlag(FlagsEnum::Z, false);
    setFlag(FlagsEnum::N, false);
    setFlag(FlagsEnum::H, false);
    setFlag(FlagsEnum::C, false);
}

void Registers::setFlag(FlagsEnum flag, bool value) {
    if(value) {
        F |= (1 << masks[flag]);  // 0bffff0000 | 0bznhc0000
    }
    else{
        F &= ~(1 << masks[flag]); // 0bffff0000 & 0b(~z)(~n)(~h)(~c)1111
    }
}

bool Registers::getFlag(FlagsEnum flag) {
    return (F >> masks[flag]) & 0b1;
}

uint8_t *Registers::get8bitRegister(const RegistersEnum &reg) {
    switch (reg) {
        case RegistersEnum::A: return &(A);
        case RegistersEnum::B: return &(B);
        case RegistersEnum::C: return &(C);
        case RegistersEnum::D: return &(D);
        case RegistersEnum::E: return &(E);
        case RegistersEnum::F: return &(F);
        case RegistersEnum::H: return &(H);
        case RegistersEnum::L: return &(L);
        default: return nullptr;
    }
}

uint16_t *Registers::get16bitRegister(const RegistersEnum &reg) {
    switch (reg) {
        case RegistersEnum::AF: return &(AF);
        case RegistersEnum::BC: return &(BC);
        case RegistersEnum::DE: return &(DE);
        case RegistersEnum::HL: return &(HL);
        case RegistersEnum::PC: return &(PC);
        case RegistersEnum::SP: return &(SP);
        default: return nullptr;
    }
}

//todo adicionar tratamento de erro (quanto tiver)

void Registers::set8bitRegister(const RegistersEnum& reg, const uint8_t& value) {
    if( auto ptr = get8bitRegister(reg) ) {
        *ptr = value;
    }
    else {
        throw WrongCpuRegisterUsageException("Expected 8-bit register.", reg);
    }
}

uint8_t Registers::get8bitRegisterValue(const RegistersEnum& reg) {
    if( auto ptr = get8bitRegister(reg) ) {
        return *ptr;
    }

    throw WrongCpuRegisterUsageException("Expected 8-bit register.", reg);
}

void Registers::set16bitRegister(const RegistersEnum& reg, const uint16_t& value) {
    if( auto ptr = get16bitRegister(reg) ) {
        *ptr = value;
    } else {
        throw WrongCpuRegisterUsageException("Expected 16-bit register.", reg);
    }
}

uint16_t Registers::get16bitRegisterValue(const RegistersEnum& reg) {
    if( auto ptr = get16bitRegister(reg) ) {
        return *ptr;
    }

    throw WrongCpuRegisterUsageException("Expected 16-bit register.", reg);
}
