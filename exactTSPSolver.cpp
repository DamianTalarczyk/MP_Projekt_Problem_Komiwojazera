#include "exactTSPSolver.h"
#include "myexceptions.h"

// Funkcja rekurencyjna. Uzywa techniki "Backtracking" (z nawrotami).
// Sluzy do generowania permutacji (wszystkich mozliwych kolejnosci miast).
void generatePermutations(int k, int n, unsigned* path, unsigned& minCost, Tour<unsigned>& bestTour, const DistanceGraph& g, unsigned start) {
    // Warunek konca rekurencji - dotarlismy do konca tablicy, mamy ulozona 1 pelna kombinacje
    if (k == n) {
        Tour<unsigned> currentTour;
        currentTour.addCity(start); // Miasto 0
        for (int i = 0; i < n; i++) {
            currentTour.addCity(path[i]); // Srodkowe miasta (np. 1, 2, 4, 3)
        }
        currentTour.addCity(start); // Powrot do miasta 0
        
        // Zliczamy koszt tej konkretnej wersji.
        unsigned cost = currentTour.totalCost(g);
        // Jesli znalezlismy lepsza (tansza) trase, nadpisujemy absolutny rekord 'minCost'
        if (cost < minCost) {
            minCost = cost;
            bestTour = currentTour;
        }
        return;
    }
    
    // Proces mieszania miast (podmienianie miejscami za pomoca zmiennej temp)
    for (int i = k; i < n; i++) {
        unsigned temp = path[k];
        path[k] = path[i];
        path[i] = temp;
        
        // Wywolanie samej siebie (rekurencja) dla kolejnego elementu
        generatePermutations(k + 1, n, path, minCost, bestTour, g, start);
        
        // Backtracking - po wyjsciu z rekurencji odwracamy podmiane, 
        // by dac szanse na sprawdzenie innej kombinacji
        temp = path[k];
        path[k] = path[i];
        path[i] = temp;
    }
}

// Funkcja glowna algorytmu dokladnego
Tour<unsigned> ExactTSPSolver::solve(const DistanceGraph& g, unsigned start) {
    if (start >= g.size()) throw MyExceptions("Blad: Niepoprawne miasto startowe");
    
    unsigned n = g.size();
    unsigned path[20]; // Tablica robocza dla permutacji
    int idx = 0;
    
    // Zbieramy wszystkie miasta OPROCZ startowego (bo start zawsze jest na poczatku i koncu)
    for (unsigned i = 0; i < n; i++) {
        if (i != start) {
            path[idx] = i;
            idx++;
        }
    }
    
    unsigned minCost = 999999;
    Tour<unsigned> bestTour;
    
    // Uruchomienie maszyny permutacyjnej od pierwszego indeksu (0)
    generatePermutations(0, idx, path, minCost, bestTour, g, start);
    
    return bestTour;
}