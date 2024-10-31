#include <iostream>
#include <fstream>	
#include <vector>
#include <queue>
#include <iomanip>
#include <cstring>
#include <algorithm>

#define INF 1000000000
using namespace std;

vector<vector<int>> cap; // Capacidad de las aristas
vector<vector<int>> adj; // Lista de adyacencia
vector<int> visited; // Para BFS
vector<int> parent; // Para BFS
vector<int> capacitiesRegulators; // Capacidad de los reguladores


// En parent dejamos el anterior en el recorrido BFS
void bfs(int s, int t) {
	queue<int> q;
	visited.assign(visited.size(), 0);
	parent.assign(parent.size(), -1);
	q.push(s);
	parent[s] = -1;
	visited[s] = true;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		if (u == t) break;
		for (int i = 0; i < adj[u].size(); ++i) {
			int v = adj[u][i];
			if (!visited[v] && (cap[u][v] > 0)) {
				parent[v] = u;
				visited[v] = true;
				q.push(v);
			}
		}
	}
}

int sendFlow(int s, int t) {
	// Intentamos llegar de s a t 
	bfs(s, t);
	if (!visited[t])
		return 0; // No pudimos 
	// Buscamos capacidad mas pequena en el camino
	int flow = INF, v = t;
	while (v != s) {
		flow = min(cap[parent[v]][v], flow);
		v = parent[v];
	} // Mandamos flujo 
	v = t;
	while (v != s) {
		cap[parent[v]][v] -= flow;
		cap[v][parent[v]] += flow; // INVERSA 
		v = parent[v];
	}
	return flow;
}

int edmondsKarp(int s, int t) {
	int ret = 0; int flow = 0;
	do {
		flow = sendFlow(s, t);
		ret += flow;
	} while (flow > 0);
	return ret;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int N;
	cin >> N;
	if (!std::cin)
		return false;

	adj.assign(2 * N + 2, vector<int>());
	cap.assign(2 * N + 2, vector<int>(2 * N + 2, 0));
	visited.assign(2 * N + 2, 0);
	parent.assign(2 * N + 2, -1);

	int capacidad;
	for (int i = 0; i < N; i++) {
		cin >> capacidad;
		int vertice = i + 1;
		adj[vertice].push_back(vertice + N); //arista de reg_out a reg_in con capacidad 0
		adj[vertice + N].push_back(vertice); //arista de reg_in a reg_out con capacidad regulador
		cap[vertice][vertice + N] += capacidad;
	}
	
	int M;
	cin >> M;

	int u, v, C;
	for (int i = 0; i < M; i++) {
		cin >> u >> v >> C;
		adj[u + N].push_back(v);
		adj[v].push_back(u + N);
		cap[u + N][v] += C; 
	}

	int B, D;
	cin >> B >> D;
	
	for (int i = 0; i < B; i++) { // barisal
		cin >> v;
		adj[0].push_back(v);
		adj[v].push_back(0);
		cap[0][v] = INF; 
	}


	for (int i = 0; i < D; i++) { // dhaka
		cin >> v;
		adj[v + N].push_back(2 * N + 1);
		adj[2 * N + 1].push_back(v);
		cap[v + N][2 * N + 1] = INF; 
	}

	cout << edmondsKarp(0, 2 * N + 1) << endl;
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