//#include <iostream>
//#include <iomanip>
//#include <fstream>
//#include <vector>
//#include <algorithm>
//
//using namespace std;
//using arista = pair<int, pair<int, int>>; // <coste, extremos> 
//
//struct UFDS {
//    vector<int> p;
//    int numSets;
//    UFDS(int n) : p(n, 0), numSets(n) {
//        for (int i = 0; i < n; ++i) p[i] = i;
//    }
//    int find(int x) {
//        return (p[x] == x) ? x : p[x] = find(p[x]);
//    }
//    void merge(int x, int y) {
//        int i = find(x), j = find(y);
//        if (i == j) return;
//        p[i] = j;
//        --numSets;
//    }
//};
//
//// Resuelve un caso de prueba, leyendo de la entrada la
//// configuración, y escribiendo la respuesta
//void resuelveCaso() {
//   
//    int n, m;
//    cin >> n >> m;
//	vector<arista> aristas;
//
//    int u, v, c;
//    for (int i = 0; i < m; i++)
//    {
//        cin >> u >> v >> c;
//		aristas.push_back({ c, {u , v } });
//    }
//
//    sort(aristas.begin(), aristas.end(), greater<>());
//
//    UFDS uf(n);
//    int coste = 0;
//
//
//    //quiero sacar la menor arista del kruskal
//	int valorArista = aristas.front().first;
//    for (auto ar : aristas) {
//        if (uf.find(ar.second.first) != uf.find(ar.second.second)) {
//            uf.merge(ar.second.first, ar.second.second); 
//			if (ar.first < valorArista)
//			{
//				valorArista = ar.first;
//			}
//            coste += ar.first; 
//            if (uf.numSets == 1) break; 
//        } 
//    } cout << valorArista << endl;
//
//  
//}
//
//int main() {
//    // Para la entrada por fichero.
//    // Comentar para acepta el reto
//#ifndef DOMJUDGE
//    std::ifstream in("datos.txt");
//    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
//#endif 
//
//    int nCasos;
//    cin >> nCasos;
//    for (int i = 0; i < nCasos; i++)
//    {
//        cout << "Case #" << i + 1 << ": ";
//        resuelveCaso();
//    }
//
//    // Para restablecer entrada. Comentar para acepta el reto
//#ifndef DOMJUDGE // para dejar todo como estaba al principio
//    std::cin.rdbuf(cinbuf);
//    system("PAUSE");
//#endif
//
//    return 0;
//}



