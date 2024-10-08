> Permite la operación de agregar y eliminar aristas de un grafo, y responder queries sobre la estructura del grafo en un tiempo t.
> Este ejemplo calcula el numero de componentes en el grafo en el tiempo t.
> Ejecutar propagate una vez se hayan agregado todas las aristas al arbol.

typedef pair<int, int> T;

struct DynamicConnectivity {
    vector<vector<T>> edges;
    vector<int> cnt_comp; // Numero de componentes
    dsu ds;
    int t;
    
    // Parametros: 
    // _t Tiempo maximo donde se realizan las actualizaciones
    // sz Tamaño del grafo sobre el que se realizan las actualizaciones
    DynamicConnectivity(int _t, int sz) : t(_t), cnt_comp(_t), ds(sz) {
        edges.assign(4 * _t, vector<T>());
    }
    
    // Rango de tiempo [i, j] en el que la arista existe
    void add_edge(int i, int j, T edge) { add_edge(1, 0, t - 1, i, j, edge);}
    void propagate() { propagate(1, 0, t - 1); }
    
    void add_edge(int p, int L, int R, int i, int j, T edge) {
        if(i > R || j < L) return;
        if(i <= L && R <= j) edges[p].push_back(edge);
        else {
            int m = (L + R) / 2, l = 2 * p, r = l + 1;
            add_edge(l, L, m, i, j, edge);
            add_edge(r, m + 1, R, i, j, edge);
        }
    }
    
    void propagate(int p, int L, int R) {
        int cnt = 0;
        for(auto &[u, v] : edges[p]) {
            ds.unite(u, v);
            cnt++;
        }
        if(L == R) cnt_comp[L] = ds.size;
        else {
            int m = (L + R) / 2, l = 2 * p, r = l + 1;
            propagate(l, L, m);
            propagate(r, m + 1, R);
        }
        while(cnt--) {
            ds.rollback();
        }
    }
};