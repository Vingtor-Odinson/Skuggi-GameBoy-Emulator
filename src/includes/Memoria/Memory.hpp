#pragma once

#include <stdint.h>
#include <Memoria/BANK00.hpp>
#include <Memoria/BANKNN.hpp>
#include <Memoria/VRAM.hpp>
#include "CPU/Device.hpp"
#include "CPU/Bus.hpp"

class CPU;

class Memory : public Device
{   private:
        Bus* bus;
        BANK00* bank00;
        BANKNN* banknn;
        VRAM* vram;

        MemoryPart* GetMemoryPart(uint16_t address);

    public:
        explicit Memory( Bus* bus );
        ~Memory();

        uint8_t read(const uint16_t& address) override;
        void write(const uint16_t& address, const uint8_t& value ) override;
};

