#ifndef SKUGGI_MBC_HPP
#define SKUGGI_MBC_HPP

#include <stdint.h>

class MBC {
protected:
    uint8_t ramGateReg;
    uint8_t bankNumber1;
    uint8_t bankNumber2;
    bool bankingMode;

public:
    virtual uint16_t read(const uint16_t& address ) {return 0x00;};
    virtual void write( const uint16_t& address, const uint8_t& value ) {};
};

#endif //SKUGGI_MBC_HPP
