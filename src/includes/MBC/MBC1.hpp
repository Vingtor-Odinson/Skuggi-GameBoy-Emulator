#ifndef SKUGGI_MBC1_HPP
#define SKUGGI_MBC1_HPP

#include "MBC/MBC.hpp"

class MBC1 : public MBC {

    uint8_t ramGateMask = 0b1010;
    uint8_t bank1Mask = 0b00011111;
    uint8_t bank2Mask = 0b11;
    uint8_t bankNumber;
    uint16_t offset;

public:
    uint16_t readFixedBank( const uint16_t& address) override;
    uint16_t readSwapBank( const uint16_t& address) override;
    void write(const uint16_t& address, const uint8_t& value) override;
};

#endif //SKUGGI_MBC1_HPP
