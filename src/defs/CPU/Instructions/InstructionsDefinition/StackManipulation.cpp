#include "CPU/CPU.hpp"
#include "enum/FlagsEnum.hpp"

namespace Instructions {
    void push(const InstructionParameters& param, CPU* cpu) {
        if(auto regPtr = cpu->get16bitRegister(param.AimedReg)) {
            uint8_t msb = (*regPtr & 0xFF00) >> 8;
            uint8_t lsb = *regPtr & 0x00FF;
            cpu->pushToStack(msb);
            cpu->pushToStack(lsb);
        }
    }

    void pop(const InstructionParameters& param, CPU* cpu) {
        if(auto regPtr = cpu->get16bitRegister(param.AimedReg)) {
            uint8_t lsb = cpu->popStack();
            uint8_t msb = cpu->popStack();
            *regPtr = (msb << 8) + lsb;
        }
    }
}