#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <cstring>
#include <iomanip>

using namespace std;
 
#define dbg(...) dbs(#__VA_ARGS__, __VA_ARGS__)
template <class T>
void dbs(string str, T t) {
    cerr << str << " : " << t << "\n";
}
template <class T, class... S>
void dbs(string str, T t, S... s) {
    int idx = str.find(',');
    cerr << str.substr(0, idx) << " : " << t << ",";
    dbs(str.substr(idx + 1), s...);
}
template <class S, class T>
ostream &operator<<(ostream &os, const pair<S, T> &p) {
    return os << "(" << p.first << ", " << p.second << ")";
}
template <class T>
void debug(T a, T b) {
    cerr << "[";
    for (T i = a; i != b; ++i) {
        if (i != a)
            cerr << ", ";
        cerr << *i;
    }
    cerr << "]\n";
}

class Graph {
public:
    Graph(int n) {
        adj.resize(n);
    }
    
    void add(int a, int b) {
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    const vector<int>& GetNeighbours(int a) const {
        return adj[a];
    }
    
private:
    vector<vector<int>> adj;
};

void dfs(const Graph& g, vector<bool>& marked, int cur) {
    marked[cur] = true;
    for (int nbr: g.GetNeighbours(cur)) {
        if (!marked[nbr]) {
            dfs(g, marked, nbr);
        }
    }
}

void SolveTestCase(int testCase = 1) {
    int n, m;
    cin >> n >> m;
    
    Graph g(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        
        a--; b--;
        g.add(a, b);
    }
    
    vector<bool> marked(n, false);
    dfs(g, marked, 0);
    
    bool tree = (m == n - 1);
    
    for (int i = 0; i < n; i++) {
        tree = tree && marked[i];
    }
    
    cout << (tree ? "YES" : "NO") << '\n';
}
 
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int test = 1;
//    cin >> test;
    
    for (int tc = 1; tc <= test; tc++)
        SolveTestCase(tc);
        
    return 0;
}
