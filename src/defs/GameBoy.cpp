#include "GameBoy.hpp"
#include "CPU/CPU.hpp"
#include "PPU/PPU.hpp"
#include "Memoria/Memory.hpp"
#include "ROM/ROMLoader.hpp"
#include "CPU/Bus.hpp"

#define MEMORY DeviceEnum::Memory
#define CARTRIDGE DeviceEnum::Cartridge

GameBoy::GameBoy() {
    bus = new Bus();
    cpu = new CPU(bus);
    ppu = new PPU(bus);
    memory = new Memory(bus);
    romLoader = new ROMLoader(bus);

    bus->addDevice(MEMORY, memory);
    bus->addDevice(CARTRIDGE, romLoader);

    lineDotCounter = 0;
}

GameBoy::~GameBoy() {
    delete romLoader;
    delete memory;
    delete cpu;
    delete bus;
}

void GameBoy::setRom(const std::string &path) const {
    romLoader->SetROM(path);
}

void GameBoy::loadRom() const {
    romLoader->LoadROM();
}

uint8_t GameBoy::read(const uint16_t &addr) const {
    return bus->read(DeviceEnum::Memory, addr);
}

void GameBoy::step()
{
    uint8_t mCicles = cpu->step();
    lineDotCounter += mCicles;

    ppu->step(mCicles);
    //dma.step(mCicles);
    //apu.step(mCicles);
}
