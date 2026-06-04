#ifndef EXACTTSPSOLVER_H
#define EXACTTSPSOLVER_H
#include "tspSolver.h"

// Klasa algorytmu dokladnego
class ExactTSPSolver : public TSPSolver {
public:
    Tour<unsigned> solve(const DistanceGraph& g, unsigned start = 0);
};
#endif