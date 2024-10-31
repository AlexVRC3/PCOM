#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <unordered_map>
#include <fstream>

using namespace std;

vector<vector<int>> adjList;
unordered_map<string, int> ciudad_idx; // ciudad e indice del vertice
vector<string> ciudades; // vector con nombre ciudad

bool bfs(int origen, int destino, vector<int>& predecesor) {
    queue<int> q;
    vector<bool> visitado(adjList.size(), false);

    q.push(origen);
    visitado[origen] = true;

    while (!q.empty()) {
        int actual = q.front();
        q.pop();

        if (actual == destino) {
            return true;
        }

        for (int adyacente : adjList[actual]) {
            if (!visitado[adyacente]) {
                visitado[adyacente] = true;
                predecesor[adyacente] = actual;
                q.push(adyacente);
            }
        }
    }
    return false;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 

    int numEnlaces;

    while (cin >> numEnlaces) {
        ciudad_idx.clear();
        ciudades.clear();
        adjList.clear();

        int numCiudades = 0;

        for (int i = 0; i < numEnlaces; i++) {
            string ciudad1, ciudad2;
            cin >> ciudad1 >> ciudad2;

            if (ciudad_idx.find(ciudad1) == ciudad_idx.end()) { // nuevos
                ciudad_idx[ciudad1] = numCiudades++;
                ciudades.push_back(ciudad1);
                adjList.push_back({});
            }
            if (ciudad_idx.find(ciudad2) == ciudad_idx.end()) { // nuevos
                ciudad_idx[ciudad2] = numCiudades++;
                ciudades.push_back(ciudad2);
                adjList.push_back({});
            }

            int idx1 = ciudad_idx[ciudad1];
            int idx2 = ciudad_idx[ciudad2];

            adjList[idx1].push_back(idx2);
            adjList[idx2].push_back(idx1);
        }

        string origen, destino;
        cin >> origen >> destino;

		if (ciudad_idx.find(origen) == ciudad_idx.end()) { // origen no tiene arista
			ciudad_idx[origen] = numCiudades++;
			ciudades.push_back(origen);
			adjList.push_back({});
		}
        if (ciudad_idx.find(origen) == ciudad_idx.end()) { // destino no tiene arista
            ciudad_idx[origen] = numCiudades++;
            ciudades.push_back(destino);
            adjList.push_back({});
        }

        if (ciudad_idx.find(destino) == ciudad_idx.end()) { // destino no tiene arista
            ciudad_idx[destino] = numCiudades++;
            ciudades.push_back(destino);
            adjList.push_back({});
        }

        vector<int> predecesor(numCiudades, -1);

        if (bfs(ciudad_idx[origen], ciudad_idx[destino], predecesor)) {
            vector<string> ruta;
            int actual = ciudad_idx[destino];

            while (actual != ciudad_idx[origen]) { // mientras que no llegue a la ciudad origen montamos la ruta
                ruta.push_back(ciudades[actual]);
                actual = predecesor[actual];
            }
            ruta.push_back(origen);

            for (int i = ruta.size() - 1; i > 0; i--) {
                cout << ruta[i] << " " << ruta[i - 1] << endl;

            }
        }
        else {
            cout << "No route" << endl;
        }
        cout << endl;
    }

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}
