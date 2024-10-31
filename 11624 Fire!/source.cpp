#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

const int MAX_SIZE = 1001;
char matriz[MAX_SIZE][MAX_SIZE];

vector<pair<int, int>> movimientos = { {1,0}, {-1,0}, {0,1}, {0,-1} };

bool invalida(pair<int, int> pos, int x, int y) {
    return pos.first < 0 || pos.first >= x || pos.second < 0 || pos.second >= y;
}

int bfs(pair<int, int> J, const vector<pair<int, int>>& F, int x, int y) {
    queue<pair<pair<int, int>, int>> cola;

    for (auto f : F) {
        cola.push({ f, -1 });
    }
    cola.push({ J, 0 });

    while (!cola.empty()) {
        auto actual = cola.front();
        cola.pop();
        auto pos = actual.first;
        int recorrido = actual.second;

        if (matriz[pos.first][pos.second] == 'F') {
            for (const auto& mov : movimientos) {
                pair<int, int> sig = { pos.first + mov.first, pos.second + mov.second };
                if (!invalida(sig, x, y) && matriz[sig.first][sig.second] == '.') {
                    matriz[sig.first][sig.second] = 'F';
                    cola.push({ sig, -1 });
                }
            }
        }
        else {
            if (matriz[pos.first][pos.second] == 'F') continue;
            for (const auto& mov : movimientos) {
                pair<int, int> sig = { pos.first + mov.first, pos.second + mov.second };
                if (invalida(sig, x, y)) return recorrido + 1;
                if (matriz[sig.first][sig.second] == '.' || matriz[sig.first][sig.second] == 'J') {
                    matriz[sig.first][sig.second] = '#';
                    cola.push({ sig, recorrido + 1 });
                }
            }
        }
    }
    return -1;
}

void resuelveCaso() {
    int x, y;
    cin >> x >> y;

    pair<int, int> posJ;
    vector<pair<int, int>> posF;

    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            cin >> matriz[i][j];
            if (matriz[i][j] == 'J') {
                posJ = { i, j };
            }
            else if (matriz[i][j] == 'F') {
                posF.push_back({ i, j });
            }
        }
    }

    int sol = bfs(posJ, posF, x, y);
    if (sol == -1) {
        cout << "IMPOSSIBLE\n";
    }
    else {
        cout << sol << "\n";
    }
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int numCasos;
    cin >> numCasos;
    for (int i = 0; i < numCasos; ++i) {
        resuelveCaso();
    }

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}
