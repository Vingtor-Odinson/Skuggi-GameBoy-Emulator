#ifndef SKUGGI_MBCFACTORY_HPP
#define SKUGGI_MBCFACTORY_HPP

#include <stdint.h>
#include <unordered_map>
#include <vector>
#include "enum/MBCEnum.hpp"

class MBC;

class MBCFactory{

    std::unordered_map<uint8_t, MBCEnum> mbcTypes = {
            {0x00, MBCEnum::NoMBC},
            {0x01, MBCEnum::MBC1},
            {0x02, MBCEnum::MBC1},
            {0x03, MBCEnum::MBC1}
    };

public:
    MBC* createMBC(const std::vector<uint8_t>& type);
};

#endif //SKUGGI_MBCFACTORY_HPP
