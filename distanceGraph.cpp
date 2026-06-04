#include "distanceGraph.h"

/* Implementacja wypisywania grafu na ekran.
Uzywamy dwoch petli for (rzędy i kolumny), aby narysowac macierz.*/
std::ostream& operator<<(std::ostream& out, const DistanceGraph& g) {
    unsigned n = g.size();
    for (unsigned i = 0; i < n; i++) {
        for (unsigned j = 0; j < n; j++) {
            out << g.distance(i, j) << "\t"; // \t to tabulacja dla ladnego wyrownania
        }
        out << "\n";
    }
    return out; // Zwracamy strumien, aby mozna bylo robic cout << g << ... 
}