> 🚨 Usar indexando desde 1 en vez de 0. Permite procesar consultas de suma en rangos y actualizaciones puntuales sobre un arreglo.

const int N = 1e5;
int bit[N+1];

void add(int k, int val) {
    for (; k <= N; k += k&-k) bit[k] += val;
}

int rsq(int k) {
    int sum = 0;
    for (; k >= 1; k -= k&-k) sum += bit[k];
    return sum;
}

int rsq(int i, int j) { return rsq(j) - rsq(i-1); }
// Ultimo valor <= o < a val
int lower_find(int val) {
    int id = 0;
    for (int i = 31-__builtin_clz(N); i >= 0; --i) {
        int nid = id | (1<<i);
        if (nid <= N && bit[nid] <= val) { // o bit[nid] < val
            val -= bit[nid];
            id = nid;
        }
    }
    return id;
}

Versión como struct en 1 index

template <typename T>
struct BIT {
	vector<T> bit;
	int n;

	BIT(int _n) {
		n = _n;
		bit.assign(n + 2, 0);
	}
	
	void add(int idx, T value) {
		for(; idx <= n; idx += idx & -idx) bit[idx] += value;
	}

	T rsq(int idx) {
		T sum = 0;
		for(; idx >= 1; idx -= idx & -idx) sum += bit[idx];
		return sum;
	}

	T rsq(int l, int r) { return rsq(r) - rsq(l - 1); }

	/* Para range update y point queries*/
	/* Para preguntar la posicion i usar rsq con un argumento -> value[i] = rsq(i) */ 
	void range_add(int l, int r, int value) {
		add(l, value);
		add(r + 1, -value);
	}
};