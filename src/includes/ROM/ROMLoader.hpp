#pragma once

#include <vector>
#include <stdint.h>
#include <string>

class CPU;

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

        void LoadBANK00();
        
        void LoadBANkNN(unsigned int bankNumber);

};