#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>  
using namespace std;


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct tSol {
    int nWalkovers;
    bool seJuega;  
};

tSol resolver(const vector<bool>& retirados, int ini, int fin) {
    if (ini + 1 == fin) { 
        bool jugador1_retirado = retirados[ini];
        bool jugador2_retirado = retirados[fin];

        if (jugador1_retirado && jugador2_retirado) {
            return { 0, false };  
        }
        else if (jugador1_retirado || jugador2_retirado) {
            return { 1, true };   
        }
        else {
            return { 0, true };   
        }
    }
    else {
        int mitad = (ini + fin) / 2;
        tSol izq = resolver(retirados, ini, mitad);
        tSol der = resolver(retirados, mitad + 1, fin);

        bool seJuega = izq.seJuega || der.seJuega;
        int walkovers = seJuega && !(izq.seJuega && der.seJuega) ? 1 : 0; 

        return { walkovers + izq.nWalkovers + der.nWalkovers, seJuega };
    }
}

void resuelveCaso() {
    // leer los datos de la entrada
    int N, M;
    cin >> N >> M;

    int totalJugadores = static_cast<int>(pow(2, N)); // 2 a la n jugadores
    vector<bool> retirados(totalJugadores, false); 

    for (int i = 0; i < M; ++i) {
        int jugador;
        cin >> jugador;
        retirados[jugador - 1] = true; 
    }

    tSol sol = resolver(retirados, 0, totalJugadores - 1);

    cout << sol.nWalkovers << "\n";
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

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