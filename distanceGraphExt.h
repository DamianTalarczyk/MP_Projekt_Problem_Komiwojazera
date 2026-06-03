#ifndef DISTANCEGRAPHEXT_H
#define DISTANCEGRAPHEXT_H

#include "distanceGraph.h"
#include <vector>

// Klasa pochodna implementujaca wlasciwy graf
class DistanceGraphExt : public DistanceGraph {
private:
    unsigned numCities;
    std::vector<std::vector<unsigned>> matrix;

public:
    DistanceGraphExt(unsigned n);
    unsigned size() const;
    unsigned distance(unsigned i, unsigned j) const;
    void setDistance(unsigned i, unsigned j, unsigned d);
};

#endif