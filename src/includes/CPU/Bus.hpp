#ifndef SKUGGI_BUS_HPP
#define SKUGGI_BUS_HPP

#include <unordered_map>
#include <stdint.h>
#include "enum/DeviceEnum.hpp"

class Device;

class Bus {
    std::unordered_map<DeviceEnum, Device*> devices;

public:
    void addDevice(const DeviceEnum&, Device*);
    void write(const uint16_t&, const uint8_t&);
    uint8_t read(const uint16_t&);
    void write(const DeviceEnum& device, const uint16_t&, const uint8_t&);
    uint8_t read(const DeviceEnum& device, const uint16_t&);
};

#endif //SKUGGI_BUS_HPP
