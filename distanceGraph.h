#ifndef DISTANCEGRAPH_H
#define DISTANCEGRAPH_H
#include <iostream>

// Interfejs wymagany przez punkt 1 instrukcji PDF [cite: 9-13].
// Klasa abstrakcyjna ("szablon/umowa"). Metody z "= 0" to metody czysto wirtualne.
// Oznacza to, ze ta klasa nie ma kodu - wymusza tylko, aby inne klasy (np. Ext)
// mialy dokladnie takie same metody. To zapewnia elastycznosc[cite: 4].
class DistanceGraph {
public:
    virtual ~DistanceGraph() {} // Wirtualny destruktor do poprawnego usuwania pamieci
    
    virtual unsigned size() const = 0;
    virtual unsigned distance(unsigned i, unsigned j) const = 0;
    virtual void setDistance(unsigned i, unsigned j, unsigned d) = 0;
    
    // Punkt 2 z PDF: Przeciazenie operatora wypisywania calej macierzy [cite: 19-20].
    friend std::ostream& operator<<(std::ostream& out, const DistanceGraph& g);
};
#endif