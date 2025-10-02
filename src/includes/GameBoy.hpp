#ifndef SKUGGI_GAMEBOY_HPP
#define SKUGGI_GAMEBOY_HPP

#include <memory>

class CPU;

class Memory;

class Bus;

class ROMLoader;

class GameBoy {

private:
    //Trocar isso pra smartpointer assim que possível
    CPU* cpu;
    Bus* bus;
    Memory* memory;
    ROMLoader* romLoader;

    uint16_t lineDotCounter;

public:
    GameBoy();
    ~GameBoy();

    void setRom(const std::string &Path) const;
    void loadRom() const;

    void step();

    uint8_t read(const uint16_t&) const;

    [[nodiscard]] CPU* getCPU() const
    {
        return cpu;
    }
};

#endif //SKUGGI_GAMEBOY_HPP
