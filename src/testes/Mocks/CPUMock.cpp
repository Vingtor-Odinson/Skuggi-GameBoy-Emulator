#include "CPUMock.hpp"
#include "CPU/CPU.hpp"
#include "CPU/Bus.hpp"
#include "Memoria/Memory.hpp"
#include "ROM/ROMLoader.hpp"

CPUMock::CPUMock() {
    bus = new Bus();
    cpu = new CPU(bus);
    memory = new Memory(bus);
    romLoader = new ROMLoader(bus);

    bus->addDevice(DeviceEnum::Memory, memory);
    bus->addDevice(DeviceEnum::Cartridge, romLoader);
}

CPU* CPUMock::getMockedCPU() {
    return cpu;
}
