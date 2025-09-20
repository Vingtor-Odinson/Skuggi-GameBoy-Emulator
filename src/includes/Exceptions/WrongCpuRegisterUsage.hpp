#ifndef SKUGGI_WRONGCPUREGISTERUSAGE_HPP
#define SKUGGI_WRONGCPUREGISTERUSAGE_HPP

#include <exception>
#include <string>
#include <iostream>

#include "Utils/Conversors/RegisterEnumToString.hpp"

// Custom exception class for incorrect CPU register usage
class WrongCpuRegisterUsageException : public std::exception {
public:
    // Constructor with a message and the invalid register types (8-bit and 16-bit)
    WrongCpuRegisterUsageException(const std::string& message, const RegistersEnum& invalidRegister)
            : msg(message), invalidReg(invalidRegister) {}

    // Override the what() function to provide a custom error message
    const char* what() const noexcept override {
        std::string fullMessage = msg + " Invalid register: " + registerToString(invalidReg);
        return fullMessage.c_str();
    }

private:
    std::string msg;
    RegistersEnum invalidReg;
};

#endif //SKUGGI_WRONGCPUREGISTERUSAGE_HPP
