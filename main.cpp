#include <iostream>
#include "distanceGraph.h"
#include "distanceGraphExt.h"
#include "tour.h"
#include "tspSolver.h"
#include "exactTSPSolver.h"
#include "heuristicTSPSolver.h"

int main() {
    // Inicjalizacja grafu 
    DistanceGraph* g = new DistanceGraphExt(6); 
    
    g->setDistance(0, 1, 14); 
    g->setDistance(0, 2, 3);  
    g->setDistance(0, 3, 20); 
    g->setDistance(0, 4, 11);
    g->setDistance(0, 5, 2);
    g->setDistance(1, 2, 1); 
    g->setDistance(1, 3, 6); 
    g->setDistance(1, 4, 17);  
    g->setDistance(1, 5, 19);  
    g->setDistance(2, 3, 16);  
    g->setDistance(2, 4, 3);
    g->setDistance(2, 5, 10); 
    g->setDistance(3, 4, 12); 
    g->setDistance(3, 5, 4);  
    g->setDistance(4, 5, 5);  


    std::cout << "Macierz odleglosci:\n";
    std::cout << *g << "\n"; 

    // Solvery 
    TSPSolver* exact = new ExactTSPSolver();
    TSPSolver* greedyNN = new HeuristicTSPSolver(0); 
    TSPSolver* greedySE = new HeuristicTSPSolver(1); 

    // Wyznaczenie tras 
    Tour<unsigned> t1 = exact->solve(*g, 0); 
    Tour<unsigned> t2 = greedyNN->solve(*g, 0); 
    Tour<unsigned> t3 = greedySE->solve(*g, 0); 

    // Prezentacja wyników
    std::cout << "=== ALGORYTM DOKLADNY ===\n"; 
    std::cout << t1 << "\n"; 
    std::cout << "Koszt: " << t1.totalCost(*g) << "\n\n";

    std::cout << "=== HEURYSTYKA NN ===\n"; 
    std::cout << t2 << "\n"; 
    std::cout << "Koszt: " << t2.totalCost(*g) << "\n\n"; 

    std::cout << "=== HEURYSTYKA SMALLEST EDGE ===\n"; 
    std::cout << t3 << "\n"; 
    std::cout << "Koszt: " << t3.totalCost(*g) << "\n\n"; 

    // Sprzątanie pamięci (Destrukcja) 
    delete greedySE; 
    delete greedyNN; 
    delete exact;    
    delete g;       

    return 0;
}