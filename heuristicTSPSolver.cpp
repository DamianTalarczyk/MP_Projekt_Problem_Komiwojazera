#include "heuristicTSPSolver.h"
#include "myexceptions.h"
#include <vector>

HeuristicTSPSolver::HeuristicTSPSolver(int type) {
    if (type != 0 && type != 1) throw MyExceptions("Blad: Zly typ algorytmu");
    algType = type;
}

Tour<unsigned> HeuristicTSPSolver::solve(const DistanceGraph& g, unsigned start) {
    if (start >= g.size()) throw MyExceptions("Blad: Zly start");
    
    /* Polimorficzny dystrybutor zadań przekierowuje wykonanie do wybranej metody 
    heurystycznej na podstawie parametru "algType" ustawionego w funkcji main*/
    if (algType == 0) return solveNN(g, start);
    else return solveSE(g, start);
}


/*  Metoda 0: Algorytm Najbliższego Sąsiada (Nearest Neighbor - NN)
    "lokalny" algorytm zachłanny: Startując z miasta początkowego, program w każdym kroku 
    analizuje odległości wyłącznie z obecnego miejsca i wybiera najbliższe, jeszcze nieodwiedzone miasto.
    Zaleta jest to że algorytm jest niezwykle szybki i prosty w implementacji.
    Wada jest to ze algorytm jest "krótkowzroczny" – nie analizuje globalnej mapy, przez co na samym końcu 
    trasy może zostać zmuszony do powrotu bardzo kosztowną krawedzia przez to
    ze nie moze przejsc dwa razy do tego samego miasta (wpada w pułapkę zachłanną). */
Tour<unsigned> HeuristicTSPSolver::solveNN(const DistanceGraph& g, unsigned start) {
    unsigned n = g.size();
    bool visited[20] = {false}; // Tablica pilnujaca, by nie odwiedzic miasta dwa razy
    Tour<unsigned> tour;
    
    unsigned current = start;
    tour.addCity(current);
    visited[current] = true;
    
    // Petla szukajaca n-1 pozostalych miast
    for (unsigned step = 1; step < n; step++) {
        unsigned nextCity = 0;
        unsigned minDst = 999999;
        
        // Przegladamy mapę w poszukiwaniu najkrotszej drogi
        for (unsigned j = 0; j < n; j++) {
            // Jesli tam nie bylismy (!visited) oraz dystans jest mniejszy niz dotychczasowy rekord
            if (!visited[j] && g.distance(current, j) < minDst) {
                minDst = g.distance(current, j);
                nextCity = j;
            }
        }
        
        // Przechodzimy do znalezionego, najblizszego miasta
        current = nextCity;
        tour.addCity(current);
        visited[current] = true;
    }
    tour.addCity(start); // Powrot do bazy na koniec
    return tour;
}

/* Metoda 1: Algorytm Najmniejszej Krawędzi (Smallest Edge - SE)
   "Globalny" algorytm zachłanny: W przeciwieństwie do NN, ten algorytm nie buduje trasy liniowo "od miasta do miasta".
   Analizuje on od razu całą mapę, wybierając krawędzie od absolutnie najtańszej do najdroższej.
   Aby powstała poprawna, pojedyncza pętla zamknięta (cykl Hamiltona), musimy pilnować dwóch reguł:
   1. Stopień wierzchołka: Z żadnego miasta nie mogą wychodzić więcej niż 2 krawędzie.
   2. Spójność grafu: Wybrana krawędź nie może zamknąć małego, izolowanego podcyklu (kółka) przed odwiedzeniem wszystkich miast. */


// Struktura pomocnicza reprezentujaca jedno polaczenie (krawedz)
struct SimpleEdge {
    unsigned u, v, weight;
};

/* Algorytm przeszukiwania grafu wszerz (BFS - Breadth-First Search) do wykrywania cykli.
   Funkcja sprawdza, czy pomiędzy miastami 'startNode' a 'targetNode' istnieje już alternatywna ścieżka 
   utworzona przez wcześniej zaakceptowane drogi. Jeśli tak, dodanie bezpośredniej krawędzi między nimi 
   spowodowałoby przedwczesne zamknięcie mniejszego cyklu, co zepsułoby trasę komiwojażera. */
