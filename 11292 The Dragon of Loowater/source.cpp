#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int resolver(vector<int>& cabezas, vector<int>& caballeros) {
    sort(cabezas.begin(), cabezas.end());
    sort(caballeros.begin(), caballeros.end());

    int n = cabezas.size();
    int m = caballeros.size();
    int numMonedas = 0;
    int idx_caballeros = 0;

    for (int i = 0; i < n; i++) {
        
        while (idx_caballeros < m && caballeros[idx_caballeros] < cabezas[i]) {
            idx_caballeros++;
        }

        if (idx_caballeros == m) {
            return -1;  // no hay sol
        }

        numMonedas += caballeros[idx_caballeros];
        idx_caballeros++;
    }

    return numMonedas;
}

bool resuelveCaso() {
    int n, m;
    cin >> n >> m;
    if (n == 0 && m == 0)
        return false;

    vector<int> cabezas(n);
    vector<int> caballeros(m);

    for (int i = 0; i < n; i++) {
        cin >> cabezas[i];
    }

    for (int i = 0; i < m; i++) {
        cin >> caballeros[i];
    }

    int sol = resolver(cabezas, caballeros);

    if (sol == -1) {
        cout << "Loowater is doomed!" << endl;
    }
    else {
        cout << sol << endl;
    }

    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to file
#endif 

    while (resuelveCaso());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}
