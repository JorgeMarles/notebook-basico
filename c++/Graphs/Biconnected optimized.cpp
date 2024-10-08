Dado un grafo no dirigido halla el block cut tree (Esta es una versión optimizada almacenando las componentes en vectores)
WARNING : La cantidad de nodos del block cut tree puede ser mayor al input, colocar el doble.
const int MX = 2e5+5; // Cantidad maxima de nodos
vector<int> g[MX]; // Lista de adyacencia
int low[MX], num[MX], cont;
stack<int> st;
bool art[MX]; // Si el nodo es un punto de articulacion
// vector<vector<int>> comps; // Componentes biconexas
// vector<vector<int>> tree; // Block cut tree
// vector<int> id; // Id del nodo en el block cut tree
// set<pair<int, int>> bridges; // Puentes del grafo original
int BCC; // Cantidad de componentes biconexas
int n, m; // Cantidad de nodos y aristas

void dfs(int u, int p = -1) {
    low[u] = num[u] = cont++;
	st.push(u);
    for (int &v : g[u]) {
        if (num[v] == -1) {
            dfs(v, u);
            if (low[v] > num[u]) 
                bridges.insert(minmax(u, v)); // bridge
            if (low[v] >= num[u]) {
                art[u] = (num[u] > 0 || num[v] > 1); // articulation
                // start biconnected
				int last = u;
                // comps.pb({last});
				while (last != v) {
					last = st.top();
					st.pop();
					// comps.back().pb(last);
				}
                BCC++; // end biconnected
            }
            low[u] = min(low[u], low[v]);
        } else {
			low[u] = min(low[u], num[v]);
        }
    }
}

void build_tree() {
    tree.clear(); id.resize(n);
    for (int u = 0; u < n; u++) {
        if (art[u]) {
            id[u] = tree.size();
            tree.pb({});
        }
    }
    for (auto &comp : comps) {
        int node = tree.size();
        tree.pb({});
        for (auto &u : comp) {
            if (art[u]) {
                tree[id[u]].pb(node);
                tree[node].pb(id[u]);
            } else id[u] = node;
        }
    }
}

void init() {
    cont = BCC = 0;
    // comps.clear();
    for (int i = 0; i <= n; i++) {
        g[i].clear();
        num[i] = -1; // no visitado
        art[i] = false;
    }
}