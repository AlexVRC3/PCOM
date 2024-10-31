#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstring>

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
vvi adj;
const int MAX_V = 100;
int hora, V;
int horaVertice[MAX_V];
int alcanzable[MAX_V];
int hijosRaiz;
int numArticulados;
bool esArticulado[MAX_V];

void dfs(int u, int uParent) {
    horaVertice[u] = alcanzable[u] = hora++;
    for (int v : adj[u]) {
        if (v == uParent) continue;
        if (horaVertice[v] == 0) {
            if (uParent == 0) hijosRaiz++;
            dfs(v, u);
            if (alcanzable[v] >= horaVertice[u] && uParent != 0 && !esArticulado[u]) {
                esArticulado[u] = true;
                numArticulados++;
            }
            alcanzable[u] = min(alcanzable[u], alcanzable[v]);
        }
        else {
            alcanzable[u] = min(alcanzable[u], horaVertice[v]);
        }
    }
}

bool resuelveCaso() {
    cin >> V;

    if (V == 0) return false;

    adj.assign(V + 1, vi());
    memset(horaVertice, 0, sizeof(horaVertice));
    memset(esArticulado, false, sizeof(esArticulado));

    string linea;
    int origen;
    cin >> origen;

    while (origen != 0) {
        getline(cin, linea);
        stringstream ss(linea);
        int destino;
        while (ss >> destino) {
            adj[origen].push_back(destino);
            adj[destino].push_back(origen);
        }
        cin >> origen;
    }

    hora = 1;
    numArticulados = 0;

    for (int i = 1; i <= V; ++i) {
        if (horaVertice[i] == 0) {
            hijosRaiz = 0;
            dfs(i, 0);
            if (hijosRaiz > 1) {
                esArticulado[i] = true;
                numArticulados++;
            }
        }
    }

    cout << numArticulados << endl;

    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}
