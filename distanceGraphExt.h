#ifndef DISTANCEGRAPHEXT_H
#define DISTANCEGRAPHEXT_H

#include "distanceGraph.h"
#include <vector>

class DistanceGraphExt : public DistanceGraph { 
private:
    unsigned numCities;
    std::vector<std::vector<unsigned>> matrix; // reprezentacja macierzy
public:
    DistanceGraphExt(unsigned n); 
    
    unsigned size() const override;
    unsigned distance(unsigned i, unsigned j) const override;
    void setDistance(unsigned i, unsigned j, unsigned d) override;
};

#endif