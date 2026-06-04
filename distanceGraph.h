#ifndef DISTANCEGRAPH_H
#define DISTANCEGRAPH_H
#include <iostream>

using namespace std;

/* Klasa abstrakcyjna ("szablon/umowa"). Metody z "= 0" to metody czysto wirtualne.
Oznacza to, ze ta klasa nie ma kodu - wymusza tylko, aby inne klasy (np. Ext)
mialy dokladnie takie same metody. To zapewnia elastycznosc*/
class DistanceGraph {
public:
    virtual ~DistanceGraph() {} // Wirtualny destruktor do usuwania pamieci
    
    virtual unsigned size() const = 0;
    virtual unsigned distance(unsigned i, unsigned j) const = 0;
    virtual void setDistance(unsigned i, unsigned j, unsigned d) = 0;
    
    // Przeciazenie operatora wypisywania calej macierzy
    friend ostream& operator<<(ostream& out, const DistanceGraph& g);
};
#endif