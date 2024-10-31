#include <vector>
#include <queue>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

const int MAX = 10000;	// Antes de recoger el numero de vertices, para inicializar nuestras estructuras

// Estructura para Lista de Adyacencias
using vi = vector<int>;
using vvi = vector<vi>;
vvi adjList;

vi dist;					// Vector donde se guardan las distancias del vector i al vector origen (para BFS)
vi visited;			// Estructura de visitados para ver que vertices se han visitado ya y cuales no

int maxSize;
int boomDay;
int V;

// BFS. Recorrido en Anchura :
void bfs(int s) {
    dist.assign(V, -1);
    visited.assign(V, false);

    maxSize = 0;
    boomDay = 0;
    int currentDay = 0;
    int size = 0;

    queue<int> q;
    dist[s] = 0; visited[s] = true;
    q.push(s);  
    while (!q.empty()) {
        int v = q.front(); q.pop();

        for (int w : adjList[v]) {
            if (!visited[w]) {
                dist[w] = dist[v] + 1;
                visited[w] = 1;
                q.push(w);
                
                if (dist[w] > currentDay) {
                    currentDay = dist[w];
                    size = 1;
                }
                else if (dist[w] == currentDay) {
                    size++;
                }

                if (size > maxSize) {
                    maxSize = size;
                    boomDay = dist[w];
                }
            }
        }
   }
}

bool resuelveCaso() {
    // leer los datos de la entrada

    cin >> V;

    if (!std::cin)
        return false;

    int a, b;
    adjList.resize(V);

    for (int i = 0; i < V; i++) {
        cin >> a;
        for (int j = 0; j < a; j++) {
            cin >> b;
            adjList[i].push_back(b);
        }
    }

    int t, s;
    cin >> t;

    dist.resize(V);
    visited.resize(V);

    for (int i = 0; i < t; i++) {
        cin >> s;
        bfs(s);

        if (boomDay != 0)
            cout << maxSize << ' ' << boomDay;
        else
            cout << 0;

        cout << endl;
    }


    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    while (resuelveCaso())
        ;


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}