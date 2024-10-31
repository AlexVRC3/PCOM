#include <iostream>
#include <iomanip>
#include <fstream>
#include <unordered_map>
#include <vector>


using namespace std;


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n, m;
    cin >> n >> m;
    if (!std::cin)
        return false;

    unordered_map<int,vector<int>> numeros;
    vector<int> sol;
    int k, v, num;
    for (int i = 0; i < n; i++)
    {
        cin >> num;
        numeros[num].push_back(i + 1);
    }
    for (int j = 0; j < m; j++)
    {
        cin >> k >> v;
        if (numeros.count(v) && numeros[v].size() >= k) {
            sol.push_back(numeros[v][k - 1]);
        }
        else {
            sol.push_back(0);
        }
    }

    for (int i = 0; i < sol.size(); i++)
    {
        cout << sol[i] << endl;
    }

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