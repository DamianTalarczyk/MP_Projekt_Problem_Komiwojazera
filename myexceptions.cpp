#include "myexceptions.h"

// Konstruktor - w momencie tworzenia bledu, zapisujemy jego tresc
MyExceptions::MyExceptions(std::string message) {
    msg = message;
}

// Metoda pozwalajaca odczytac blad na ekranie
std::string MyExceptions::getMessage() const {
    return msg;
}