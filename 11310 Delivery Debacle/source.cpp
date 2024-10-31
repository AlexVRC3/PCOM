// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

// función que resuelve el problema
long long int resolver(int L) {
    vector<long long int> v(L);
    if (L == 0) {   return 0;   }

    if (L >= 1) {   v[0] = 1;   }
    if (L >= 2) {   v[1] = 5;   }
    if (L >= 3) {   v[2] = 11;  }

    for (int i = 3; i < L; i++)
        v[i] = v[i - 1] + (4 * v[i - 2]) + (2 * v[i - 3]);

    return v[L - 1];
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int L;
    cin >> L;

    long long int sol = resolver(L);

    cout << sol << endl;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}