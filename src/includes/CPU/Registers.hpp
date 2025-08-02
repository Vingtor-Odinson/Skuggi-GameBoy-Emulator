#pragma once

#include <stdint.h>
#include <unordered_map>
#include "enum/FlagsEnum.hpp"

class Registers
{
    private:
        std::unordered_map<FlagsEnum, uint8_t> masks;

    public:

        Registers();

        void setFlag( const FlagsEnum&, const bool&);

        bool getFlag( const FlagsEnum& );

        union{
            struct{
                uint8_t F;
                uint8_t A;
            };
            uint16_t AF;
        };
    
        union{
            struct{
                uint8_t C;
                uint8_t B;
            };
            uint16_t BC;
        };
    
        union{
            struct{
                uint8_t E;
                uint8_t D;
            };
            uint16_t DE;
        };
    
        union{
            struct{
                uint8_t L;
                uint8_t H;
            };
            uint16_t HL;
        };
    
        uint16_t SP;
        uint16_t PC;
};
