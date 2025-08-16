#pragma once

#include <vector>
#include <stdint.h>
#include <string>
#include "CPU/Device.hpp"

class MBC;

class BANK00;

class BANKNN;

class ROMLoader : public Device
{   
    private:

        MBC* mbc;
        std::string ROMPath;
        std::vector<uint8_t>* ROMData;

    public:
        
        void SetROM(const std::string& Path);

        void LoadROM();

        uint8_t read(const uint16_t& address) override;
        void write(const uint16_t& address, const uint8_t& value) override;
        uint8_t readRom(const uint16_t& add);

        friend class BANK00;
        friend class BANKNN;
};