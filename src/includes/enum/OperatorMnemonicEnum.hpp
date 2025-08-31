#ifndef GBEMU_REGISTERSENUM_H
#define GBEMU_REGISTERSENUM_H

enum class OperatorMnemonicEnum { //Todo: change this name since it does not represent only the registers anymore and seems to be more related to the op mnemonic
    A,
    B,
    C,
    D,
    E,
    F,
    H,
    L,
    AF,
    BC,
    DE,
    HL,
    SP,
    PC,
    n8,
    e8,
    n16,
    a16,
    NC,
    Z,
    NZ,
    INVALID
};

#endif //GBEMU_REGISTERSENUM_H
