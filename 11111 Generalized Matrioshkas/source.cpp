#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <stack>
#include <stdlib.h>

using namespace std;

bool resuelveCaso() {
    // leer los datos de la entrada

    std::string str;
    getline(cin, str);
    stringstream ss(str);

    if (str == "")
        return false;

    stack<int> pilaAbiertos;
    stack<int> pilaSumas;

    int n;
    bool matrioshkaValida = true;

    while (ss >> n) { 

        if (n < 0) { // negativo
            
            pilaAbiertos.push(n);
            pilaSumas.push(0);  
        }
        else { // positivo
            
            if (pilaAbiertos.empty() || pilaAbiertos.top() != -n) {
                matrioshkaValida = false;
                break;
            }

            pilaAbiertos.pop();

            int sumaInterna = pilaSumas.top();
            pilaSumas.pop();
            if (sumaInterna >= n) {
                matrioshkaValida = false;
                break;
            }

            if (!pilaSumas.empty()) {
                pilaSumas.top() += n;
            }
        }
    }

    if (!pilaAbiertos.empty()) {
        matrioshkaValida = false;
    }

    if (matrioshkaValida) {
        cout << ":-) Matrioshka!" << endl;
    }
    else {
        cout << ":-( Try again." << endl;
    }

    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to datos.txt
#endif 

    while (resuelveCaso());

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}
