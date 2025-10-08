#include <stdexcept>

#include "CPU/CPU.hpp"
#include "enum/FlagsEnum.hpp"

#define C FlagsEnum::C

uint8_t getRegByte(const RegistersEnum& reg, CPU* cpu)
{
    if (reg == RegistersEnum::HL)
    {
        const auto addrHL = cpu->get16bitRegisterValue(RegistersEnum::HL);
        return cpu->read(addrHL);
    }
    if (const auto regByte = cpu->get8bitRegisterValue(reg))
    {
        return regByte;
    }

    throw std::runtime_error("Invalid register");
}

void setRegByte(const uint8_t& regByte, const RegistersEnum& reg, CPU* cpu)
{
    if (reg == RegistersEnum::HL)
    {
        const auto addrHL = cpu->get16bitRegisterValue(RegistersEnum::HL);
        cpu->write(addrHL, regByte);
        return;
    }
    try {
        cpu->set8bitRegister(reg, regByte);
    } catch (const std::exception& e) {
        throw std::runtime_error("Invalid register");
    }
}

uint8_t rotateLeft(const RegistersEnum& reg, CPU* cpu)
{
    uint8_t regByte = getRegByte(reg, cpu);

    const uint8_t msBitA = (regByte & 0b10000000) >> 7;
    const uint8_t cBit = cpu->getFlag(C);
    cpu->setFlag(C, msBitA);

    regByte &= 0b01111111;
    regByte = regByte << 1;
    regByte += cBit;

    setRegByte(regByte, reg, cpu);
    return regByte;
}

uint8_t rotateLeftNoC(const RegistersEnum& reg, CPU* cpu)
{
    uint8_t regByte = getRegByte(reg, cpu);

    const uint8_t msBitA = (regByte & 0b10000000) >> 7;
    cpu->setFlag(C, msBitA);

    regByte &= 0b01111111;
    regByte = regByte << 1;
    regByte += msBitA;
    setRegByte(regByte, reg, cpu);
    return regByte;
}

uint8_t rotateRight(const RegistersEnum& reg, CPU* cpu)
{
    uint8_t regByte = getRegByte(reg, cpu);

    const uint8_t cBit = cpu->getFlag(C) << 7;
    cpu->setFlag(C, regByte & 0x01);

    regByte &= 0b11111110;
    regByte = regByte >> 1;
    regByte += cBit;
    setRegByte(regByte, reg, cpu);
    return regByte;
}

uint8_t rotateRightNoC(const RegistersEnum& reg, CPU* cpu)
{
    uint8_t regByte = getRegByte(reg, cpu);

    const uint8_t msBit = regByte & 0x01;
    const uint8_t cBit = msBit << 7;
    cpu->setFlag(C, msBit);

    regByte &= 0b11111110;
    regByte = regByte >> 1;
    regByte += cBit;
    setRegByte(regByte, reg, cpu);
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

    void sla(const InstructionParameters& params, CPU* cpu)
    {
        uint8_t regByte = getRegByte(params.AimedReg, cpu);

        cpu->setFlag(C, (regByte & 0x80) >> 7); //Sets the C flag as the ms bit
        regByte = ((regByte & 0x7F) << 1); //Shifts the rest of the byte
        setRegByte(regByte, params.AimedReg, cpu);
        cpu->setFlag(FlagsEnum::Z, regByte == 0x00);
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

    void sra (const InstructionParameters& params, CPU* cpu)
    {
        uint8_t regByte = getRegByte(params.AimedReg, cpu);

        cpu->setFlag(C, (regByte & 0x01));
        regByte = (regByte & 0x80) + ((regByte & 0xFE) >> 1);
        setRegByte(regByte, params.AimedReg, cpu);
        cpu->setFlag(FlagsEnum::Z, regByte == 0x00);
    }

    void srl (const InstructionParameters& params, CPU* cpu)
    {
        uint8_t regByte = getRegByte(params.AimedReg, cpu);

        cpu->setFlag(C, (regByte & 0x01));
        regByte = (regByte & 0xFE) >> 1;
        setRegByte(regByte, params.AimedReg, cpu);
        cpu->setFlag(FlagsEnum::Z, regByte == 0x00);
    }
}