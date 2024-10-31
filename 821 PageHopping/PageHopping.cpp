#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>

using namespace std;

const int MAX = 100;
double sumaValores;
int adjMat[MAX][MAX];

void floyd(int V) {
    for (int k = 0; k < V; k++)
        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++)
                if (adjMat[i][k] + adjMat[k][j] < adjMat[i][j]) {
                    adjMat[i][j] = adjMat[i][k] + adjMat[k][j];
                }

}

bool resuelveCaso(int &it) {

    int a, b; cin >> a >> b;
    sumaValores = 0;

    if (a == 0 && b == 0)
        return false;

    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++)
        {
            adjMat[i][j] = 1000;
        }
    }

    int V = max(a, b);
    adjMat[a - 1][b - 1] = 1;
    while (cin >> a >> b && a != 0 && b != 0) {
        V = max(V, b);
        V = max(a, V);
        adjMat[a - 1][b - 1] = 1;
    }

    floyd(V);

    int cont = 0;
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            if (i != j && adjMat[i][j] != 1000) {
                cont++;
                sumaValores += adjMat[i][j];
            }

    double clicks = sumaValores / cont;

    cout << "Case " << it << ": average length between pages = " << fixed << setprecision(3) << setfill('0') << clicks << " clicks\n";

    it++;
    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 

    int it = 1;
    while (resuelveCaso( it));


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}