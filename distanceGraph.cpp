#include "distanceGraph.h"

// Funkcja wypisujaca graf na ekran (zwykle petle for)
std::ostream& operator<<(std::ostream& out, const DistanceGraph& g) {
    unsigned n = g.size();
    for (unsigned i = 0; i < n; i++) {
        for (unsigned j = 0; j < n; j++) {
            out << g.distance(i, j) << "\t";
        }
        out << "\n";
    }
    return out;
}