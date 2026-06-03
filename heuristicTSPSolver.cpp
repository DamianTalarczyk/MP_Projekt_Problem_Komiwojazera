#include "exactTSPSolver.h"
#include "myexceptions.h"

// Klasyczna, "studencka" funkcja rekurencyjna do szukania permutacji
void generatePermutations(int k, int n, unsigned* path, unsigned& minCost, Tour<unsigned>& bestTour, const DistanceGraph& g, unsigned start) {
    if (k == n) {
        // Zbuduj trase
        Tour<unsigned> currentTour;
        currentTour.addCity(start);
        for (int i = 0; i < n; i++) {
            currentTour.addCity(path[i]);
        }
        currentTour.addCity(start);
        
        // Policz i porownaj z rekordem
        unsigned cost = currentTour.totalCost(g);
        if (cost < minCost) {
            minCost = cost;
            bestTour = currentTour;
        }
        return;
    }
    
    for (int i = k; i < n; i++) {
        // Swap
        unsigned temp = path[k];
        path[k] = path[i];
        path[i] = temp;
        
        generatePermutations(k + 1, n, path, minCost, bestTour, g, start);
        
        // Backtrack (cofniecie)
        temp = path[k];
        path[k] = path[i];
        path[i] = temp;
    }
}

Tour<unsigned> ExactTSPSolver::solve(const DistanceGraph& g, unsigned start) {
    if (start >= g.size()) throw MyExceptions("Blad: Niepoprawne miasto startowe");
    
    unsigned n = g.size();
    unsigned path[20]; // Prosta tablica, zakladamy ze n nie przekroczy 20
    int idx = 0;
    
    // Wpisz miasta oprocz startowego
    for (unsigned i = 0; i < n; i++) {
        if (i != start) {
            path[idx] = i;
            idx++;
        }
    }
    
    unsigned minCost = 999999;
    Tour<unsigned> bestTour;
    
    // Startujemy funkcje rekurencyjna od indeksu 0
    generatePermutations(0, idx, path, minCost, bestTour, g, start);
    
    return bestTour;
}