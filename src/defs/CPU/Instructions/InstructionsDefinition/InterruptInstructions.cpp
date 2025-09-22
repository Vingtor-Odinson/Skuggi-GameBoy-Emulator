#include "CPU/CPU.hpp"
#include "enum/FlagsEnum.hpp"

namespace Instructions {
    void di(const InstructionParameters& param, CPU* cpu) {
        cpu->disableIME();
    }

    void ei(const InstructionParameters& param, CPU* cpu) {
        cpu->shallSetIME = true;
    }
}
