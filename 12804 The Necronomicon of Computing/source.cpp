#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
vvi adj;

vector<bool> visit;
vector<bool> enExploracion;
bool hayCiclo = false;

void answer() {

    if (hayCiclo && visit[visit.size() - 1])
        cout << "SOMETIMES" << endl;
    else if (hayCiclo || !visit[visit.size() - 1])
        cout << "NEVER" << endl;
    else
        cout << "ALWAYS" << endl;
}


void dfs(int u) {
    enExploracion[u] = true;
    visit[u] = true;

    for (int v : adj[u]) {
        if (!visit[v])
            dfs(v);
        else if (enExploracion[v])
            hayCiclo = true;
    }
    enExploracion[u] = false;
}

void resuelveCaso() {
    int L;
    cin >> L;

    adj.assign(L + 1, vi());

    for (int i = 0; i < L; i++) {
        char I;
        cin >> I;

        switch (I) {
        case 'A':
            adj[i].push_back(i + 1);
            break;

        case 'J': {
            int n;
            cin >> n;
            adj[i].push_back(n - 1);
            break;
        }

        case 'C': {
            int n;
            cin >> n;
            adj[i].push_back(n - 1);
            adj[i].push_back(i + 1);
            break;
        }
        }
    }

    enExploracion.assign(L + 1, false);
    visit.assign(L + 1, false);
    hayCiclo = false;

    dfs(0);

    answer();
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int numCasos;
    cin >> numCasos;
    for (int i = 0; i < numCasos; i++)
    {
        resuelveCaso();
    }

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}

