#ifndef EXACTTSPSOLVER_H
#define EXACTTSPSOLVER_H

#include "tspSolver.h"

class ExactTSPSolver : public TSPSolver {
public:
    Tour<unsigned> solve(const DistanceGraph& g, unsigned start = 0) override; 
};

#endif