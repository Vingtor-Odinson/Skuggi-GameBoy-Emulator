#include <algorithm>
#include <stdexcept>
#include "MBC/MBCFactory.hpp"
#include "MBC/MBC1.hpp"

const std::unordered_map<uint8_t, MBCEnum> MBCFactory::mbcTypes = {
{0x00, MBCEnum::NoMBC},
{0x01, MBCEnum::MBC1},
{0x02, MBCEnum::MBC1},
{0x03, MBCEnum::MBC1}
};

MBC* MBCFactory::createMBC(const std::vector<uint8_t>& ROMData) {

    uint8_t type = ROMData[0x147];
    auto it = mbcTypes.find(type); //todo: separar em um método pra facilitar a legibilidade

    if(it == mbcTypes.end()) {
        throw std::runtime_error("Unknown MBC type.");
    }

    switch (it->second) {
        case MBCEnum::NoMBC:
            return nullptr;
        case MBCEnum::MBC1:
            return new MBC1();
        default:
            std::runtime_error("MBC not implemented.");
    }
}