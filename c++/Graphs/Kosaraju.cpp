const int N = 2e5; // Número máximo de nodos
vector<int> g[N+1], rg[N+1]; // Lista de adyacencia normal y reversada
//vector<int> comp_nodes[N+1]; // Vector con los nodos de cada componente
//vector<int> new_g[N+1]; // DAG con los nodos componente unidos
//set<int> new_g[N+1]; // DAG con los nodos componente unidos sin aristas múltiples
stack<int> st; // Pila donde almacenar el recorrido inicial
bool vist[N+1]; // Nodos visitados
int comp[N+1]; // Componente a la que pertenece el nodo
int SCC; // Número de componentes fuertemente conexas
int n, m; // Número de nodos y de aristas

void add_nodes(int u) {
    vist[u] = true;
    for(int &v : g[u]) {
        if(!vist[v]) add_nodes(v);
    }
    st.push(u);
}

void get_component(int u) {
    vist[u] = true;
    comp[u] = SCC;
    //comp_nodes[SCC].pb(u);
    for(int &v : rg[u]) {
        if(!vist[v]) get_component(v);
    }
}

void kosaraju() {
    for(int i = 1; i <= n; i++) {
        if(!vist[i]) {
            add_nodes(i);
        }
    }
    for(int i = 1; i <= n; i++) {
        vist[i] = false;
    }
    while(!st.empty()) {
        if(!vist[st.top()]) {
            SCC++;
            get_component(st.top());
        }
        st.pop();
    }
}

/*
void build_new_graph() {
    for(int u = 1; u <= n; u++) {
        for(int &v : g[u]) {
            if(comp[u] != comp[v]) {
                new_g[comp[u]].pb(comp[v]);
                //new_g[comp[u]].insert(comp[v]);
            }
        }
    }
}
*/

void init() {
    SCC = 0;
    for(int i = 1; i <= n; ++i) {
        g[i].clear();
        rg[i].clear();
        vist[i] = false;
        // new_g[i].clear();
        // comp_nodes[i].clear(); 
    }
}