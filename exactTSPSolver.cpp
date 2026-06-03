#include "heuristicTSPSolver.h"
#include "myexceptions.h"
#include <vector>

HeuristicTSPSolver::HeuristicTSPSolver(int type) {
    if (type != 0 && type != 1) throw MyExceptions("Blad: Zly typ algorytmu");
    algType = type;
}

Tour<unsigned> HeuristicTSPSolver::solve(const DistanceGraph& g, unsigned start) {
    if (start >= g.size()) throw MyExceptions("Blad: Zly start");
    
    if (algType == 0) return solveNN(g, start);
    else return solveSE(g, start);
}

// ==========================================
// METODA 0: Najblizszy Sasiad
// ==========================================
Tour<unsigned> HeuristicTSPSolver::solveNN(const DistanceGraph& g, unsigned start) {
    unsigned n = g.size();
    bool visited[20] = {false};
    Tour<unsigned> tour;
    
    unsigned current = start;
    tour.addCity(current);
    visited[current] = true;
    
    for (unsigned step = 1; step < n; step++) {
        unsigned nextCity = 0;
        unsigned minDst = 999999;
        
        for (unsigned j = 0; j < n; j++) {
            if (!visited[j] && g.distance(current, j) < minDst) {
                minDst = g.distance(current, j);
                nextCity = j;
            }
        }
        
        current = nextCity;
        tour.addCity(current);
        visited[current] = true;
    }
    tour.addCity(start);
    return tour;
}

// ==========================================
// METODA 1: Smallest Edge (Najmniejsza Krawedz)
// ==========================================
struct SimpleEdge {
    unsigned u, v, weight;
};

// Klasyczna funkcja sprawdzajaca wczesny cykl na tablicach
bool checkCycle(unsigned startNode, unsigned targetNode, unsigned n, unsigned adj[20][20]) {
    bool visited[20] = {false};
    unsigned q[20];
    int head = 0, tail = 0;
    
    q[tail++] = startNode;
    visited[startNode] = true;
    
    while (head < tail) {
        unsigned curr = q[head++];
        for (unsigned i = 0; i < n; i++) {
            if (adj[curr][i] == 1 && !visited[i]) {
                if (i == targetNode) return true; // Powstanie kolko
                visited[i] = true;
                q[tail++] = i;
            }
        }
    }
    return false;
}

Tour<unsigned> HeuristicTSPSolver::solveSE(const DistanceGraph& g, unsigned start) {
    unsigned n = g.size();
    std::vector<SimpleEdge> edges;
    
    for (unsigned i = 0; i < n; i++) {
        for (unsigned j = i + 1; j < n; j++) {
            SimpleEdge e;
            e.u = i; e.v = j; e.weight = g.distance(i, j);
            edges.push_back(e);
        }
    }
    
    // Proste sortowanie babelkowe 
    for (unsigned i = 0; i < edges.size(); i++) {
        for (unsigned j = 0; j < edges.size() - 1; j++) {
            if (edges[j].weight > edges[j+1].weight) {
                SimpleEdge temp = edges[j];
                edges[j] = edges[j+1];
                edges[j+1] = temp;
            }
        }
    }
    
    unsigned degrees[20] = {0};
    unsigned adj[20][20] = {0}; 
    unsigned edgesCount = 0;
    
    for (unsigned i = 0; i < edges.size(); i++) {
        if (edgesCount == n) break;
        unsigned u = edges[i].u;
        unsigned v = edges[i].v;
        
        if (degrees[u] < 2 && degrees[v] < 2) {
            if (edgesCount < n - 1 && checkCycle(u, v, n, adj)) {
                continue;
            }
            adj[u][v] = 1;
            adj[v][u] = 1;
            degrees[u]++;
            degrees[v]++;
            edgesCount++;
        }
    }
    
    // Budowa ostatecznej trasy
    Tour<unsigned> tour;
    bool inTour[20] = {false};
    unsigned curr = start;
    tour.addCity(curr);
    inTour[curr] = true;
    
    for (unsigned i = 0; i < n - 1; i++) {
        unsigned nextCity = curr;
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
    tour.addCity(start);
    
    return tour;
}