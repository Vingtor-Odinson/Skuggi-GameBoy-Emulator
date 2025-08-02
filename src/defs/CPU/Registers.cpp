#include "CPU/Registers.hpp"

Registers::Registers() {
    masks[FlagsEnum::Z] = 7; //0b10000000
    masks[FlagsEnum::N] = 6; //0b01000000
    masks[FlagsEnum::H] = 5; //0b00100000
    masks[FlagsEnum::C] = 4; //0b00010000
}

void Registers::setFlag(const FlagsEnum& flag, const bool& value) {
    if(value) {
        F |= (1 << masks[flag]);  // 0bffff0000 | 0bznhc0000
    }
    else{
        F &= ~(1 << masks[flag]); // 0bffff0000 & 0b(~z)(~n)(~h)(~c)1111
    }
}

bool Registers::getFlag(const FlagsEnum& flag) {
    return (F >> masks[flag]) & 0b1;
}