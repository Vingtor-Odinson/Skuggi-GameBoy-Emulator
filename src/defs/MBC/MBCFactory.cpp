#include <algorithm>
#include <stdexcept>
#include "MBC/MBCFactory.hpp"
#include "MBC/MBC1.hpp"

MBC* MBCFactory::createMBC(const std::vector<uint8_t>& ROMData) {

    uint8_t type = ROMData[0x147];
    auto it = mbcTypes.find(type);

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