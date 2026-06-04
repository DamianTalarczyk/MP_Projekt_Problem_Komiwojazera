#include "myexceptions.h"

using namespace std;

// Konstruktor - w momencie tworzenia bledu, zapisujemy jego tresc
MyExceptions::MyExceptions(string message) {
    msg = message;
}

// Metoda pozwalajaca odczytac blad na ekranie
string MyExceptions::getMessage() const {
    return msg;
}