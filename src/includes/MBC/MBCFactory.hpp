#ifndef SKUGGI_MBCFACTORY_HPP
#define SKUGGI_MBCFACTORY_HPP

#include <stdint.h>
#include <unordered_map>
#include <vector>
#include "enum/MBCEnum.hpp"

class MBC;

class MBCFactory{

    static const std::unordered_map<uint8_t, MBCEnum> mbcTypes;

public:
    static MBC* createMBC(const std::vector<uint8_t>& type);
};

#endif //SKUGGI_MBCFACTORY_HPP
