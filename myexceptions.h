#ifndef MYEXCEPTIONS_H
#define MYEXCEPTIONS_H
#include <string>
#include <exception>

/* Dziedziczy po standardowej klasie wyjatkow C++ (std::exception), 
dzieki czemu wspolpracuje z blokami try-catch w main.cpp*/
class MyExceptions : public std::exception {
private:
    std::string msg; // Zmienna przechowujaca tresc bledu
public:
    MyExceptions(std::string message);
    std::string getMessage() const;
};
#endif