const int ALPHA = 26; // Tamano del alfabeto
const char L = 'a'; // Primera letra del alfabeto

int get_mov(char &ch) {
	return ch - L;
}

struct node {
    int next[ALPHA];
    // int idx;
    vector<int> idx;
    int fail, fail_out, cnt;
    int &operator[](int i) {return next[i];}
};

struct Trie {
    vector<node> nodes;
    vector<int> cnt;

    Trie() {nodes.push_back(node());}

    void add_str(string &s) {
        int u = 0;
        for(auto &ch : s) {
            int c = get_mov(ch);
            if(!nodes[u][c]) {
                nodes[u][c] = nodes.size();
                nodes.push_back(node());
            }
            u = nodes[u][c];
        }
        nodes[u].idx.push_back(cnt.size());
        cnt.push_back(0);
    }

    void build_aho_automaton() {
        queue<int> q;
        int u = 0;
        q.push(u);

        while(!q.empty()) {
            u = q.front();
            q.pop();

            for(int c = 0; c < ALPHA; c++) {
                int v = nodes[u][c];
                if(v) {
                    q.push(v);
                    if(u) {
                        // Calcula el fail
                        int nxt_fail = nodes[u].fail;
                        while(nxt_fail && !nodes[nxt_fail][c]) {
                            nxt_fail = nodes[nxt_fail].fail;
                        }
                        nodes[v].fail = nodes[nxt_fail][c];

                        // Calcula el fail_out
                        if(!nodes[nodes[v].fail].idx.size()) {
                            nodes[v].fail_out = nodes[nodes[v].fail].fail_out;
                        }
                        else nodes[v].fail_out = nodes[v].fail;
                    }
                }
            }
        }
    }

    void run_automaton(string &s) {
        int u = 0;
        for(char &ch : s) {
            int c = get_mov(ch);
            while(u && !nodes[u][c]) {
                u = nodes[u].fail;
            }
            u = nodes[u][c];

      	    // Propagar las apariciones de las palabras en ejecución
		    int v = u;
            while(v) {
                for(int &id : nodes[v].idx) {
                    cnt[id]++;
                }
                v = nodes[v].fail_out;
            }
        }
    }

    // Propagar las apariciones de las palabras en despues de la ejecucion
    // Solo se puede llamar si se elimina la otra propagacion
    /*
    void propagate() {
        queue<pii> q;
        vector<pii> nodos_vis;
        pii p = {0, 0};
        q.push(p);

        while(!q.empty()) {
            p = q.front();
            q.pop();
            nodos_vis.pb({p.sd, p.ft});

            for(int c = 0; c < ALPHA; c++) {
                if(nodes[p.ft][c]) {
                    q.push({nodes[p.ft][c], p.sd + 1});
                }
            }
        }
        sort(nodos_vis.rbegin(), nodos_vis.rend());
        for(auto &[d, u] : nodos_vis) {
            nodes[nodes[u].fail].cnt += nodes[u].cnt;
            if(nodes[u].idx.size()) {
                for(int &id : nodes[u].idx) {
                    cnt[id] += nodes[u].cnt;
                }
            }
        }
    }
    */
};