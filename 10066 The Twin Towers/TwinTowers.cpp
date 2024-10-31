#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;


int  resolver(vector<int>const& izq, vector<int>const& der) {
    int N = izq.size();
    int M = der.size();

    vector<vector<int>> map(N + 1, vector<int>(M + 1, 0));

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {

            map[i][j] = max(map[i - 1][j], map[i][j - 1]);

            if (izq[i - 1] == der[j - 1]) {
                int num = map[i - 1][j - 1] + 1;

                if (num > map[i][j]) {
                    map[i][j] = num;
                }
            }
        }
    }

    return map[N][M];
}

bool resuelveCaso(int &it) {

    int nIzq, nDer; cin >> nIzq >> nDer;
    if (nIzq == 0 && nDer == 0) return false;

    vector<int> izq(nIzq);
    vector<int> der(nDer);

    for (int i = 0; i < nIzq; i++) {
        cin >> izq[i];
    }
    for (int i = 0; i < nDer; i++) {
        cin >> der[i];
    }

    cout << "Twin Towers #" << it << '\n' << "Number of Tiles : " << resolver(izq, der) << '\n' << '\n';
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
    while (resuelveCaso(it));


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}