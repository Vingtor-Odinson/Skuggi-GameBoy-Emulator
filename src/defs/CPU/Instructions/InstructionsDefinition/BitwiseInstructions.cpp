#include "CPU/CPU.hpp"
#include "enum/FlagsEnum.hpp"

namespace Instructions {

    void cpl(const InstructionParameters& param, CPU* cpu) {
        uint8_t valueA = cpu->get8bitRegisterValue(RegistersEnum::A);
        valueA = ~valueA;
        cpu->set8bitRegister(RegistersEnum::A, valueA);

        cpu->setFlag(FlagsEnum::N, true);
        cpu->setFlag(FlagsEnum::H, true);
    }

}