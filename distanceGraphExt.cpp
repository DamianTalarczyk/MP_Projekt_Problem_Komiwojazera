#include "distanceGraphExt.h"
#include "myexceptions.h"

DistanceGraphExt::DistanceGraphExt(unsigned n) : numCities(n), matrix(n, std::vector<unsigned>(n, 0)) { 
    // Konstruktor tworzy graf z zerami na przekątnej
}

unsigned DistanceGraphExt::size() const { 
    return numCities;
}

unsigned DistanceGraphExt::distance(unsigned i, unsigned j) const { 
    if (i >= numCities || j >= numCities) {
        throw MyExceptions("Blad: Indeks miasta poza zakresem!"); 
    }
    return matrix[i][j];
}

void DistanceGraphExt::setDistance(unsigned i, unsigned j, unsigned d) { 
    if (i >= numCities || j >= numCities) {
        throw MyExceptions("Blad: Indeks miasta poza zakresem!"); 
    }
    if (i == j && d != 0) { 
        throw MyExceptions("Blad: Odleglosc do samego siebie musi wynosic 0!"); 
    }
    
    matrix[i][j] = d; 
    matrix[j][i] = d; // graf jest symetryczny 
}