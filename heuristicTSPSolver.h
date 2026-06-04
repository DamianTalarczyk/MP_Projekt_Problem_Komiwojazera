#ifndef HEURISTICTSPSOLVER_H
#define HEURISTICTSPSOLVER_H
#include "tspSolver.h"

// Klasa obslugujaca oba algorytmy przyblizone
class HeuristicTSPSolver : public TSPSolver {
private:
    int algType; // Przechowuje informacje, czy wybrano metode 0 (NN - Nearest Neighbor/Najbliższy Sąsiad) czy 1 (SE - Smallest Edge/Najmniejsza Krawędź) 
    Tour<unsigned> solveNN(const DistanceGraph& g, unsigned start);
    Tour<unsigned> solveSE(const DistanceGraph& g, unsigned start);
    
public:
    HeuristicTSPSolver(int type); // Konstruktor
    Tour<unsigned> solve(const DistanceGraph& g, unsigned start = 0);
};
#endif