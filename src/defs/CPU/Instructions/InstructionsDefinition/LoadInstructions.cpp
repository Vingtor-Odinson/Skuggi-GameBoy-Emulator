#include <stdexcept>

#include "CPU/CPU.hpp"
#include "Utils/Conversors/OpMnemonicToRegEnum.hpp"

uint8_t get_ldh_byte(const OperatorMnemonicEnum& mnemonic, CPU* cpu)
{
    switch (mnemonic)
    {
    case OperatorMnemonicEnum::A:
        {
            return cpu->get8bitRegisterValue(OpMnemonicToReg::convert(mnemonic));
        }
    case OperatorMnemonicEnum::C:
        {
            uint8_t lsbAddr = cpu->get8bitRegisterValue(OpMnemonicToReg::convert(mnemonic));
            return cpu->read(0xFF00 + lsbAddr);
        }
    case OperatorMnemonicEnum::n8:
        {
            uint8_t lsbAddr = cpu->fetchMemory();
            return cpu->read(0xFF00 + lsbAddr);
        }
    default:
        {
            throw std::invalid_argument("Invalid mnemonic for LDH");
        }
    }
}

void set_ldh_value(const uint8_t& value, const OperatorMnemonicEnum& mnemonic, CPU* cpu)
{
    switch (mnemonic)
    {
    case OperatorMnemonicEnum::A:
        {
            cpu->set8bitRegister(OpMnemonicToReg::convert(mnemonic), value);
            break;
        }
    case OperatorMnemonicEnum::C:
        {
            uint8_t lsbAddr = cpu->get8bitRegisterValue(OpMnemonicToReg::convert(mnemonic));
            cpu->write(0xFF00 + lsbAddr, value);
            break;
        }
    case OperatorMnemonicEnum::n8:
        {
            uint8_t lsbAddr = cpu->fetchMemory();
            cpu->write(0xFF00 + lsbAddr, value);
            break;
        }
    default:
        {
            throw std::invalid_argument("Invalid mnemonic for LDH");
        }
    }
}

namespace Instructions
{
    void ldh(const InstructionParameters& params, CPU* cpu)
    {
        uint8_t value = get_ldh_byte(params.sndOpMnemonic, cpu);
        set_ldh_value(value, params.firstOpMnemonic, cpu);
    }
};