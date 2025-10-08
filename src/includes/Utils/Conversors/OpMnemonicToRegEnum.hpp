#ifndef SKUGGI_OPMNEMONICTOREGENUM_HPP
#define SKUGGI_OPMNEMONICTOREGENUM_HPP

#include <unordered_map>
#include "enum/RegistersEnum.hpp"
#include "enum/OperatorMnemonicEnum.hpp"

class OpMnemonicToReg{
private:
    static inline std::unordered_map<OperatorMnemonicEnum, RegistersEnum> mnemonicToRegMap = {
            {OperatorMnemonicEnum::A, RegistersEnum::A},
            {OperatorMnemonicEnum::B, RegistersEnum::B},
            {OperatorMnemonicEnum::C, RegistersEnum::C},
            {OperatorMnemonicEnum::D, RegistersEnum::D},
            {OperatorMnemonicEnum::E, RegistersEnum::E},
            {OperatorMnemonicEnum::F, RegistersEnum::F},
            {OperatorMnemonicEnum::H, RegistersEnum::H},
            {OperatorMnemonicEnum::L, RegistersEnum::L},
            {OperatorMnemonicEnum::AF, RegistersEnum::AF},
            {OperatorMnemonicEnum::BC, RegistersEnum::BC},
            {OperatorMnemonicEnum::DE, RegistersEnum::DE},
            {OperatorMnemonicEnum::HL, RegistersEnum::HL},
            {OperatorMnemonicEnum::SP, RegistersEnum::SP},
            {OperatorMnemonicEnum::PC, RegistersEnum::PC}
    };

public:
    static RegistersEnum convert(const OperatorMnemonicEnum& mnemonic) {
        auto it = mnemonicToRegMap.find(mnemonic);
        if(it != mnemonicToRegMap.end()) {
            return it->second;
        }
        return RegistersEnum::INVALID;
    }
};

#endif //SKUGGI_OPMNEMONICTOREGENUM_HPP