bool checkCycle(unsigned startNode, unsigned targetNode, unsigned n, unsigned adj[20][20]) {
    bool visited[20] = {false};
    unsigned q[20]; // Prosta kolejka uzywana do przejscia grafu
    int head = 0, tail = 0;
    
    q[tail++] = startNode;
    visited[startNode] = true;
    
    while (head < tail) {
        unsigned curr = q[head++];
        for (unsigned i = 0; i < n; i++) {
            // Jesli istnieje zaakceptowana sciezka z obecnego i w niej nie bylismy
            if (adj[curr][i] == 1 && !visited[i]) {
                if (i == targetNode) return true; // Wykryto istniejące połączenie - dodanie krawędzi grozi zamknieciem cyklu.
                visited[i] = true;
                q[tail++] = i;
            }
        }
    }
    return false; // Drogi są odseparowane można bezpiecznie połączyć miasta.
}

Tour<unsigned> HeuristicTSPSolver::solveSE(const DistanceGraph& g, unsigned start) {
    unsigned n = g.size();
    std::vector<SimpleEdge> edges;
    
    // Zbieramy wszystkie drogi do "worka"
    for (unsigned i = 0; i < n; i++) {
        for (unsigned j = i + 1; j < n; j++) {
            SimpleEdge e;
            e.u = i; e.v = j; e.weight = g.distance(i, j);
            edges.push_back(e);
        }
    }
    
    /* Sortowanie bąbelkowe (Bubble Sort): Układamy krawędzie rosnąco według wag.
    Jest to fundamentalny krok heurystyki SE – musimy posortować dane, aby móc w kolejnym 
    kroku zachłannie wybierać krawędzie zaczynając od tych o najniższym koszcie.*/
    for (unsigned i = 0; i < edges.size(); i++) {
        for (unsigned j = 0; j < edges.size() - 1; j++) {
            if (edges[j].weight > edges[j+1].weight) {
                SimpleEdge temp = edges[j];
                edges[j] = edges[j+1];
                edges[j+1] = temp;
            }
        }
    }
    
    unsigned degrees[20] = {0}; // Zlicza drogi dopiete do konkretnego miasta
    unsigned adj[20][20] = {0}; // Tablica zapisujaca wylacznie zaakceptowane drogi
    unsigned edgesCount = 0;
    
    // Idziemy po krawedziach od najtanszej do najdrozszej
    for (unsigned i = 0; i < edges.size(); i++) {
        if (edgesCount == n) break; // Skoncz, jesli narysowalismy n drog (pelny cykl)
        
        unsigned u = edges[i].u;
        unsigned v = edges[i].v;
        
        // Zasada 1: Zaden wierzcholek nie moze miec stopnia wiekszego niz 2
        if (degrees[u] < 2 && degrees[v] < 2) {
            
            // Zasada 2: Brak przedwczesnych mniejszych cykli
            // Jesli nie rysujemy wlasnie ostatniej krawedzi, sprawdz czy nie zrobimy kolka
            if (edgesCount < n - 1 && checkCycle(u, v, n, adj)) {
                continue; // Odstaz ta droge, szukaj nastepnej
            }
            
            // Akceptacja krawedzi (jest bezpieczna i najtansza)
            adj[u][v] = 1;
            adj[v][u] = 1;
            degrees[u]++;
            degrees[v]++;
            edgesCount++;
        }
    }
    
    // Z budowli drogowej (adj) otwarzamy sekwencje przejazdu dla Dziennika Trasy (Tour)
    Tour<unsigned> tour;
    bool inTour[20] = {false};
    unsigned curr = start;
    tour.addCity(curr);
    inTour[curr] = true;
    
    for (unsigned i = 0; i < n - 1; i++) {
        unsigned nextCity = curr;
        // Znajdz miasto, do ktorego narysowalismy droge i do ktorego mozemy wejsc
        for (unsigned neighbor = 0; neighbor < n; neighbor++) {
            if (adj[curr][neighbor] == 1 && !inTour[neighbor]) {
                nextCity = neighbor;
                break;
            }
        }
        curr = nextCity;
        tour.addCity(curr);
        inTour[curr] = true;
    }
    tour.addCity(start); // Powrot
    
    return tour;
}