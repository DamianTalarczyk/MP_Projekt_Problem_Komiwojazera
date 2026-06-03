#ifndef MYEXCEPTIONS_H
#define MYEXCEPTIONS_H

#include <string>

// Klasa wymagana w PDF do zglaszania bledow
class MyExceptions {
private:
    std::string msg;
public:
    MyExceptions(std::string message);
    std::string getMessage() const;
};

#endif