#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

int M, N; // M parte izquierda, N parte derecha
vector<vector<int>> grafo;
vector<int> match, vis;

int aug(int l) { // devuelve 1 si encuentra un augmenting path para el matching M representado en match
    if (vis[l]) return 0;
    vis[l] = 1;
    for (int r : grafo[l]) {
        if (match[r] == -1 || aug(match[r])) {
            match[r] = l;
            return 1;
        }
    }
    return 0;
}

int berge_mcbm() {
    int mcbm = 0;
    match.assign(N + M, -1);
    for (int l = 0; l < N; ++l) {
        vis.assign(N, 0);
        mcbm += aug(l);
    }
    return mcbm;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    double velocidad; // m/s
    int segundos; //segundos
    grafo.clear();
    cin >> N >> M >> segundos >> velocidad;
    if(!std::cin)
		return false;

	grafo.assign(N, vector<int>());

	vector<pair<double, double>> gophers(N), holes(M);
	for (int i = 0; i < N; ++i) {
		cin >> gophers[i].first >> gophers[i].second;
	}
	for (int i = 0; i < M; ++i) {
		cin >> holes[i].first >> holes[i].second;
	}

	//inicializo la lista de adyacencia si puede llegar a tiempo
    for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			double dist = sqrt(pow(gophers[i].first - holes[j].first, 2) + pow(gophers[i].second - holes[j].second, 2));
			if (dist / velocidad <= segundos) {
				grafo[i].push_back(j);
			}
		}
	}

	cout << N - berge_mcbm() << '\n';

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
