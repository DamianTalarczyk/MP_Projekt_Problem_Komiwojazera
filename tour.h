#ifndef TOUR_H
#define TOUR_H

#include <vector>
#include <iostream>
#include "distanceGraph.h"
#include "myexceptions.h"

// Szablon klasy wymagany przez punkt 7 w PDF
template <typename T = unsigned>
class Tour {
private:
    std::vector<T> visitedCities;

public:
    void addCity(T city) {
        visitedCities.push_back(city);
    }

    unsigned length() const {
        return visitedCities.size();
    }

    T city(unsigned i) const {
        if (i >= visitedCities.size()) throw MyExceptions("Blad: Zly indeks trasy!");
        return visitedCities[i];
    }

    // Obliczanie sumy kosztow na podstawie grafu
    T totalCost(const DistanceGraph& g) const {
        T cost = 0;
        if (visitedCities.empty()) return 0;
        
        for (unsigned i = 0; i < visitedCities.size() - 1; i++) {
            cost += g.distance(visitedCities[i], visitedCities[i + 1]);
        }
        return cost;
    }

    // Wypisywanie miast
    friend std::ostream& operator<<(std::ostream& out, const Tour<T>& t) {
        for (unsigned i = 0; i < t.length(); i++) {
            out << t.city(i);
            if (i != t.length() - 1) out << " -> ";
        }
        return out;
    }
};

#endif