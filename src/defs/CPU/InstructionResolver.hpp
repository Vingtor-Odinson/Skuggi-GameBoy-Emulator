#pragma once    

#include <CPU/Instructions.hpp>

class InstructionParameters
{
    public:
        uint8_t ArgumentNumber;

        uint8_t Aimed8Byte; 
        uint16_t Aimed16Byte;

        uint8_t Origin8Byte;
        uint16_t Origin16Byte;

        std::string AimedReg;
        std::string OriginReg;

        bool AimedIsAddress;
        bool OriginIsAddress;

        bool AimIsNextByte;
        bool AimIsNextBytes;

        bool OriginIsNextByte;
        bool OriginIsNextBytes;
};

class InstructionResolver
{

    public:

        void ConfigParams(Instruction* inst, InstructionParameters param);
};