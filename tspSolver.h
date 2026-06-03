#ifndef TSPSOLVER_H
#define TSPSOLVER_H

#include "tour.h"
#include "distanceGraph.h"

// Glowny interfejs dla algorytmow
class TSPSolver {
public:
    virtual ~TSPSolver() {}
    virtual Tour<unsigned> solve(const DistanceGraph& g, unsigned start = 0) = 0;
};

#endif