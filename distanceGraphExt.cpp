#include "distanceGraphExt.h"
#include "myexceptions.h"

// Konstruktor wymagany przez PDF [cite: 23-25]. Tworzy graf dla 'n' miast.
DistanceGraphExt::DistanceGraphExt(unsigned n) {
    numCities = n;
    unsigned INF = 999999; // Zabezpieczenie! Brakujaca droga to dla algorytmu nieskonczonosc.
    
    for (unsigned i = 0; i < n; i++) {
        std::vector<unsigned> row;
        for (unsigned j = 0; j < n; j++) {
            // PDF[cite: 25]: Odleglosc do samego siebie (na przekatnej) musi wynosic 0.
            if (i == j) row.push_back(0); 
            else row.push_back(INF); // Wszystkie inne drogi domyslnie nie istnieja (sa zablokowane)
        }
        matrix.push_back(row);
    }
}

unsigned DistanceGraphExt::size() const { return numCities; }

// Pobieranie odleglosci z zabezpieczeniem (Punkt 7 PDF [cite: 56-57])
unsigned DistanceGraphExt::distance(unsigned i, unsigned j) const {
    if (i >= numCities || j >= numCities) throw MyExceptions("Blad: Zly indeks miasta!");
    return matrix[i][j];
}

// Ustawianie odleglosci (Budowa mapy)
void DistanceGraphExt::setDistance(unsigned i, unsigned j, unsigned d) {
    if (i >= numCities || j >= numCities) throw MyExceptions("Blad: Zly indeks miasta!");
    if (i == j && d != 0) throw MyExceptions("Blad: Odleglosc do siebie to 0!");
    
    // PDF[cite: 18]: Graf jest symetryczny (nieskierowany). 
    // Zatem droga z A do B (i->j) to ta sama droga co z B do A (j->i).
    matrix[i][j] = d;
    matrix[j][i] = d;
}