Estructura de datos que permite procesar consultas por rangos y actualizaciones individuales sobre un arreglo.

const int MX = 1e5;
int bit[MX+1];

void add(int k, int val) {
    for (; k <= MX; k += k&-k) bit[k] += val;
}

int rsq(int k) {
    int sum = 0;
    for (; k >= 1; k -= k&-k) sum += bit[k];
    return sum;
}

int rsq(int i, int j) { return rsq(j) - rsq(i-1); }

int lower_find(int val) { // last value < or <= to val
    int id = 0;
    for (int i = 31-__builtin_clz(MX); i >= 0; --i) {
        int nid = id | (1<<i);
        if (nid <= MX && bit[nid] <= val) { // change <= to <
            val -= bit[nid];
            id = nid;
        }
    }
    return idx;
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

	/* For range update, point queries*/
	// Use rsq with one argument -> value[i] = rsq(i)
	void range_add(int l, int r, int value) {
		add(l, value);
		add(r + 1, -value);
	}
};