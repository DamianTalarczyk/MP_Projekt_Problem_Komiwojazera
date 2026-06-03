#ifndef HEURISTICTSPSOLVER_H
#define HEURISTICTSPSOLVER_H

#include "tspSolver.h"

class HeuristicTSPSolver : public TSPSolver {
private:
    int algType;
    Tour<unsigned> solveNN(const DistanceGraph& g, unsigned start);
    Tour<unsigned> solveSE(const DistanceGraph& g, unsigned start);
    
public:
    HeuristicTSPSolver(int type);
    Tour<unsigned> solve(const DistanceGraph& g, unsigned start = 0);
};

#endif