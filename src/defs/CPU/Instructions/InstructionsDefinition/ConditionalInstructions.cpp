#include <CPU/CPU.hpp>
#include <Memoria/Memory.hpp>
#include <CPU/Instructions/Instructions.hpp>
#include <CPU/Registers.hpp>
#include <CPU/Instructions/InstructionResolver.hpp>
#include <nlohmann/json.hpp>
#include "enum/RegistersEnum.hpp"

namespace Instructions {

    void call(const InstructionParameters& param, CPU* cpu) {
        if(param.OriginIsNextBytes) {
            if((param.firstOpMnemonic == OperatorMnemonicEnum::C && cpu->getFlag(FlagsEnum::C)) ||
                    (param.firstOpMnemonic == OperatorMnemonicEnum::NC && !cpu->getFlag(FlagsEnum::C)) ||
                    (param.firstOpMnemonic == OperatorMnemonicEnum::Z && cpu->getFlag(FlagsEnum::Z)) ||
                    (param.firstOpMnemonic == OperatorMnemonicEnum::NZ && !cpu->getFlag(FlagsEnum::Z)) ||
                    (param.firstOpMnemonic == OperatorMnemonicEnum::INVALID)){

                uint8_t lsb = cpu->fetchMemory(); //least significant byte
                uint8_t msb = cpu->fetchMemory(); //most significant byte
                uint16_t orValue = (msb << 8) | lsb;

                uint8_t PClsb = *cpu->get16bitRegister(RegistersEnum::PC) & 0xFF ;
                uint8_t PCmsb = (*cpu->get16bitRegister(RegistersEnum::PC) & 0xFF00) >> 8;

                cpu->addToStack(PCmsb);
                cpu->addToStack(PClsb);

                *cpu->get16bitRegister(RegistersEnum::PC) = orValue;
            }
        }
    }

}