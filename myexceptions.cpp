#include "myexceptions.h"

MyExceptions::MyExceptions(std::string message) {
    msg = message;
}

std::string MyExceptions::getMessage() const {
    return msg;
}