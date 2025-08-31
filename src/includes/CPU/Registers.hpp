#pragma once

#include <stdint.h>
#include <unordered_map>
#include "enum/FlagsEnum.hpp"
#include "enum/RegistersEnum.hpp"

class Registers
{
    private:
        std::unordered_map<FlagsEnum, uint8_t> masks;

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


    public:

        Registers();

        void setFlag(FlagsEnum, bool);
        bool getFlag(FlagsEnum);

        uint8_t* get8bitRegister(const RegistersEnum& reg);
        uint16_t* get16bitRegister(const RegistersEnum& reg);
};
