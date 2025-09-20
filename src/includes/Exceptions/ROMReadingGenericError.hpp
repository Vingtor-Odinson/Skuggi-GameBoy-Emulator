#ifndef ROMReadingGenericError_HPP
#define ROMReadingGenericError_HPP

#include <exception>
#include <string>
#include <iostream>

class ROMReadingGenericError : public std::exception {
public:
    // Constructor with a message and the invalid register types (8-bit and 16-bit)
    ROMReadingGenericError(const std::string& message)
            : msg(message) {}

    // Override the what() function to provide a custom error message
    const char* what() const noexcept override {
        return msg.c_str();
    }

private:
    std::string msg;
};

#endif //ROMReadingGenericError_HPP
