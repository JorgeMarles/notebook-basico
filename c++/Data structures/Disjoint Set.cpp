> Permite mantener una colección de conjuntos disyuntos. find(u) indica a qué conjunto pertenece u. unite(u, v) une los conjuntos de u y v en uno.
> Para permitir rollbacks descomentar las lineas 7, 21, 27, [33 - 41]. Además cambiar el return de la linea 14 por el de la linea 15 para impedir la compresión.

struct dsu {
    vector<int> par, sz;
    int size; // Cantidad de conjuntos
    // stack<pair<int, int>> edges;

    dsu(int n) : par(n), sz(n, 1), size(n) {
        iota(par.begin(), par.end(), 0);
    }
    // Busca el nodo representativo del conjunto de u
    int find(int u) {
        return par[u] == u ? u : (par[u] = find(par[u]));
        // return par[u] == u ? u : find(par[u]);
    }
    // Une los conjuntos de u y v
    void unite(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) {
            // edges.push({-1, -1});
            return;
        }
        if (sz[u] > sz[v]) swap(u, v);
        par[u] = v;
        sz[v] += sz[u];
        // edges.push({u , v});
        size--;
    }
    // Cantidad de elementos en el conjunto de u
    int count(int u) { return sz[find(u)]; }
    /*
    void rollback() {
        assert(!edges.empty());
        int u = edges.top().ft, v = edges.top().sd;
        edges.pop();
        if(u == -1) return;
        sz[v] -= sz[u];
        par[u] = u;
        size++;
    }
    */
};
