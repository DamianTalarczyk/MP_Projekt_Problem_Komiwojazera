#ifndef TSPSOLVER_H
#define TSPSOLVER_H

#include "distanceGraph.h"
#include "tour.h"

class TSPSolver { 
public:
    virtual ~TSPSolver() {}
    // Zwraca Tour<unsigned>, ponieważ domyślny parametr szablonu to unsigned 
    virtual Tour<unsigned> solve(const DistanceGraph& g, unsigned start = 0) = 0; 
};

#endif