#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

const int INF = 100000;

int V;
vector<vector<int>> dist; // matriz de adyacencia del grafo
vector<vector<int>> memo; // tabla de DP

// Otra Estructura (Dijkstra) de Lista de Adyacentes (contiene vertices adyacentes + valor arista)
using vi = vector<int>;		// Vector Enteros para distancias : Dijkstra
using ii = pair<int, int>; // Vertice + valor
using vii = vector<ii>;
vector<vii> adjList2;


// devuelve el coste de ir desde pos al origen (el vértice 0)
// pasando por todos los vértices no visitados (con un bit a 0)
int tsp(int pos, int visitados) {
    if (visitados == (1 << V) - 1) // hemos visitado ya todos los vértices
        return dist[pos][0]; // volvemos al origen

    if (memo[pos][visitados] != -1)
        return memo[pos][visitados];

    int res = 1000000000; // INF

    for (int i = 1; i < V; ++i)
        if (!(visitados & (1 << i))) // no hemos visitado vértice i
            res = min(res, dist[pos][i] + tsp(i, visitados | (1 << i)));

    return memo[pos][visitados] = res;
}


// Algoritmo de Dijkstra

void Dijkstra(int s, vi& dist) {
    dist.assign(adjList2.size(), INF);
    dist[s] = 0;
    priority_queue<ii, vii, greater<ii>> pq;
    pq.push({ 0, s });
    while (!pq.empty()) {
        ii front = pq.top(); pq.pop();
        int d = front.first, u = front.second;
        if (d > dist[u]) continue;
        for (auto a : adjList2[u]) {
            if (dist[u] + a.first < dist[a.second]) {
                dist[a.second] = dist[u] + a.first;
                pq.push({ dist[a.second], a.second });
            }
        }
    }
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    
    int N, M; cin >> N >> M;
    V = N;
    int x, y, d;

    adjList2.assign(V, {});

    for (int i = 0; i < M; i++) {
        cin >> x >> y >> d;

        adjList2[x].push_back({ d,y });
        adjList2[y].push_back({ d,x });
    }

    

    int S; cin >> S;
    dist.assign(S+1, vector<int>(S+1, 0));
    int s;
    vector<int> vertices(S + 1);
    vertices[0] = 0;
    for (int i = 1; i < S + 1; i++) {
        cin >> s;
        vertices[i] = s;
    }

    vector<int> distDijstra(V);

    for (int i = 0; i < S + 1; i++) {

        Dijkstra(vertices[i], distDijstra);
        for (int j = 0; j < S + 1; j++) {
            dist[i][j] = distDijstra[vertices[j]];
        }
    }
    V = S + 1;
    memo.assign(V, vector<int>(1 << V, -1));

    // escribir sol
    cout << tsp(0, 1) << endl;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}