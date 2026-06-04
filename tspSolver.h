#ifndef TSPSOLVER_H
#define TSPSOLVER_H
#include "tour.h"
#include "distanceGraph.h"

//DO POPARWY: Interfejs dla wszystkich ekspertow od szukania tras.
class TSPSolver {
public:
    virtual ~TSPSolver() {} // Wirtualny destruktor
    
    // Metoda czysto wirtualna. Kazdy algorytm musi przyjac mape 'g' i wydac trase 'Tour'.
    virtual Tour<unsigned> solve(const DistanceGraph& g, unsigned start = 0) = 0;
};
#endif