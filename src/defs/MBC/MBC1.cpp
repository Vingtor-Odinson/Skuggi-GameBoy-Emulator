#include "MBC/MBC1.hpp"

void MBC1::write(const uint16_t &address, const uint8_t &value) {

    uint8_t region = address >> 12;

    switch (region) {
        case 0x0:
        case 0x1:
            ramGateReg = value;
            break;
        case 0x2:
        case 0x3:
            bankNumber1 = (value != 0) ? value : 0x1;
            break;
        case 0x4:
        case 0x5:
            bankNumber2 = value;
            break;
        case 0x6:
        case 0x7:
            bankingMode = value & 1 ? true : false;
            break;
    }
}

uint16_t MBC1::readFixedBank(const uint16_t &address) {
    bankNumber = bankingMode ? (bankNumber2 & bank2Mask) << 5 : 0;
    offset = bankNumber*0x4000;
    return address + offset;
}

uint16_t MBC1::readSwapBank(const uint16_t &address) {
    bankNumber = ((bankNumber2 & bank2Mask) << 5) + (bankNumber1 & bank1Mask);
    offset = bankNumber*0x4000;
    return address + offset;
}