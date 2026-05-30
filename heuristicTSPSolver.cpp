#include "heuristicTSPSolver.h"
#include "myexceptions.h"
#include <vector>

HeuristicTSPSolver::HeuristicTSPSolver(int type) : algType(type) { 
    if (type != 0 && type != 1) {
        throw MyExceptions("Blad: Nieznany typ heurystyki!");
    }
}

Tour<unsigned> HeuristicTSPSolver::solve(const DistanceGraph& g, unsigned start) { 
    if (start >= g.size()) throw MyExceptions("Blad: Niepoprawne miasto startowe!"); 
    
    if (algType == 0) return solveNN(g, start); 
    else return solveSE(g, start);
}

// 0 - Metoda najbliższego sąsiada (NN) [cite: 52, 53]
Tour<unsigned> HeuristicTSPSolver::solveNN(const DistanceGraph& g, unsigned start) { 
    unsigned n = g.size();
    std::vector<bool> visited(n, false);
    Tour<unsigned> tour;

    unsigned current = start;
    tour.addCity(current);
    visited[current] = true;

    for (unsigned step = 1; step < n; ++step) {
        unsigned nextCity = -1;
        unsigned minDst = -1;

        for (unsigned j = 0; j < n; ++j) {
            if (!visited[j] && g.distance(current, j) < minDst) { 
                minDst = g.distance(current, j); 
                nextCity = j;
            }
        }
        current = nextCity;
        tour.addCity(current); 
        visited[current] = true; 
    }
    tour.addCity(start); // powrót 
    return tour;
}

// 1 - Metoda najmniejszej krawędzi (SE) 
Tour<unsigned> HeuristicTSPSolver::solveSE(const DistanceGraph& g, unsigned start) {
    // Tutaj powinna znaleźć się logika zbierania najkrótszych krawędzi 
    // i budowania cyklu z kontrolą stopnia wierzchołków <= 2
    // Dla uproszczenia szablonu zwracamy pustą/prostą trasę:
    Tour<unsigned> tour;
    // ... (Twoja implementacja algorytmu SE) ...
    return tour;
}