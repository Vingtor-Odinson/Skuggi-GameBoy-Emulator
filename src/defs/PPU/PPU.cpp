#include "CPU/Bus.hpp"
#include "PPU/PPU.hpp"

PPU::PPU(Bus* bus)
{
    this->bus = bus;
}

void PPU::step(const uint8_t& cyc)
{

}