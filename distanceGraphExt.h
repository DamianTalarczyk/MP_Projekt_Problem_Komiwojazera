#ifndef DISTANCEGRAPHEXT_H
#define DISTANCEGRAPHEXT_H
#include "distanceGraph.h"
#include <vector>

// Punkt 3 z PDF: Wlasciwa implementacja grafu[cite: 21].
// "public DistanceGraph" oznacza, ze ta klasa podpisuje wczesniejsza umowe (dziedziczy).
class DistanceGraphExt : public DistanceGraph {
private:
    unsigned numCities; // Przechowuje ilosc miast (rozmiar mapy)
    
    // Dwuwymiarowa tablica dynamiczna (wektor wektorow) przechowujaca odleglosci.
    // Np. matrix[0][2] poda nam koszt przejazdu z miasta 0 do 2.
    std::vector<std::vector<unsigned>> matrix;

public:
    DistanceGraphExt(unsigned n);
    unsigned size() const;
    unsigned distance(unsigned i, unsigned j) const;
    void setDistance(unsigned i, unsigned j, unsigned d);
};
#endif