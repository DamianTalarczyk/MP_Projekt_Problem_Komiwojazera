#ifndef TOUR_H
#define TOUR_H

#include <vector>
#include <iostream>
#include "distanceGraph.h"
#include "myexceptions.h"

// Użycie szablonu klasy - typ T definiuje typ zwracanego kosztu trasy 
template <typename T = unsigned>
class Tour { 
private:
    std::vector<unsigned> visitedCities; // kolejność odwiedzanych miast [cite: 32]
public:
    Tour() = default;

    void addCity(unsigned city) {
        visitedCities.push_back(city);
    }

    unsigned length() const { 
        return visitedCities.size();
    }

    unsigned city(unsigned i) const { 
        if (i >= visitedCities.size()) {
            throw MyExceptions("Blad: Indeks trasy poza zakresem!");
        }
        return visitedCities[i];
    }

    T totalCost(const DistanceGraph& g) const { 
        if (visitedCities.empty()) return 0;
        
        T cost = 0;
        for (size_t i = 0; i < visitedCities.size() - 1; ++i) {
            cost += g.distance(visitedCities[i], visitedCities[i + 1]);
        }
        return cost;
    }

    // Przeciążenie operatora << dla klasy szablonowej 
    friend std::ostream& operator<<(std::ostream& out, const Tour<T>& t) { 
        for (unsigned i = 0; i < t.length(); ++i) { 
            out << t.city(i) << (i == t.length() - 1 ? "" : " -> "); 
        }
        return out;
    }
};

#endif