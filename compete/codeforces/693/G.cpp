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
class DiGraph : public Graph<T> {
public:
    using Graph<T>::edges;
    using Graph<T>::adj;
    using Graph<T>::n;
    
    DiGraph(int n) : Graph<T>(n) {}
    
    int add(int from, int to, T cost = 1) {
        assert(from >= 0 && from < n);
        assert(to >= 0 && to < n);
        
        int edgeId = (int) edges.size();
        adj[from].push_back(edgeId);
        edges.push_back({from, to, cost});
        
        return edgeId;
    }
    
    DiGraph<T> reverse() const {
        DiGraph<T> rdg(n);
        for (auto &e: edges) {
            rdg.add(e.to, e.from, e.cost);
        }
        
        return rdg;
    }
};

vector<int> BFS(const DiGraph<int>& g) {
    vector<int> d(g.n, -1);
    
    queue<int> q;
    q.push(0);
    d[0] = 0;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (int id: g.adj[u]) {
            auto e = g.edges[id];
            int v = u ^ e.from ^ e.to;
            
            if (d[v] == -1) {
                d[v] = d[u] + 1;
                q.push(v);
            }
        }
    }
    
    return d;
}


void SolveTestCase(int testCase = 1) {
    int n, m;
    cin >> n >> m;
    
    DiGraph<int> g(n);
    
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        g.add(u, v);
    }
    
    vector<int> d = BFS(g);
    
    vector<vector<int>> cache(n, vector<int>());
    for (int i = 0; i < n; i++) {
        cache[d[i]].push_back(i);
    }
    
    vector<int> minReachable(n, n + 1);
    
    for (int i = n - 1; i >= 0; i--) {
        for (int u: cache[i]) {
            minReachable[u] = d[u];
            for (int id: g.adj[u]) {
                auto e = g.edges[id];
                int v = u ^ e.from ^ e.to;
                
                if (d[u] < d[v]) {
                    minReachable[u] = min(minReachable[u], minReachable[v]);
                }
            }
        }
    }
    
//    debug(minReachable.begin(), minReachable.end());
    
    vector<int> ans(n, n + 1);
    for (int u = 0; u < n; u++) {
        ans[u] = minReachable[u];
        
        for (int id: g.adj[u]) {
            auto e = g.edges[id];
            int v = u ^ e.from ^ e.to;
            
            ans[u] = min(ans[u], minReachable[v]);
        }
    }
    
    
    for (int i = 0; i < n; i++) {
        if (i > 0) {
            cout << ' ';
        }
        cout << ans[i];
    }
    cout << '\n';
    
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
