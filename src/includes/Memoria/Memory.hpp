#pragma once

#include <stdint.h>
#include <Memoria/BANK00.hpp>
#include <Memoria/BANKNN.hpp>
#include <Memoria/VRAM.hpp>
#include "CPU/Device.hpp"
#include "CPU/Bus.hpp"

class CPU;

class Memory : public Device
{   
    public:

        Bus* bus;
        BANK00* bank00;
        BANKNN* banknn;
        VRAM* vram;
    
        explicit Memory( Bus* bus );
        ~Memory();

        static uint8_t GetMemoryCategory( uint16_t address );
        uint8_t read(const uint16_t& address) override;
        void write(const uint16_t& address, const uint8_t& value ) override;
        MemoryPart* GetMemoryPart(uint16_t address);
};

