#ifndef SKUGGI_DEVICE_HPP
#define SKUGGI_DEVICE_HPP

#include <stdint.h>

class Device {
public:
    virtual void write(const uint16_t&, const uint8_t&) {};
    virtual uint8_t read(const uint16_t&) {return 0x00;};
};

#endif //SKUGGI_DEVICE_HPP
