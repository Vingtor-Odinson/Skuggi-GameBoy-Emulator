#include "CPU/Bus.hpp"
#include "CPU/Device.hpp"
#include <stdexcept>

void Bus::addDevice(const DeviceEnum & device, Device* devicePtr) {
    devices.insert(std::make_pair(device, devicePtr));
}

uint8_t Bus::read(const DeviceEnum &device, const uint16_t &address) {
    auto devicePtr = devices.find(device);

    if(devicePtr == devices.end()) {
        throw std::runtime_error("Tried to access a undefined Device." );
    }

    return devicePtr->second->read(address);
}

void Bus::write(const DeviceEnum &device, const uint16_t &address, const uint8_t &value) {
    auto devicePtr = devices.find(device);

    if(devicePtr == devices.end()) {
        throw std::runtime_error("Tried to access a undefined Device." );
    }

    return devicePtr->second->write(address, value);
}