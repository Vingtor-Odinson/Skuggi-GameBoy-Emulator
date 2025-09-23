#include <CPU/CPU.hpp>
#include <Memoria/Memory.hpp>
#include <CPU/Instructions/Instructions.hpp>
#include <CPU/Registers.hpp>
#include <CPU/Instructions/InstructionResolver.hpp>
#include <nlohmann/json.hpp>
#include "enum/RegistersEnum.hpp"

bool checkFlagsConditions(const OperatorMnemonicEnum& flag, const CPU* cpu) {
    return (flag == OperatorMnemonicEnum::C && cpu->getFlag(FlagsEnum::C)) ||
           (flag == OperatorMnemonicEnum::NC && !cpu->getFlag(FlagsEnum::C)) ||
           (flag == OperatorMnemonicEnum::Z && cpu->getFlag(FlagsEnum::Z)) ||
           (flag == OperatorMnemonicEnum::NZ && !cpu->getFlag(FlagsEnum::Z));
}

namespace Instructions {

    void xorInst(const InstructionParameters& params, CPU* cpu) {
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

            valueA = valueA ^ valueB;
            *ptrA = valueA;

            cpu->setFlag(FlagsEnum::Z, valueA == 0x00);
            cpu->setFlag(FlagsEnum::N, false);
            cpu->setFlag(FlagsEnum::H, false);
            cpu->setFlag(FlagsEnum::C, false);
        }
    }

    void call(const InstructionParameters& param, CPU* cpu) {
        if(checkFlagsConditions(param.firstOpMnemonic, cpu) || (param.firstOpMnemonic == OperatorMnemonicEnum::a16)){

            uint8_t lsb = cpu->fetchMemory(); //least significant byte
            uint8_t msb = cpu->fetchMemory(); //most significant byte
            uint16_t orValue = (msb << 8) | lsb;

            uint8_t PClsb = *cpu->get16bitRegister(RegistersEnum::PC) & 0xFF ;
            uint8_t PCmsb = (*cpu->get16bitRegister(RegistersEnum::PC) & 0xFF00) >> 8;

            cpu->pushToStack(PCmsb);
            cpu->pushToStack(PClsb);

            *cpu->get16bitRegister(RegistersEnum::PC) = orValue; //implicit JP
        }
    }

    void jp(const InstructionParameters& param, CPU* cpu) {
        if(param.AimIsNextBytes || checkFlagsConditions(param.firstOpMnemonic, cpu)) {
            uint8_t lsb = cpu->fetchMemory(); //least significant byte
            uint8_t msb = cpu->fetchMemory(); //most significant byte
            uint16_t orValue = (msb << 8) | lsb;

            *cpu->get16bitRegister(RegistersEnum::PC) = orValue;
        }
        else if(uint16_t* orReg = cpu->get16bitRegister(param.AimedReg) ) {
            *cpu->get16bitRegister(RegistersEnum::PC) = *orReg;
        }
    }

    void jr(const InstructionParameters& param, CPU* cpu) {
        if(checkFlagsConditions(param.firstOpMnemonic, cpu) || (param.firstOpMnemonic == OperatorMnemonicEnum::e8)) {
            int8_t offset = cpu->fetchMemory();
            *cpu->get16bitRegister(RegistersEnum::PC) += offset;
        }
    }

    void ret(const InstructionParameters& param, CPU* cpu) {
        InstructionParameters popParam = InstructionParameters();
        popParam.AimedReg = RegistersEnum::PC;
        pop(popParam, cpu);
    }

    void reti(const InstructionParameters& param, CPU* cpu) {
        ret(param, cpu);
        cpu->setIME();
    }

}