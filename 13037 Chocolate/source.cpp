#include <iostream>
#include <iomanip>
#include <fstream>
#include <unordered_map>
#include <unordered_set>

using namespace std;


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int L, R, S;
    unordered_map<int, unordered_set<int>> chocolate_persona;
    unordered_set<int> chocolates_1;
    unordered_set<int> chocolates_2;
    unordered_set<int> chocolates_3;

    int num;
    cin >> L >> R >> S;

    int sol1izq = 0, sol1der = 0;
    int sol2izq = 0, sol2der = 0;
    int sol3izq = 0, sol3der = 0;

    for (int i = 0; i < L; i++)
    {
        cin >> num;
        chocolates_1.insert(num);
        chocolate_persona[num].insert(1);
    }
    for (int j = 0; j < R; j++)
    {
        cin >> num;
        chocolates_2.insert(num);
        chocolate_persona[num].insert(2);
    }
    for (int z = 0; z < S; z++)
    {
        cin >> num;
        chocolates_3.insert(num);
        chocolate_persona[num].insert(3);
    }
    
    for (auto personas : chocolate_persona) { 
        if (personas.second.size() == 2) { 
            if (!personas.second.count(1)) {
                sol1der++;
            }
            if (!personas.second.count(2)) {
                sol2der++;
            }
            if (!personas.second.count(3)) {
                sol3der++;
            }
        }

        if (personas.second.size() == 1) { 
            if (personas.second.count(1)) {
                sol1izq++;
            }
            if (personas.second.count(2)) {
                sol2izq++;
            }
            if (personas.second.count(3)) {
                sol3izq++;
            }
        }
    }

    cout << sol1izq << " " << sol1der << endl;
    cout << sol2izq << " " << sol2der << endl;
    cout << sol3izq << " " << sol3der << endl;

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
 
    for (int i = 0; i < numCasos; ++i) {
        cout << "Case #" << i + 1<< ":" << endl;
        resuelveCaso();
    }
        


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}