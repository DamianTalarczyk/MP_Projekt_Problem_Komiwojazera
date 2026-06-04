#ifndef MYEXCEPTIONS_H
#define MYEXCEPTIONS_H
#include <string>
#include <exception>

using namespace std;

/* Dziedziczy po standardowej klasie wyjatkow C++ (std::exception), 
dzieki czemu wspolpracuje z blokami try-catch w main.cpp*/
class MyExceptions : public exception {
private:
    string msg; // Zmienna przechowujaca tresc bledu
public:
    MyExceptions(string message);
    string getMessage() const;
};
#endif