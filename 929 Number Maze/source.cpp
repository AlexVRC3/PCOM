#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
#include <fstream>

using namespace std;

const int INF = INT_MAX;
const int dx[] = { -1, 1, 0, 0 }; //movimientos
const int dy[] = { 0, 0, -1, 1 };

using vi = vector<int>;
using vvi = vector<vi>;
vvi adjList;

struct celda {
    int x, y, coste;
    bool operator>(const celda& other) const {
        return coste > other.coste; 
    }
};

int dijkstra(const vector<vector<int>>& matriz, int N, int M, vvi &dist) {
    priority_queue<celda, vector<celda>, greater<celda>> pq; 

    dist[0][0] = matriz[0][0];
    pq.push({ 0, 0, matriz[0][0] });

    while (!pq.empty()) {
        celda actual = pq.top();
        pq.pop();

        int x = actual.x, y = actual.y, coste = actual.coste;

        if (x == N - 1 && y == M - 1) { // final
            return coste;
        }

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && ny >= 0 && nx < N && ny < M) { // pos correcta
                int nuevo_coste = coste + matriz[nx][ny];
                if (nuevo_coste < dist[nx][ny]) {
                    dist[nx][ny] = nuevo_coste;
                    pq.push({ nx, ny, nuevo_coste });
                }
            }
        }
    }
}

int main() {

    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    int t;
    cin >> t; 

    while (t--) {
        int N, M;
        cin >> N >> M; 
        vvi matriz(N, vi(M));

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                cin >> matriz[i][j];
            }
        }
        vvi dist(N, vi(M, INF));
        cout << dijkstra(matriz, N, M, dist) << endl;
    }

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
