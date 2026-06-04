#ifndef TOUR_H
#define TOUR_H
#include <vector>
#include <iostream>
#include "distanceGraph.h"
#include "myexceptions.h"

using namespace std;

/* Szablon klasy:
Pozwala on na stworzenie trasy, ktorej koszt moze byc typu int, double, float itd. (Dzieki temu ze jest to szablon)
T = unsigned oznacza, ze domyslnie uzywamy liczb calkowitych dodatnich.
Poniewaz to szablon, caly kod metod musi byc w pliku .h
Kompilator generuje kod w momencie uzycia w main.cpp dlatego tour.h pozostaje pusty*/
template <typename T = unsigned>
class Tour {
private:
    vector<unsigned> visitedCities; // Zapisuje kolejne miasta

public:
    void addCity(unsigned city) { visitedCities.push_back(city); }
    unsigned length() const { return visitedCities.size(); }
    
    unsigned city(unsigned i) const {
        if (i >= visitedCities.size()) throw MyExceptions("Blad: Zly indeks trasy!");
        return visitedCities[i];
    }

    // Metoda totalCost: Oblicza sume kosztow calej wyznaczonej trasy
    T totalCost(const DistanceGraph& g) const {
        T cost = 0;
        if (visitedCities.empty()) return 0; // Zabezpieczenie przed pusta trasa
        
        /* Petla idzie po liscie odwiedzonych miast.
        Odczytuje z grafu 'g' odleglosc miedzy obecnym miastem [i], a nastepnym [i+1].*/
        for (unsigned i = 0; i < visitedCities.size() - 1; i++) {
            cost += g.distance(visitedCities[i], visitedCities[i + 1]);
        }
        return cost;
    }

    // Przeciazenie do wypisywania z strzalkami
    friend ostream& operator<<(ostream& out, const Tour<T>& t) {
        for (unsigned i = 0; i < t.length(); i++) {
            out << t.city(i);
            // Dopoki nie jestesmy na ostatnim miescie, wypisuj strzalke miedzy nimi
            if (i != t.length() - 1) out << " -> ";
        }
        return out;
    }
};
#endif