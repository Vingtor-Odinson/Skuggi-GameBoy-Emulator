#pragma once

#include <string>
#include <stdint.h>
#include "enum/OperatorMnemonicEnum.hpp"
#include "enum/FlagsEnum.hpp"
#include "enum/RegistersEnum.hpp"

class InstructionParameters
{
    public:
        uint8_t ArgumentNumber;

        uint8_t Aimed8Byte; 
        uint16_t Aimed16Byte;

        uint8_t Origin8Byte;
        uint16_t Origin16Byte;

        RegistersEnum AimedReg;
        RegistersEnum OriginReg;

        OperatorMnemonicEnum firstOpMnemonic;
        OperatorMnemonicEnum sndOpMnemonic;

        bool AimedIsAddress;
        bool OriginIsAddress;

        bool AimIsNextByte;
        bool AimIsNextBytes;

        bool OriginIsNextByte;
        bool OriginIsNextBytes;

        bool AimShouldIncrement;
        bool OriginShouldIncrement;

        bool AimShouldDecrement;
        bool OriginShouldDecrement;

        bool AimIsNextByteSigned;
        bool OriginIsNextByteSigned;
};