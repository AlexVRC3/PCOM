#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

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

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int a, b;

    int refusals = 0; 
    vector<pair<int, int>> v;
    int maxV = 0;

    // leer los datos de la entrada
    cin >> a;
    if (!cin || a == -1) return false;

    while (a != -1) {
        cin >> b;
		maxV = max(maxV, max(a, b));
		v.push_back({ a, b });
        cin >> a;
    }
    UFDS uf(maxV + 1);
	for (int i = 0; i < v.size(); i++) {
		if (uf.find(v[i].first) == uf.find(v[i].second)) {
			refusals++;
		}
		else {
			uf.merge(v[i].first, v[i].second);
		}
	}
    cout << refusals << endl;

    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 

    while (resuelveCaso());

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}
