#ifndef SKUGGI_REGISTERENUMTOSTRING_HPP
#define SKUGGI_REGISTERENUMTOSTRING_HPP

#include <array>
#include "enum/RegistersEnum.hpp"

constexpr std::array<const char*, 15> registerNames = {
        "A",
        "B",
        "C",
        "D",
        "E",
        "F",
        "H",
        "L",
        "AF",
        "BC",
        "DE",
        "HL",
        "SP",
        "PC",
        "INVALID"
};

constexpr const char* registerToString(const RegistersEnum& reg) {
    std::size_t index = static_cast<int>(reg);
    return (index < registerNames.size()) ? registerNames[index] : "Unknown Register";
}

#endif //SKUGGI_REGISTERENUMTOSTRING_HPP
