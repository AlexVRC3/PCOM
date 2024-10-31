#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

const int MAX = 50;
int df[] = { 1,0,-1,0 }, dc[] = { 0,1,0,-1 };
bool visited[MAX][MAX];
char mapa[MAX][MAX];
int F, C;

/*
bool operator> (pair<char,int> const& a, pair<char, int> const& b) {
    return (a.second > b.second) || (a.second == b.second && a.first < b.first);
}*/

bool ok(int i, int j) {
    return 0 <= i && i < F && 0 <= j && j < C;
}

int dfs(int i, int j) {
    int tam = 1; visited[i][j] = true;
    for (int k = 0; k < 4; ++k) {
        int ni = i + df[k], nj = j + dc[k];
        if (ok(ni, nj) && mapa[ni][nj] == mapa[i][j] && !visited[ni][nj])
            tam += dfs(ni, nj);
    }
    return tam;
}

bool resuelveCaso(int& z) {
    cin >> F >> C;
    vector<pair<char, int>> sol(MAX * MAX);

    if (F == 0 && C == 0)
        return false;
    

    for (int i = 0; i < F; ++i) {
        for (int j = 0; j < C; ++j) {
            cin >> mapa[i][j];
            visited[i][j] = false;
        }
    }

    int numero = 0, tamaño = 0;
    for (int i = 0; i < F; ++i) {
        for (int j = 0; j < C; ++j) {
            if (!visited[i][j] && mapa[i][j] != '.') {
                tamaño = dfs(i, j);
                sol[numero] = { mapa[i][j] , tamaño };

                ++numero;
            }
        }
    }

    sol.resize(numero);

    sort(sol.begin(), sol.end(), [](pair<char, int> const& a, pair<char, int> const& b) {
        return (a.second > b.second) || (a.second == b.second && a.first < b.first);
    });


    z++;
    cout << "Problem " << z << ":" << endl;
    for (int i = 0; i < sol.size(); i++) {
        cout << sol[i].first << " " << sol[i].second << endl;
    }

    return true;

}

int main() {

#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 

    int z = 0;
    while (resuelveCaso(z));

#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}
