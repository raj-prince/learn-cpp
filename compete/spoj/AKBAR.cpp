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
#include <numeric>
#include <cassert>

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

template <typename T>
class Graph {
public:
    struct Edge {
        int from;
        int to;
        T cost;
    };
    
    Graph(int _n) : n(_n) {
        adj.resize(_n);
    }
    
    vector<Edge> edges;
    vector<vector<int>> adj;
    int n;
    
    virtual int add(int from, int to, T cost) = 0;
};

template <typename T>
class UndiGraph : public Graph<T> {
public:
    using Graph<T>::edges;
    using Graph<T>::adj;
    using Graph<T>::n;
    
    UndiGraph(int n) : Graph<T>(n) {}
    
    int add(int from, int to, T cost = 1) {
        assert(from >= 0 && from < n);
        assert(to >= 0 && to < n);
        
        int edgeId = (int) edges.size();
        adj[from].push_back(edgeId);
        adj[to].push_back(edgeId);
        edges.push_back({from, to, cost});
        
        return edgeId;
    }
};

bool dfs(const UndiGraph<int>& g, int v, vector<int>& mark, int dfs_number, int strength) {
    if (mark[v] && mark[v] != dfs_number)
        return false;
        
    mark[v] = dfs_number;
    
    if (strength == 0) return true;
    
    for (int id: g.adj[v]) {
        auto edge = g.edges[id];
        int to = v ^ edge.from ^ edge.to;
        
        /* Important: We can go the visited not further, maybe the new visite will be with more strength */
        bool goodPlacement = dfs(g, to, mark, dfs_number, strength - 1);
        if (!goodPlacement) return false;
    }
    
    return true;
}

void SolveTestCase(int testCase = 1) {
    int n, r, m;
    cin >> n >> r >> m;
    
    UndiGraph<int> g(n);
    for (int i = 0; i < r; i++) {
        int a, b;
        cin >> a >> b;
        
        a--; b--;
        g.add(a, b);
    }
    
    vector<int> mark(n, 0);
    
    bool goodPlacement = true;
    
    for (int i = 1; i <= m; i++) {
        int k, s;
        cin >> k >> s;
        k--;
        
        goodPlacement = goodPlacement && dfs(g, k, mark, i, s);
    }
    
    for (int i = 0; i < n; i++) {
        if (goodPlacement && mark[i] == 0) {
            goodPlacement = false;
            break;
        }
    }
    cout << (goodPlacement ? "Yes" : "No") << '\n';
}
 
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int test = 1;
    cin >> test;
    
    for (int tc = 1; tc <= test; tc++)
        SolveTestCase(tc);
        
    return 0;
}

