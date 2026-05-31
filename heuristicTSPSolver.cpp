#include "heuristicTSPSolver.h"
#include "myexceptions.h"
#include <vector>
#include <algorithm>

// Struktura pomocnicza dla krawędzi używana w metodzie Smallest Edge
struct Edge {
    unsigned u, v, weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

// 1. KONSTRUKTOR (To jego brakowało linkerowi!)
HeuristicTSPSolver::HeuristicTSPSolver(int type) : algType(type) {
    if (type != 0 && type != 1) {
        throw MyExceptions("Blad algorytmu: Nieprawidlowy typ heurystyki!");
    }
}

// 2. GŁÓWNA FUNKCJA STERUJĄCA SOLVERA
Tour<unsigned> HeuristicTSPSolver::solve(const DistanceGraph& g, unsigned start) {
    if (start >= g.size()) {
        throw MyExceptions("Blad algorytmu: Niepoprawne miasto startowe!");
    }
    
    if (algType == 0) {
        return solveNN(g, start);
    } else {
        return solveSE(g, start);
    }
}

// 3. METODA 0: NAJBLIŻSZY SĄSIAD (NN)
Tour<unsigned> HeuristicTSPSolver::solveNN(const DistanceGraph& g, unsigned start) {
    unsigned n = g.size();
    std::vector<bool> visited(n, false);
    Tour<unsigned> tour;

    unsigned current = start;
    tour.addCity(current);
    visited[current] = true;

    for (unsigned step = 1; step < n; ++step) {
        unsigned nextCity = -1;
        unsigned minDst = -1; // Maksymalna wartość dla unsigned

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
    tour.addCity(start); // Powrót do miasta startowego
    return tour;
}

// 4. METODA 1: NAJMNIEJSZA KRAWĘDŹ (SE)
Tour<unsigned> HeuristicTSPSolver::solveSE(const DistanceGraph& g, unsigned start) {
    unsigned n = g.size();
    std::vector<Edge> edges;

    // Zbierz wszystkie unikalne krawędzie z grafu
    for (unsigned i = 0; i < n; ++i) {
        for (unsigned j = i + 1; j < n; ++j) {
            edges.push_back({i, j, g.distance(i, j)});
        }
    }

    // Posortuj krawędzie od najkrótszej
    std::sort(edges.begin(), edges.end());

    std::vector<unsigned> degrees(n, 0);
    std::vector<std::vector<unsigned>> adj(n); // lista sąsiedztwa budowanego cyklu
    unsigned edgesCount = 0;

    // Funkcja pomocnicza lambda (DFS) do sprawdzania, czy powstanie przedwczesny cykl
    auto introducesPrematureCycle = [&](unsigned u, unsigned v) {
        if (adj[u].empty() || adj[v].empty()) return false;
        std::vector<bool> visited(n, false);
        std::vector<unsigned> q;
        q.push_back(u);
        visited[u] = true;
        
        while(!q.empty()) {
            unsigned curr = q.back();
            q.pop_back();
            for(unsigned neighbor : adj[curr]) {
                if(neighbor == v) return true;
                if(!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push_back(neighbor);
                }
            }
        }
        return false;
    };

    // Zachłanne dobieranie krawędzi zgodnie z zasadami stopnia i cyklu
    for (const auto& edge : edges) {
        if (edgesCount == n) break;

        // Warunek 1: Stopień wierzchołków musi być mniejszy niż 2
        if (degrees[edge.u] < 2 && degrees[edge.v] < 2) {
            // Warunek 2: Blokada przedwczesnego cyklu (chyba że to ostatnia krawędź)
            if (edgesCount < n - 1 && introducesPrematureCycle(edge.u, edge.v)) {
                continue; 
            }

            // Dodaj krawędź do rozwiązania
            adj[edge.u].push_back(edge.v);
            adj[edge.v].push_back(edge.u);
            degrees[edge.u]++;
            degrees[edge.v]++;
            edgesCount++;
        }
    }

    // Odtwórz trasę jako sekwencję miast, zaczynając od punktu 'start'
    Tour<unsigned> tour;
    std::vector<bool> inTour(n, false);
    unsigned curr = start;
    tour.addCity(curr);
    inTour[curr] = true;

    for (unsigned i = 0; i < n - 1; ++i) {
        unsigned nextCity = curr;
        for (unsigned neighbor : adj[curr]) {
            if (!inTour[neighbor]) {
                nextCity = neighbor;
                break;
            }
        }
        curr = nextCity;
        tour.addCity(curr);
        inTour[curr] = true;
    }
    tour.addCity(start); // Powrót do miasta początkowego

    return tour;
}