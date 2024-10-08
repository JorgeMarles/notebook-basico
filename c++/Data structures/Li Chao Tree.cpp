typedef int T;
const T oo = 1e9;

struct Line {
    /* Representa un polinomio de primer grado */
    T m, b;

    /* Cambiar -oo por oo en caso de quere minimizar la funcion */
    Line() : m(0), b(-oo) {}

    Line(T _m, T _b) : m(_m), b(_b) {}

    T f(T x) {
        return m * x + b;
    }
};

struct LiChaoTree {
    vector<Line> nodes;
    int n;

    /* Crea un LiChaoTree que contiene el rango [0, n), donde cada posicion es el punto maximo entre todas las funciones */
    LiChaoTree(int _n) {
        n = _n;
        nodes.assign(4*n, Line());
    }    

    void add_line(Line nw) { add_line(1, 0, n, nw); }

    T get(int x) {return get(1, 0, n, x);}

    void add_line(int p, int l, int r, Line nw) {
        int m = (l + r) / 2;
        /* Cambiar > por < en caso de querer minimizar la funcion */
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
        /* Cambiar max por min en caso de querer minimizar la funcion */
        if(x < m) {
            return max(nodes[p].f(x), get(2 * p, l, m, x));
        }
        return max(nodes[p].f(x), get(2 * p + 1, m, r, x));
    }
};