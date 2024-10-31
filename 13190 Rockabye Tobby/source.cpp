
#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>

using namespace std;


struct query {
    int num;
    int periodo;
    int tiempo_siguiente;

    bool operator<(const query& otra) const {
        if (tiempo_siguiente == otra.tiempo_siguiente) {
            return num > otra.num;
        }
        return tiempo_siguiente > otra.tiempo_siguiente;
    }
};


// función que resuelve el problema
vector<int> resolver(priority_queue<query>& pq, int K) {
    vector<int> sol;
    while (sol.size() < K) {
        query top = pq.top();
        pq.pop();
        sol.push_back(top.num);

        top.tiempo_siguiente += top.periodo;
        pq.push(top);
    }
    return sol;
}



// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    string reg;
    priority_queue<query> pq;

    cin >> reg;
    if (!std::cin)
        return false;

    while (reg != "#") {
        query q;

        cin >> q.num >> q.periodo;
        q.tiempo_siguiente = q.periodo;
        pq.push(q);
        cin >> reg;
    }

    int K;
    cin >> K;
    vector<int> sol = resolver(pq, K);

    // escribir sol
    for (int num : sol) {
        cout << num << endl;
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