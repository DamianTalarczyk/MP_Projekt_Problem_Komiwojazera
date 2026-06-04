#include <iostream>
#include "distanceGraphExt.h"
#include "exactTSPSolver.h"
#include "heuristicTSPSolver.h"
#include "myexceptions.h"

using namespace std;

// Glowny plik wywolujacy dzialanie programu
int main() {
    try { // Blok przechwytujacy wyjatki rzucane z klas
        
        // Polimorfizm: Uzywamy wskaznika na interfejs bazowy, ale tworzymy obiekt klasy pochodnej
        DistanceGraph* g = new DistanceGraphExt(6); 

        
        // Zapisywanie polaczen w grafie (mapie)
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

        cout << "Macierz odleglosci:\n";
        cout << *g << "\n"; // Uzycie przeciazonego operatora <<

        /*Tworzenie "ekspertow" do liczenia tras.
        Tu rowniez widac polimorfizm - pod jednym interfejsem TSPSolver kryja sie rozne algorytmy.*/
        TSPSolver* exact = new ExactTSPSolver();
        TSPSolver* greedyNN = new HeuristicTSPSolver(0);
        TSPSolver* greedySE = new HeuristicTSPSolver(1);

        // Wyznaczanie tras
        Tour<unsigned> t1 = exact->solve(*g, 0);
        Tour<unsigned> t2 = greedyNN->solve(*g, 0);
        Tour<unsigned> t3 = greedySE->solve(*g, 0);

        // Wyswietlanie wynikow 
        cout << "=== ALGORYTM DOKLADNY ===\n";
        cout << t1 << "\n"; // Operator << dla trasy Tour
        cout << "Koszt: " << t1.totalCost(*g) << "\n\n";

        cout << "=== HEURYSTYKA NN ===\n";
        cout << t2 << "\n";
        cout << "Koszt: " << t2.totalCost(*g) << "\n\n";

        cout << "=== HEURYSTYKA SMALLEST EDGE ===\n";
        cout << t3 << "\n";
        cout << "Koszt: " << t3.totalCost(*g) << "\n\n";

        // Zarzadzanie pamiecia - instrukcja delete zwalnia wczesniej przydzielona nowa pamiec (new)
        delete greedySE;
        delete greedyNN;
        delete exact;
        delete g;

    } catch (const MyExceptions& e) {
        /* Jesli jakas z metod rzuci wyjatkiem
        program tu wpadnie, wyswietli tekst bledu i bezpiecznie sie zakonczy.*/
        cout << e.getMessage() << endl;
    }

    return 0;
}