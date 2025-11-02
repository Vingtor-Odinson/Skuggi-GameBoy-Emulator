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

uint8_t Bus::read(const uint16_t &address) {
    /***
     *Default method reads from memory
     */

    auto memoryPtr = devices.find(DeviceEnum::Memory);

    if(memoryPtr == devices.end()) {
        throw std::runtime_error("It was not possible to find a memory device." );
    }

    return memoryPtr->second->read(address);
}

void Bus::write(const uint16_t &address, const uint8_t &value) {
    /***
    *Default method writes to memory
    */

    auto memoryPtr = devices.find(DeviceEnum::Memory);

    if(memoryPtr == devices.end()) {
        throw std::runtime_error("Tried to access a undefined Device." );
    }

    return memoryPtr->second->write(address, value);
}