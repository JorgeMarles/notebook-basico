const int alfa = 26;
const char L = 'a';

struct node {
    int next[alfa], link, len;
    ll cnt;
    node(int x, int l = 0, ll c = 1): len(x), link(l), cnt(c) {
        memset(next, 0, sizeof next);
    }
    int& operator [] (int i) { return next[i]; }
};

struct palindromic_tree {
    vector<node> tree;
    string s;
    int n;
    int last;
    palindromic_tree(string t = "") {
        n = last = 0;
        tree.pb(node(-1));
        tree.pb(node(0));
        for (auto &c: t)add_char(c);
    }

    int getlink(int p) {
        while (s[n - tree[p].len - 1] != s[n])p = tree[p].link;
        return p;
    }

    void add_char(char ch) {
        s.pb(ch);
        int p = getlink(last), c = ch - L;
        if (!tree[p][c]) {
            int link = getlink(tree[p].link);
            link = max(1, tree[link][c]);
            tree[p][c] = SZ(tree);
            tree.pb(node(tree[p].len + 2, link, 0));
        }
        last = tree[p][c];
        tree[last].cnt++;
        n++;
    }
};

const int F_CHAR = 'a';

struct Node {
	map<int, int> next;
	int link, len, cnt;
	int beginIndex, endIndex;
	
	Node(int _len, int _link = 0, int index) : len(_len), link(_link), cnt(0) {
		if (len > 0) {
			beginIndex = index - len - 1;
			endIndex = index;
		}
		else beginIndex = endIndex = len;
	} 

	int& operator [] (int i) {
		if (next.count(i)) return next[i];
		return -1;
	}
};

struct Palindromic_tree {
	vector<Node> nodes; 
	string str;
	int last;
	
	Palindromic_tree(string s = "") {
		last = 0;
		nodes.push_back(Node(-1));
		nodes.push_back(Node(0));
		for (auto &c : s) add_char(c);
	}
	
	int get_sufix(int p, int index) {
		while (index - nodes[p].len - 1 < 0 || str[index - nodes[p].len - 1] != str[index]) {
			p = nodes[p].link;
		}
		return p;
	}
	
	void add_char(char ch) {
		int index = str.size();
		str += ch;
		int p = get_sufix(last, index), c = ch - F_CHAR;
		if (nodes[p][c] == -1) {
			nodes.push_back(Node(p.len + 2, index));
			nodes[p][c] = last;
			if (nodes[last].len > 1) {
				p = get_link(nodes[p].link, index);
				nodes[last].link = nodes[p][c];
			}
			else {
				nodes[last].link = 1;
			}			
		}
		else {
			last = nodes[p][c];
		}
		nodes[last].cnt++;
	}
};
