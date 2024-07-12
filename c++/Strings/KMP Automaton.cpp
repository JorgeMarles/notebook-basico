const int N = 1e6; // Tamaño máximo de la cadena
const int ALPHA = 26; // Tamaño del alfabeto
const int CH = 'a'; // Primer caracter del alfabeto
int aut[N][ALPHA]; // Autómata
int n; // Tamaño del patrón

void kmp_automaton(string &p) {
    n = p.size();
    for(int i = 0; i < ALPHA; i++) {
        aut[0][i] = 0;
    }
    aut[0][p[0] - CH] = 1; 
    for(int i = 1, j = 0; i <= n; i++) {
        for(int k = 0; k < ALPHA; k++) {
            aut[i][k] = aut[j][k];
        }
        if(i < n) {
            aut[i][p[i] - CH] = i + 1;
            j = aut[j][p[i] - CH];
        }
    }
}

int count_str(string &s, /*vector<int> &index*/) {
    int ans = 0, pos = 0, m = s.size();
    for(int i = 0; i < m; i++) {
        pos = aut[pos][s[i] - CH];
        if(pos == n) {
            ans++;
            //index.push_back(i - n + 2);
        }
    }
    return ans;
}