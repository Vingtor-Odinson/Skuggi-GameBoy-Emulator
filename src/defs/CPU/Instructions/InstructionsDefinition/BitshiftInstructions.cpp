#include "CPU/CPU.hpp"
#include "enum/FlagsEnum.hpp"

#define C FlagsEnum::C

namespace Instructions {

    void rla (const InstructionParameters& params, CPU* cpu) {
        auto valueA = cpu->get8bitRegisterValue(RegistersEnum::A);

        uint8_t msBitA = (valueA & 0b10000000) >> 7;
        uint8_t cBit = cpu->getFlag(C);
        cpu->setFlag(C, msBitA);

        valueA &= 0b01111111;
        valueA = valueA << 1;
        valueA += cBit;
        cpu->set8bitRegister(RegistersEnum::A, valueA);
    }

    void rlca (const InstructionParameters& params, CPU* cpu) {
        auto valueA = cpu->get8bitRegisterValue(RegistersEnum::A);

        uint8_t msBitA = (valueA & 0b10000000) >> 7;
        cpu->setFlag(C, msBitA);

        valueA &= 0b01111111;
        valueA = valueA << 1;
        valueA += msBitA;
        cpu->set8bitRegister(RegistersEnum::A, valueA);
    }

    void rra (const InstructionParameters& params, CPU* cpu) {
        auto valueA = cpu->get8bitRegisterValue(RegistersEnum::A);

        uint8_t cBit = cpu->getFlag(C) << 7;
        cpu->setFlag(C, valueA & 0x01);

        valueA &= 0b11111110;
        valueA = valueA >> 1;
        valueA += cBit;
        cpu->set8bitRegister(RegistersEnum::A, valueA);
    }

    void rrca (const InstructionParameters& params, CPU* cpu) {
        auto valueA = cpu->get8bitRegisterValue(RegistersEnum::A);

        uint8_t msBit = valueA & 0x01;
        uint8_t cBit = msBit << 7;
        cpu->setFlag(C, msBit);

        valueA &= 0b11111110;
        valueA = valueA >> 1;
        valueA += cBit;
        cpu->set8bitRegister(RegistersEnum::A, valueA);
    }
}