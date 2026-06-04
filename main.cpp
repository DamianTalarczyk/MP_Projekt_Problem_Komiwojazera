#include <iostream>
#include "distanceGraphExt.h"
#include "exactTSPSolver.h"
#include "heuristicTSPSolver.h"
#include "myexceptions.h"
#include <chrono>
#include <fstream>

using namespace std;

// Glowny plik wywolujacy dzialanie programu
int main() {
    try { // Blok przechwytujacy wyjatki rzucane z klas
        
        //// Polimorfizm: Uzywamy wskaznika na interfejs bazowy, ale tworzymy obiekt klasy pochodnej
        //DistanceGraph* g = new DistanceGraphExt(6); 

        //
        //// Zapisywanie polaczen w grafie (mapie)
        //g->setDistance(0, 1, 14); 
        //g->setDistance(0, 2, 3);  
        //g->setDistance(0, 3, 20); 
        //g->setDistance(0, 4, 11);
        //g->setDistance(0, 5, 2);
        //g->setDistance(1, 2, 1); 
        //g->setDistance(1, 3, 6); 
        //g->setDistance(1, 4, 17);  
        //g->setDistance(1, 5, 19);  
        //g->setDistance(2, 3, 16);  
        //g->setDistance(2, 4, 3);
        //g->setDistance(2, 5, 10); 
        //g->setDistance(3, 4, 12); 
        //g->setDistance(3, 5, 4);  
        //g->setDistance(4, 5, 5);  

        //cout << "Macierz odleglosci:\n";
        //cout << *g << "\n"; // Uzycie przeciazonego operatora <<

        // Otwieramy plik tekstowy z danymi grafu, gdzie pierwsza linia to liczba miast
        ifstream file("graf.txt");
        if (!file.is_open()) {
            throw MyExceptions("Blad: Nie udalo sie otworzyc pliku graf.txt");
        }

        // Wczytujemy liczbe miast (pierwsza wartosc z pliku)
        unsigned n;
        if (!(file >> n)) {
            throw MyExceptions("Blad: Brak liczby miast");
        }

        // Tworzymy obiekt grafu i
        // przekazujemy dynamicznie zmienna 'n' wczytana z pliku
        DistanceGraph* g = new DistanceGraphExt(n);

        // Za pomoca petli wczytujemy reszte macierzy i uzupelniamy graf
        for (unsigned i = 0; i < n; i++) {
            for (unsigned j = 0; j < n; j++) {
                unsigned val;
                if (!(file >> val)) {
                    throw MyExceptions("Blad: Za malo danych w pliku grafu!");
                }
                g->setDistance(i, j, val); // Uzywamy standardowej metody z instrukcji
            }
        }
        file.close(); // Zamykamy strumien pliku, dane sa juz bezpieczne w obiekcie grafu

        cout << "Macierz odleglosci zaladowana z pliku (Rozmiar: " << n << "):\n";
        cout << *g << "\n";

        /*Tworzenie "ekspertow" do liczenia tras.
        Tu rowniez widac polimorfizm - pod jednym interfejsem TSPSolver kryja sie rozne algorytmy.*/
        TSPSolver* exact = new ExactTSPSolver();
        TSPSolver* greedyNN = new HeuristicTSPSolver(0);
        TSPSolver* greedySE = new HeuristicTSPSolver(1);

        // Wyznaczanie tras
        // Pomiar dla algorytmu dokladnego
        auto startExact = chrono::high_resolution_clock::now();
        Tour<unsigned> t1 = exact->solve(*g, 0);
        auto endExact = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> durationExact = endExact - startExact;

        // Pomiar dla heurystyki Najblizszego Sasiada (NN)
        auto startNN = chrono::high_resolution_clock::now();
        Tour<unsigned> t2 = greedyNN->solve(*g, 0);
        auto endNN = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> durationNN = endNN - startNN;

        // Pomiar dla heurystyki Najmniejszej Krawedzi (SE)
        auto startSE = chrono::high_resolution_clock::now();
        Tour<unsigned> t3 = greedySE->solve(*g, 0);
        auto endSE = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> durationSE = endSE - startSE;

        // Wyswietlanie wynikow 
        cout << "ALgorytm Dokladny\n";
        cout << t1 << "\n"; // Operator << dla trasy Tour
        cout << "Koszt: " << t1.totalCost(*g) << "\n";
        cout << "Czas wykonania: " << durationExact.count() << " ms\n\n";

        cout << "Heurystyka - Nearest Neighbor\n";
        cout << t2 << "\n";
        cout << "Koszt: " << t2.totalCost(*g) << "\n";
        cout << "Czas wykonania: " << durationNN.count() << " ms\n\n";

        cout << "Heurystyka - Smallest Edge\n";
        cout << t3 << "\n";
        cout << "Koszt: " << t3.totalCost(*g) << "\n";
        cout << "Czas wykonania: " << durationSE.count() << " ms\n\n";

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