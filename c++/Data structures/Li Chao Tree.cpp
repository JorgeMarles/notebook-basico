typedef int T;
const T oo = 1e9;

struct Line {
    // A representation of a first-degree polynomial function
    T m, b;

    // Change -oo for oo in case of minimization 
    Line() : m(0), b(-oo) {}

    Line(T _m, T _b) : m(_m), b(_b) {}

    T f(T x) {
        return m * x + b;
    }
};

struct LiChaoTree {
    vector<Line> nodes;
    int n;

    // Create a LiChaoTree with a range [0, n) that maximizes the value of the functions
    LiChaoTree(int _n) {
        n = _n;
        nodes.assign(4*n, Line());
    }    

    void add_line(Line nw) { add_line(1, 0, n, nw); }

    T get(int x) {return get(1, 0, n, x);}

    void add_line(int p, int l, int r, Line nw) {
        int m = (l + r) / 2;
        // Change > for < in case of minimize
        bool left = nw.f(l) > nodes[p].f(l);
        bool middle = nw.f(m) > nodes[p].f(m);
        if(middle) {
            swap(nodes[p], nw);
        }
        if(r - l > 1) {
            if(left != middle) {
                add_line(2 * p, l, m, nw);
            }
            else {
                add_line(2 * p + 1, m, r, nw);
            }
        }
    }

    T get(int p, int l, int r, int x) {
        int m = (l + r) / 2;
        if(r - l == 1) {
            return nodes[p].f(x);
        }
        // Change max for min in case of minimize
        if(x < m) {
            return max(nodes[p].f(x), get(2 * p, l, m, x));
        }
        return max(nodes[p].f(x), get(2 * p + 1, m, r, x));
    }
};