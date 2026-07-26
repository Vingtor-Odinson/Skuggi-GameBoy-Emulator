#pragma once

#include <stdexcept>
#include <unordered_map>
#include "enum/RegistersEnum.hpp"
#include "enum/OperatorMnemonicEnum.hpp"

class OpMnemonicToNumber{
private:
    static inline std::unordered_map<OperatorMnemonicEnum, uint8_t> mnemonicToRegMap = {
        {OperatorMnemonicEnum::b0, 0x00},
        {OperatorMnemonicEnum::b1, 0x01},
        {OperatorMnemonicEnum::b2, 0x02},
        {OperatorMnemonicEnum::b3, 0x03},
        {OperatorMnemonicEnum::b4, 0x04},
        {OperatorMnemonicEnum::b5, 0x05},
        {OperatorMnemonicEnum::b6, 0x06},
        {OperatorMnemonicEnum::b7, 0x07},
    };

public:
    static uint8_t convert(const OperatorMnemonicEnum& mnemonic) {
        auto it = mnemonicToRegMap.find(mnemonic);
        if(it != mnemonicToRegMap.end()) {
            return it->second;
        }
        throw std::invalid_argument("Invalid OperatorMnemonicEnum");
    }
};

