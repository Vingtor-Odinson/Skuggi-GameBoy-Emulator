#pragma once

#include <vector>
#include <stdint.h>
#include <string>

class MBC;

class BANK00;

class BANKNN;

class ROMLoader
{   
    private:

        MBC* mbc;
        std::string ROMPath;
        std::vector<uint8_t>* ROMData;

    public:
        
        void SetROM(const std::string& Path);

        void LoadROM();

        uint8_t readFixedBank(const uint16_t& address);
        uint8_t readSwapBank(const uint16_t& address);
        void write(const uint16_t& address, const uint8_t& value);
        uint8_t readRom(const uint16_t& add);

        friend class BANK00;
        friend class BANKNN;
};