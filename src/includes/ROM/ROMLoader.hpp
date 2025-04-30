#pragma once

#include <vector>
#include <stdint.h>
#include <string>

class CPU;

class BANK00;

class BANKNN;

class ROMLoader
{   
    private:
        CPU* cpu;
        std::string ROMPath;
        std::vector<uint8_t>* ROMData;

    public:
        ROMLoader( CPU* cpuRef );
        
        void SetROM( std::string Path );

        void LoadROM();

        uint8_t ReadROM( uint16_t address );

        friend class BANK00;
        friend class BANKNN;
};