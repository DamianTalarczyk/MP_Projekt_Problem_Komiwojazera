#ifndef HEURISTICTSPSOLVER_H
#define HEURISTICTSPSOLVER_H
#include "tspSolver.h"

// Klasa obslugujaca oba algorytmy przyblizone[cite: 43, 47].
class HeuristicTSPSolver : public TSPSolver {
private:
    int algType; // Przechowuje informacje, czy wybrano metode 0 (NN) czy 1 (SE) [cite: 50-52]
    Tour<unsigned> solveNN(const DistanceGraph& g, unsigned start);
    Tour<unsigned> solveSE(const DistanceGraph& g, unsigned start);
    
public:
    HeuristicTSPSolver(int type); // Konstruktor wymagany w PDF [cite: 48-49]
    Tour<unsigned> solve(const DistanceGraph& g, unsigned start = 0);
};
#endif