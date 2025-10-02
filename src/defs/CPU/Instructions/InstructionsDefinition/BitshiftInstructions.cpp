#include "CPU/CPU.hpp"
#include "enum/FlagsEnum.hpp"

#define C FlagsEnum::C

uint8_t rotateLeft(const RegistersEnum& reg, CPU* cpu)
{
    auto regByte = cpu->get8bitRegisterValue(reg);

    const uint8_t msBitA = (regByte & 0b10000000) >> 7;
    const uint8_t cBit = cpu->getFlag(C);
    cpu->setFlag(C, msBitA);

    regByte &= 0b01111111;
    regByte = regByte << 1;
    regByte += cBit;
    cpu->set8bitRegister(reg, regByte);
    return regByte;
}

uint8_t rotateLeftNoC(const RegistersEnum& reg, CPU* cpu)
{
    auto regByte = cpu->get8bitRegisterValue(reg);

    const uint8_t msBitA = (regByte & 0b10000000) >> 7;
    cpu->setFlag(C, msBitA);

    regByte &= 0b01111111;
    regByte = regByte << 1;
    regByte += msBitA;
    cpu->set8bitRegister(reg, regByte);
    return regByte;
}

uint8_t rotateRight(const RegistersEnum& reg, CPU* cpu)
{
    auto regByte = cpu->get8bitRegisterValue(reg);

    const uint8_t cBit = cpu->getFlag(C) << 7;
    cpu->setFlag(C, regByte & 0x01);

    regByte &= 0b11111110;
    regByte = regByte >> 1;
    regByte += cBit;
    cpu->set8bitRegister(reg, regByte);
    return regByte;
}

uint8_t rotateRightNoC(const RegistersEnum& reg, CPU* cpu)
{
    auto regByte = cpu->get8bitRegisterValue(reg);

    const uint8_t msBit = regByte & 0x01;
    const uint8_t cBit = msBit << 7;
    cpu->setFlag(C, msBit);

    regByte &= 0b11111110;
    regByte = regByte >> 1;
    regByte += cBit;
    cpu->set8bitRegister(reg, regByte);
    return regByte;
}

namespace Instructions {

    void rla (const InstructionParameters& params, CPU* cpu) {
        rotateLeft(RegistersEnum::A, cpu);
    }

    void rl (const InstructionParameters& params, CPU* cpu)
    {
        const uint8_t resultByte = rotateLeft(params.AimedReg, cpu);
        cpu->setFlag(FlagsEnum::Z, resultByte == 0x00);
    }

    void rlca (const InstructionParameters& params, CPU* cpu) {
        rotateLeftNoC(RegistersEnum::A, cpu);
    }

    void rlc (const InstructionParameters& params, CPU* cpu) {
        const uint8_t resultByte = rotateLeftNoC(params.AimedReg, cpu);
        cpu->setFlag(FlagsEnum::Z, resultByte == 0x00);
    }

    void rra (const InstructionParameters& params, CPU* cpu) {
        rotateRight(RegistersEnum::A, cpu);
    }

    void rr (const InstructionParameters& params, CPU* cpu)
    {
        const uint8_t resultByte = rotateRight(params.AimedReg, cpu);
        cpu->setFlag(FlagsEnum::Z, resultByte == 0x00);
    }

    void rrca (const InstructionParameters& params, CPU* cpu) {
        rotateRightNoC(RegistersEnum::A, cpu);
    }

    void rrc (const InstructionParameters& params, CPU* cpu) {
        const uint8_t result = rotateRightNoC(params.AimedReg, cpu);
        cpu->setFlag(FlagsEnum::Z, result == 0x00);
    }
}