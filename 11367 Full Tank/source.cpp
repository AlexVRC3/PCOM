#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <vector>
#include <queue>
#include <tuple>
#include <climits>


using namespace std;

 using estado = tuple<int, int, int>; //costeActual, ciudad, combustible_restante

vector<vector<pair<int,int>>> adj;
vector<int> costesGasolina;

int resolver(int n, int capacidad, int ini, int fin) {
    
    vector<vector<int>> costeMin(n, vector<int>(capacidad + 1, INT_MAX));

    priority_queue<estado, vector<estado>, greater<estado>> pq;

    pq.push({ 0, ini, 0 });
    costeMin[ini][0] = 0;
   
    while (!pq.empty()) {

        estado s = pq.top();
        pq.pop();

        int costeActual = std::get<0>(s);
        int ciudad = std::get<1>(s);
        int combustible_restante = std::get<2>(s);

        if (ciudad == fin) {
            return costeActual;
        }

        if (costeActual > costeMin[ciudad][combustible_restante]) { // si ya ha sido procesado y no interesa omitimos
            continue;
        }

        // repotar en ciudad actual
        if (combustible_restante < capacidad) { 
            int nuevoCombustible = combustible_restante + 1;
            int nuevoCoste = costeActual + costesGasolina[ciudad];
            if (nuevoCoste < costeMin[ciudad][nuevoCombustible]) {
                costeMin[ciudad][nuevoCombustible] = nuevoCoste;
                pq.push({ nuevoCoste, ciudad, nuevoCombustible });
            }
        }

        // movernos a las posibles ciudades
        for (const auto& arista : adj[ciudad]) {
            if (combustible_restante >= arista.second) {  // si tenemos combustible
                int nuevaCiudad = arista.first;
                int nuevoCombustible = combustible_restante - arista.second;
                if (costeActual < costeMin[nuevaCiudad][nuevoCombustible]) {
                    costeMin[nuevaCiudad][nuevoCombustible] = costeActual;
                    pq.push({ costeActual, nuevaCiudad, nuevoCombustible });
                }
            }
        }
    }

    return -1; //imposible
}

int main() {

    #ifndef DOMJUDGE
        std::ifstream in("datos.txt");
        auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
    #endif 
    int n, m;
    cin >> n >> m;

    costesGasolina.assign(n,0);
	adj.assign(n, vector<pair<int, int>>());

    for (int i = 0; i < n; ++i) {
        cin >> costesGasolina[i];
    }

    for (int i = 0; i < m; ++i) {
        int u, v, d;
        cin >> u >> v >> d;
        adj[u].push_back({ v, d });
        adj[v].push_back({ u, d });
    }

    int q;
    cin >> q;
    for (int i = 0; i < q; i++)
    {
        int c, s, e;
        cin >> c >> s >> e;

        int result = resolver(n, c, s, e);
        if (result == -1) {
            cout << "impossible\n";
        }
        else {
            cout << result << '\n';
        }
    }

        // Para restablecer entrada. Comentar para acepta el reto
    #ifndef DOMJUDGE // para dejar todo como estaba al principio
        std::cin.rdbuf(cinbuf);
        system("PAUSE");
    #endif

    return 0;
}