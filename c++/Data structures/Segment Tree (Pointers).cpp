typedef int T; 
const T neutro = 1e9;

T merge(T &a, T &b) {
    return min(a, b);
}

struct node {
    T value; node *l, *r;  
    // T lazy;
    
    node() : value(neutro), l(nullptr), r(nullptr)/*, lazy(neutro)*/ {}
    
    node(T val) : value(val), l(nullptr), r(nullptr)/*, lazy(neutro)*/ {} 
    
    /*
    void propagate(T val) {
        if (val == neutro) return;
        value = val;
        lazy = neutro;
        if (l != nullptr) l->lazy = val;
        if (r != nullptr) r->lazy = val;
    }
    */
    
    void unite() {
        T lf = (l != nullptr) ? l->value : neutro;
        T rg = (r != nullptr) ? r->value : neutro;  
        value = merge(lf, rg);
    }
};

struct segtree {
    node *root;
    int n;

    segtree(const vector<int> &v) {
        n = v.size();
        root = build(0, n - 1, v);
    }

    node* build(int L, int R, const vector<int> &v) {
        if (L == R) return new node(v[L]);
        int m = (L + R) / 2;
        node *p = new node();
        p->l = build(L, m, v);
        p->r = build(m + 1, R, v);
        p->unite();
        return p;
    }
    
    T query(int i, int j) { return query(root, 0, n - 1, i, j); }
    void upd(int i, int j, T val) { upd(root, 0, n - 1, i, j, val); }
    
    T query(node *p, int L, int R, int i, int j) {
        // p->propagate(p->lazy);
        if (i > R || j < L) return neutro;
        if (i <= L && j >= R) return p->value;
        int m = (L + R) / 2;
        T lf = query(p->l, L, m, i, j);
        T rg = query(p->r, m + 1, R, i, j);
        return merge(lf, rg);
    }

    void upd(node *p, int L, int R, int i, int j, T val) {
        // p->propagate(p->lazy);
        if (i > R || j < L) return;
        if (i <= L && j >= R) p->value = val; //cambiar por p->propagate(val);
        else {
            int m = (L + R) / 2;
            upd(p->l, L, m, i, j, val);
            upd(p->r, m + 1, R, i, j, val);
            p->unite();
        }
    }
};