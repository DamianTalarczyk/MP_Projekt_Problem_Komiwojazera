#include "myexceptions.h"

MyExceptions::MyExceptions(const std::string& msg) : message(msg) {}

const char* MyExceptions::what() const noexcept {
    return message.c_str();
}