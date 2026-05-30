#include "exactTSPSolver.h"
#include "myexceptions.h"
#include <algorithm>
#include <numeric>

Tour<unsigned> ExactTSPSolver::solve(const DistanceGraph& g, unsigned start) { 
    if (start >= g.size()) throw MyExceptions("Blad: Niepoprawne miasto startowe!"); 

    unsigned n = g.size();
    std::vector<unsigned> cities;
    for (unsigned i = 0; i < n; ++i) {
        if (i != start) cities.push_back(i);
    }

    Tour<unsigned> bestTour;
    unsigned minCost = -1; // odpowiednik nieskończoności dla unsigned

    // Przeglądanie wszystkich dopuszczalnych permutacji miast
    do {
        Tour<unsigned> currentTour;
        currentTour.addCity(start);
        for (unsigned c : cities) {
            currentTour.addCity(c); 
        }
        currentTour.addCity(start); // powrót do miasta startowego 

        unsigned currentCost = currentTour.totalCost(g); 
        if (currentCost < minCost) {
            minCost = currentCost;
            bestTour = currentTour;
        }
    } while (std::next_permutation(cities.begin(), cities.end()));

    return bestTour; 
}