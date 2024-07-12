mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<ll> rnd(0, LLONG_MAX);

template <typename T>
struct Treap {
    
    T unite(T left, T mid, T right) {
        return left + mid + right;
    }
    
    struct Node {
        T value, sbt_value, lazy;
        ll priority; int sbt_size;
        Node *left, *right;
        bool is_rever;
    
        Node(T v, T neutro) : value(v), left(nullptr), right(nullptr) {
            priority = rnd(rng);
            sbt_value = value;
            lazy = neutro;
            is_rever = false;
            sbt_size = 1;
        }
    };
    
    Node *root;
    T neutro;
    
    Treap() : root(nullptr), neutro(0) {}
    
    int size(Node *node) {
        return (node != nullptr) ? node->sbt_size : 0;
    }
    
    void propagate(Node *node) {
        if (node == nullptr) return;
        if (node->is_rever) {
            swap(node->left, node->right);
            if (node->left != nullptr) {
                node->left->is_rever ^= true;
            } 
            if (node->right != nullptr) {
                node->right->is_rever ^= true;
            } 
            node->is_rever = false;
        }
        if (node->lazy == neutro) return;
        node->value = node->lazy;
        /*Si la actualización depende de los hijos, usar el método update para facilitar el proceso*/
        node->sbt_value = node->lazy * node->sbt_size;
        if (node->left != nullptr) {
            node->left->lazy = node->lazy;
        }  
        if (node->right != nullptr) {
            node->right->lazy = node->lazy;
        }  
        node->lazy = neutro;
    }
    
    void update(Node *node) {
        if (node == nullptr) return;
        int lf_sz = (node->left != nullptr) ? node->left->sbt_size : 0;
        int rg_sz = (node->right != nullptr) ? node->right->sbt_size : 0;
        node->sbt_size = lf_sz + rg_sz + 1;
        T lf_v = (node->left != nullptr) ? node->left->sbt_value : neutro;
        T rg_v = (node->right != nullptr) ? node->right->sbt_value : neutro;
        node->sbt_value = unite(lf_v, node->value, rg_v); 
    }
    
    array<Node*, 2> split(Node *node, int cnt_left) {
        if (node == nullptr) return {nullptr, nullptr};
        propagate(node);
        if (cnt_left <= size(node->left)) {
            auto lf_ans = split(node->left, cnt_left);
            node->left = lf_ans[1];
            update(node);
            return {lf_ans[0], node};
        }
        else {
            cnt_left = cnt_left - size(node->left) - 1;
            auto rg_ans = split(node->right, cnt_left);
            node->right = rg_ans[0];
            update(node);
            return {node, rg_ans[1]};
        }
    }
    
    Node* merge(Node *lf, Node *rg) {
        if (lf == nullptr) return rg;
        if (rg == nullptr) return lf;
        propagate(lf);
        propagate(rg);
        if (lf->priority < rg->priority) {
            lf->right = merge(lf->right, rg);
            update(lf);
            return lf;
        }
        else {
            rg->left = merge(lf, rg->left);
            update(rg);
            return rg;
        }
    }
    
    void push(T value) {
        Node *node = new Node(value, neutro);
        root = merge(root, node);
    }
    
    void inorder() { inorder(root); }
    
    void inorder(Node *node) {
        if (node == nullptr) return;
        propagate(node);
        inorder(node->left);
        cout << node->value << " " << node->sbt_value << " " << node->priority << endl;
        inorder(node->right);
    }
    
    /*
        Rango inclusive [l, r] indexado de 0
        cuts[0] = Subarbol con nodos [0, l - 1]
        cuts[1] = Subarbol con nodos [l, r]
        cuts[2] = Subarbol con nodos [r + 1, n - 1]
    */
    void upd(int l, int r, T value) {
        auto lf_cut = split(root, l);
        auto rg_cut = split(lf_cut[1], r - l + 1);
        array<Node*, 3> cuts = {lf_cut[0], rg_cut[0], rg_cut[1]};
        cuts[1]->lazy = value;
        root = merge(cuts[0], merge(cuts[1], cuts[2]));
    }
    
    T query(int l, int r) {
        auto lf_cut = split(root, l);
        auto rg_cut = split(lf_cut[1], r - l + 1);
        array<Node*, 3> cuts = {lf_cut[0], rg_cut[0], rg_cut[1]};
        T ans_query = cuts[1]->sbt_value;
        root = merge(cuts[0], merge(cuts[1], cuts[2]));
        return ans_query;
    }
};