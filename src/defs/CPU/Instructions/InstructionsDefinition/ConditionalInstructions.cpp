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

}