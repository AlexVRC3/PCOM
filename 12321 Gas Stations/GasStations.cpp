#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct {
    int ini;
    int fin;
}tGasolina;

bool operator<(tGasolina const& a, tGasolina const& b) {
    return a.ini < b.ini || (a.ini == b.ini && a.fin > b.fin);
}

int numGasolineras(vector<tGasolina>& g, int L) {
    sort(g.begin(), g.end());

    int pasadizos = 0;
    int it = 0;
    int gasActual = 0;
    while (it < L) {

        int maxL = it;

        while (gasActual < g.size() && g[gasActual].ini <= it) {
            maxL = max(maxL, g[gasActual].fin);//puede ser que un limite a la derecha sea mayor que el otro
            gasActual++;
        }
        pasadizos++;

        if (maxL == it) {
            pasadizos = -1;
            break;
        }

        it = maxL;
    }
    
    if (it < L) {
        pasadizos = -1;
    }

    return pasadizos;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int L, G; cin >> L >> G;

    if (L == 0 && G == 0)
        return false;

    int x, r;
    vector<tGasolina> g(G);
    for (int i = 0; i < G; i++) {
        cin >> x >> r;
        if (x - r < 0)
            g[i] = { 0, x + r };
        else if (x + r > L)
            g[i] = { x - r, L };
        else
            g[i] = { x - r, x + r };
    }

    int res = numGasolineras(g, L);
    if (res == -1)
        cout << res;
    else
        cout << G - res;
    cout << '\n';

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
