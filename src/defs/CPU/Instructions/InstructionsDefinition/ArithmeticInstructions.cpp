#include "CPU/CPU.hpp"
#include "enum/FlagsEnum.hpp"

void checkDecFlags(const uint8_t& orValue, const uint8_t& newValue, CPU* cpu) {
    cpu->setFlag(FlagsEnum::N, true);
    cpu->setFlag(FlagsEnum::Z, newValue == 0x00);

    uint8_t oldLowerPart = orValue & 0x0F;
    uint8_t newLowerPart = newValue & 0x0F;

    cpu->setFlag(FlagsEnum::H, oldLowerPart < newLowerPart);
}

void checkSubFlags(const uint8_t& valueA, const uint8_t& valueB, CPU* cpu) {
    cpu->setFlag(FlagsEnum::C, valueB > valueA);
    checkDecFlags(valueA, valueA - valueB, cpu);
}

namespace Instructions {

    void dec( const InstructionParameters& params, CPU* cpu )
    {
        if ( auto reg16 = cpu->get16bitRegister(params.AimedReg) )
        {
            if(params.AimedReg == RegistersEnum::HL && params.AimedIsAddress) {
                uint8_t orValue = cpu->read(*reg16);
                uint8_t newValue = orValue - 1;

                cpu->write(*reg16, newValue);

                checkDecFlags(orValue, newValue, cpu);
            }
            else {
                (*reg16) -= 1;
            }

        }
        else if ( auto reg = cpu->get8bitRegister(params.AimedReg) )
        {
            uint8_t orValue = *reg;
            uint8_t newValue = orValue - 1;
            (*reg) = newValue;

            checkDecFlags(orValue, newValue, cpu);
        }
    }

    void sub(const InstructionParameters& params, CPU* cpu) {
        if(params.AimedReg == RegistersEnum::A) {
            uint8_t* ptrA = cpu->get8bitRegister(params.AimedReg);
            uint8_t valueA = *ptrA;
            uint8_t valueB;

            if(auto regPtr = cpu->get8bitRegister(params.OriginReg)) {
                valueB = *regPtr;
            }
            else if(params.OriginReg == RegistersEnum::HL && params.OriginIsAddress) {
                uint16_t addrHL = cpu->get16bitRegisterValue(RegistersEnum::HL);
                valueB = cpu->read(addrHL);
            }
            else if(params.OriginIsNextByte) {
                valueB = cpu->fetchMemory();
            }
            else {
                return;
            }

            *ptrA = valueA - valueB;
            checkSubFlags(valueA, valueB, cpu);
        }
    }

}