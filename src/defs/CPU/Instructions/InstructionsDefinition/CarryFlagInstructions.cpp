#include "CPU/CPU.hpp"
#include "enum/FlagsEnum.hpp"

namespace Instructions {

    void ccf(const InstructionParameters& params, CPU* cpu) {
        cpu->setFlag(FlagsEnum::C, !cpu->getFlag(FlagsEnum::C));
    }

    void scf(const InstructionParameters& params, CPU* cpu) {
        cpu->setFlag(FlagsEnum::C, true);
    }
}