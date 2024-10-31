#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>
#include <climits>
#include <vector>

using namespace std;

using vi = vector<int>;
using ii = pair<int, int>; //arista
using vii = vector<ii>; //lista de aristas
using vvi = vector<vi>;
vector<vii> adjList;

void dijkstra(int s, vi& dist) {
    dist.assign(adjList.size(), INT_MAX);
    dist[s] = 0;
    priority_queue<ii, vii, greater<ii>> pq;
    pq.push({ 0, s });

    while (!pq.empty()) {
        ii front = pq.top(); pq.pop();
        int d = front.first, u = front.second;
        if (d > dist[u]) continue;

        for (auto a : adjList[u]) {
            if (dist[u] + a.first < dist[a.second]) {
                dist[a.second] = dist[u] + a.first;
                pq.push({ dist[a.second], a.second });
            }
        }
    }
}

bool resuelveCaso() {
    int N, S, T, P;
    cin >> N >> S >> T >> P;

    if (!std::cin)  // fin de la entrada
        return false;

    adjList.assign(N, {});

    int v, w, val;
    for (int i = 0; i < P; i++) {
        cin >> v >> w >> val;
        adjList[w - 1].push_back({ val, v - 1 });
    }

    int ratones = 0;
    vi dist;
    dijkstra(S - 1, dist);
    for (int i = 0; i < N; i++)
    {
        if (dist[i] <= T)
            ratones++;
    }

    cout << ratones - 1 << "\n";

    return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
