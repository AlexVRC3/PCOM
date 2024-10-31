#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int V; // número total de vértices (karel + beepers)
vector<vector<int>> dist; // matriz de adyacencia del grafo (distancias)
vector<vector<int>> memo; // tabla de DP

int tsp(int pos, int visitados) {
    if (visitados == (1 << V) - 1) // si todos los vértices han sido visitados
        return dist[pos][0]; // regresar al origen

    if (memo[pos][visitados] != -1)
        return memo[pos][visitados]; // devolver el resultado memoizado

    int res = 1000000000; // INF

    // probar todas las posibilidades
    for (int i = 1; i < V; ++i) {
        if (!(visitados & (1 << i))) // si el vértice i no ha sido visitado
            res = min(res, dist[pos][i] + tsp(i, visitados | (1 << i)));
    }

    return memo[pos][visitados] = res;
}

// Resuelve un caso de prueba
void resuelveCaso() {
    int x, y;
    cin >> x >> y;

    int karel_x, karel_y;
    cin >> karel_x >> karel_y;

    int nBeepers;
    cin >> nBeepers;

    vector<pair<int, int>> beepers;

    beepers.push_back({ karel_x, karel_y });

    for (int i = 0; i < nBeepers; i++) {
        int z, w;
        cin >> z >> w;
        beepers.push_back({ z, w });
    }

    V = nBeepers + 1;

    dist.assign(V, vector<int>(V, 0));

    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            dist[i][j] = abs(beepers[i].first - beepers[j].first) + abs(beepers[i].second - beepers[j].second);
        }
    }

    // Inicializar la tabla de memoización
    memo.assign(V, vector<int>(1 << V, -1));

    cout << "The shortest path has length " << tsp(0, 1) << '\n';
}

int main() {
    // Para la entrada por fichero (comentar para acepta el reto)
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); // redirigir cin a fichero
#endif 

    int numCasos;
    cin >> numCasos; // leer el número de casos
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // Para restablecer entrada (comentar para acepta el reto)
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}
