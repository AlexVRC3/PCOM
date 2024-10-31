#include <iostream>
#include <iomanip>
#include <queue>
#include <fstream>
#include <cstring>

#define MAX_V 41
bool visited[MAX_V][MAX_V];
int dist[MAX_V][MAX_V][3];
const int INF = 1e9;
int N;

using namespace std;

int movK[8][2] = {
    {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
    {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
};

int movB[4][2] = {
    {2, 2}, {2, -2}, {-2, 2}, {-2, -2}
};

bool posicionValida(int x, int y) {
    return x > 0 && x <= 2 * N && y > 0 && y <= 2 * N && visited[x][y];
}

typedef struct {
    int x, y, movAnt, mov;
} tIteracion;

int bfs(int oX, int oY, int dX, int dY) {
    queue<tIteracion> q;

    // Empezamos el BFS sin ningun movimiento anterior y ningun movimiento realizado
    q.push({ oX, oY, -1, 0 });
    dist[oX][oY][0] = 0;
    dist[oX][oY][1] = 0;
    dist[oX][oY][2] = 0;

    while (!q.empty()) {
        tIteracion it = q.front();
        q.pop();

        // LLegamos
        if (it.x == dX && it.y == dY)
            return it.mov;

        // Probamos con los movimientos de K
        if (it.movAnt != 0) {
            for (auto& k : movK) {
                int aux_x = it.x + k[0], aux_y = it.y + k[1];

                if (posicionValida(aux_x, aux_y) && dist[aux_x][aux_y][0] == INF) {
                    dist[aux_x][aux_y][0] = it.mov + 1;
                    tIteracion newIt = { aux_x, aux_y, 0, it.mov + 1 };
                    q.push(newIt);
                }
            }
        }

        // Probamos con los movimientos de B
        if (it.movAnt != 1) {
            for (auto& b : movB) {
                int aux_x = it.x + b[0], aux_y = it.y + b[1];

                if (posicionValida(aux_x, aux_y) && dist[aux_x][aux_y][1] == INF) {
                    dist[aux_x][aux_y][1] = it.mov + 1;
                    tIteracion newIt = { aux_x, aux_y, 1, it.mov + 1 };
                    q.push(newIt);
                }
            }
        }

        // Probamos con los movimientos de T
        if (it.movAnt != 2) {
            int aux_x = 2*N - it.x + 1;
            int aux_y = 2*N - it.y + 1;

            for (int i = 0; i < 2; i++) {
                if (i == 0) {
                    if (posicionValida(aux_x, it.y) && dist[aux_x][it.y][2] == INF) {
                        dist[aux_x][it.y][2] = it.mov + 1;
                        tIteracion newIt = { aux_x, it.y, 2, it.mov + 1 };
                        q.push(newIt);
                    }
                }
                else {
                    if (posicionValida(it.x, aux_y) && dist[it.x][aux_y][2] == INF) {
                        dist[it.x][aux_y][2] = it.mov + 1;
                        tIteracion newIt = { it.x, aux_y, 2, it.mov + 1 };
                        q.push(newIt);
                    }
                }
            }
        }
    }

    // Si no llegamos
    return -1;
}

// Resuelve un caso de prueba
bool resuelveCaso() {
    cin >> N;
    if (N == 0)
        return false;

    // Inicializamos visitados (tablero) (true = no hay obstaculo)
    memset(visited, true, sizeof(visited));
    // Inicializamos distancias con bucle en lugar de memset
    for (int i = 0; i < MAX_V; i++) {
        for (int j = 0; j < MAX_V; j++) {
            dist[i][j][0] = dist[i][j][1] = dist[i][j][2] = INF;
        }
    }

    int o1, o2, d1, d2;
    cin >> o1 >> o2 >> d1 >> d2;

    int obs1, obs2;
    while (cin >> obs1 >> obs2 && (obs1 != 0 || obs2 != 0)) {
        visited[obs1][obs2] = false;
    }

    int result = bfs(o1, o2, d1, d2);

    if (result == -1)
        cout << "Solution doesn't exist" << endl;
    else
        cout << "Result : " << result << endl;

    return true;
}

int main() {
    // Para la entrada por fichero.
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 

    while (resuelveCaso());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}
