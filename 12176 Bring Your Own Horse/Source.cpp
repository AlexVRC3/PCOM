//#include <iostream>
//#include <iomanip>
//#include <fstream>
//#include <queue>
//#include <climits>
//#include <vector>
//
//using namespace std;
//
//const int INF = INT_MAX;
//
//using vi = vector<int>;
//using ii = pair<int, int>; // Vertice + valor
//using vii = vector<ii>;
//vector<vii> adjList;
//
//// Algoritmo de Dijkstra modificado
//void dijkstra(int s, vi& dist) {
//    dist.assign(adjList.size(), INF);
//    dist[s] = 0;
//    priority_queue<ii, vii, greater<ii>> pq;
//    pq.push({ 0, s });
//    while (!pq.empty()) {
//        ii front = pq.top(); pq.pop();
//        int d = front.first, u = front.second;
//        if (d > dist[u]) continue;
//        for (auto a : adjList[u]) {
//            int aristaMax = max(dist[u], a.first);
//            if (dist[a.second] > aristaMax) { // descansa entre dias no hace falta suma de distancias
//                dist[a.second] = aristaMax;
//                pq.push({ dist[a.second], a.second });
//            }
//        }
//    }
//}
//
//void resuelveCaso() {
//    int N, R;
//    cin >> N >> R;
//    int u, v, c;
//    adjList.assign(N, {});
//    for (int i = 0; i < R; i++) {
//        cin >> u >> v >> c;
//        adjList[u - 1].push_back({ c, v - 1 });
//        adjList[v - 1].push_back({ c, u - 1 });
//    }
//    int Q;
//    cin >> Q;
//    int s, t;
//    vi dist(N);
//    for (int i = 0; i < Q; i++) {
//        cin >> s >> t;
//        dijkstra(s - 1, dist);
//        cout << dist[t - 1] << '\n';
//    }
//    cout << '\n';
//}
//
//int main() {
//    // ajustes para que cin extraiga directamente de un fichero
//#ifndef DOMJUDGE
//    std::ifstream in("datos.txt");
//    auto cinbuf = std::cin.rdbuf(in.rdbuf());
//#endif
//
//    int nCasos;
//    cin >> nCasos;
//    for (int i = 0; i < nCasos; i++) {
//		cout << "Case " << i + 1 << '\n';
//        resuelveCaso();
//    }
//
//    // para dejar todo como estaba al principio
//#ifndef DOMJUDGE
//    std::cin.rdbuf(cinbuf);
//    system("PAUSE");
//#endif
//    return 0;
//}

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
using arista = pair<int, pair<int, int>>; // <coste, extremos> 

struct UFDS {
    vector<int> p;
    int numSets;
    UFDS(int n) : p(n, 0), numSets(n) {
        for (int i = 0; i < n; ++i) p[i] = i;
    }
    int find(int x) {
        return (p[x] == x) ? x : p[x] = find(p[x]);
    }
    void merge(int x, int y) {
        int i = find(x), j = find(y);
        if (i == j) return;
        p[i] = j;
        --numSets;
    }
};

void resuelveCaso() {
    int n, m;
    cin >> n >> m;
    vector<arista> aristas;

    int u, v, c;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> c;
        aristas.push_back({ c, { u - 1, v - 1 } });
    }

    sort(aristas.begin(), aristas.end());

    int Q;
    cin >> Q;
    for (int q = 0; q < Q; ++q) {
        int s, t;
        cin >> s >> t;
        s--; t--;

        UFDS uf(n);
        int valorArista = -1;

        for (const auto& ar : aristas) {
            int cost = ar.first;
            int u = ar.second.first;
            int v = ar.second.second;

            if (uf.find(u) != uf.find(v)) {
                uf.merge(u, v);
                valorArista = cost;

                if (uf.find(s) == uf.find(t)) {
                    break;
                }
            }
        }

        if (uf.find(s) == uf.find(t)) {
            cout << valorArista << endl;
        }
    }
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int nCasos;
    cin >> nCasos;
    for (int i = 0; i < nCasos; i++) {
        cout << "Case " << i + 1 << endl;
        resuelveCaso();
        cout << '\n';
    }

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}