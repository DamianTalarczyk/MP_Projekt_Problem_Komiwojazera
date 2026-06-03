#include "distanceGraphExt.h"
#include "myexceptions.h"

DistanceGraphExt::DistanceGraphExt(unsigned n) {
    numCities = n;
    unsigned INF = 999999; // Zabezpieczenie przed brakujacymi drogami
    
    for (unsigned i = 0; i < n; i++) {
        std::vector<unsigned> row;
        for (unsigned j = 0; j < n; j++) {
            if (i == j) row.push_back(0); // Zera na przekatnej
            else row.push_back(INF);
        }
        matrix.push_back(row);
    }
}

unsigned DistanceGraphExt::size() const {
    return numCities;
}

unsigned DistanceGraphExt::distance(unsigned i, unsigned j) const {
    if (i >= numCities || j >= numCities) throw MyExceptions("Blad: Zly indeks miasta!");
    return matrix[i][j];
}

void DistanceGraphExt::setDistance(unsigned i, unsigned j, unsigned d) {
    if (i >= numCities || j >= numCities) throw MyExceptions("Blad: Zly indeks miasta!");
    if (i == j && d != 0) throw MyExceptions("Blad: Odleglosc do siebie to 0!");
    
    // Graf symetryczny
    matrix[i][j] = d;
    matrix[j][i] = d;
}