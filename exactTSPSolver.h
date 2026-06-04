#ifndef EXACTTSPSOLVER_H
#define EXACTTSPSOLVER_H
#include "tspSolver.h"

// Klasa algorytmu dokladnego [cite: 42-46].
class ExactTSPSolver : public TSPSolver {
public:
    Tour<unsigned> solve(const DistanceGraph& g, unsigned start = 0);
};
#endif