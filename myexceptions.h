#ifndef MYEXCEPTIONS_H
#define MYEXCEPTIONS_H

#include <exception>
#include <string>

class MyExceptions : public std::exception {
private:
    std::string message;
public:
    MyExceptions(const std::string& msg);
    const char* what() const noexcept override;
};

#endif