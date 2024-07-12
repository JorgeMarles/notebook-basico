/*
Constrains
a <= b <= c <= d

1. cost(b, c) <= cost(a, d)
2. cost(a, c) + cost(b, d) <= cost(a, d) + cost(b, c)

En el caso general

opt(i, j - 1) <= opt(i, j) <= opt(i + 1, j)

Esta ecuación se resume en que si agrego un elemento,
ya sea a la izquierda o a la derecha, el corte óptimo
no se mueve o se desplaza en la misma dirección.

Este código esta hecho para trabajar en rangos inclusivos [i, j]

*/

typedef int T;

const T oo = 1e9;
const int N = 1001;
int opt[N][N];
T dp[N][N];
int n;

T cost(int i, int j) {
    return;   
}

T f(int i, int j) {
    if (i > j) return 0;
    if (i == j) {
        opt[i][j] = i;
        return cost(i, j);
    }
    T &ans = dp[i][j];
    if (ans != -1) return ans;
    ans = oo;
    f(i, j - 1); f(i + 1, j);
    for (int k = opt[i][j - 1]; k <= opt[i + 1][j]; ++k) {
        T new_cost = f(i, k - 1) + f(k + 1, j) + cost(i, j);
        if (new_cost < ans) {
            ans = new_cost;
            opt[i][j] = k;
        }
    }
    return ans;
}

void init() {
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            dp[i][j] = -1;
        }
    }
}

/*
Versión iterativa

Tener cuidado con el dp[i][k - 1] y dp[k + 1][j] ya que puede tomar basura
inicializar el dp[i][0] = 0 y dp[n + 1][j] = 0
*/

typedef int T;

const T oo = 1e9;
const int N = 1005;
int opt[N][N];
T dp[N][N];
int n;

T cost(int i, int j) {
    return;   
}

T f() {
    for (int i = 1; i <= n; ++i) {
        opt[i][i] = i;
        dp[i][i] = cost(i, i);
    }
    for (int i = 1; i <= n; ++i) {
        dp[i][0] = dp[n + 1][i] = 0;
    }
    for (int i = n - 1; i >= 1; --i) {
        for (int j = i + 1; j <= n; ++j) {
            T ans = oo;
            for (int k = opt[i][j - 1]; k <= opt[i + 1][j]; ++k) {
                T new_cost = dp[i][k - 1] + dp[k + 1][j] + cost(i, j);
                if (new_cost <= ans) {
                    ans = new_cost;
                    opt[i][j] = k;
                }
            }
            dp[i][j] = ans;
        }
    }
    return dp[1][n];
}
