#ifndef SKUGGI_PPU_HPP
#define SKUGGI_PPU_HPP
#include <cstdint>

class Bus;

class PPU
{
    private:
        Bus* bus;

    public:
        PPU(Bus* bus);

        void step(const uint8_t& cyc);
};

#endif //SKUGGI_PPU_HPP