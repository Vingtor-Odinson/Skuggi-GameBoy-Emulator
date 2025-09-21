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

    void rra (const InstructionParameters& params, CPU* cpu) {
        auto valueA = cpu->get8bitRegisterValue(RegistersEnum::A);

        uint8_t cBit = cpu->getFlag(C) << 7;
        cpu->setFlag(C, valueA & 0x01);

        valueA &= 0b11111110;
        valueA = valueA >> 1;
        valueA += cBit;
        cpu->set8bitRegister(RegistersEnum::A, valueA);
    }
}