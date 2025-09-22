#ifndef SKUGGI_IOREGISTERS_HPP
#define SKUGGI_IOREGISTERS_HPP

#include <array>
#include "Memoria/MemoryParts.hpp"


/**
 *
 * 0xFF00 | Joypad input
 * 0xFF01 - 0xFF02 | Serial transfer
 * 0xFF04 - 0xFF07 | Timer and divider
 * 0xFF0F | Interrupts
 * 0xFF10 - 0xFF26 | Audio
 * 0xFF30 - 0xFF3F | Wave pattern
 * 0xFF40 - 0xFF4B | LCD
 * 0xFF4C - 0xFF4D | Key 0 and Key 1
 * 0xFF4F | VRAM Bank select
 * 0xFF50 | Boot ROM mapping control
 * 0xFF51 - 0xFF55 | VRAM DMA
 * 0xFF56 | IR Port
 * 0xFF68 - 0xFF6B | BG / OBJ Palletes
 * 0xFF6C Object priority mode
 * 0xFF70 WRAM Bank select
 *
 */


class Bus;

class IORegisters : public MemoryPart //Implementação da primeira parte da memória: O BANK00 que conterá o HEADER do jogo
{
private:
    uint16_t offset = 0xFF00;
    std::array<uint8_t, 0x7F> registers;

public:

    uint8_t Read(uint16_t address) override;
    void Write(uint16_t address, uint8_t value) override;
};
#endif //SKUGGI_IOREGISTERS_HPP
