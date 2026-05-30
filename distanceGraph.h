#ifndef DISTANCEGRAPH_H
#define DISTANCEGRAPH_H

#include <iostream>

class DistanceGraph {
public:
    virtual ~DistanceGraph() {}
    virtual unsigned size() const = 0; 
    virtual unsigned distance(unsigned i, unsigned j) const = 0; 
    virtual void setDistance(unsigned i, unsigned j, unsigned d) = 0; 

    // Przeciążenie operatora wypisywania macierzy 
    friend std::ostream& operator<<(std::ostream& out, const DistanceGraph& g);
};

#endif