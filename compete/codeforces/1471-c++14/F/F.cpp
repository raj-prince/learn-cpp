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

#ifdef LOCAL
#define dbg(...) dbs(#__VA_ARGS__, __VA_ARGS__)
#else
#define dbg(...) 42
#endif

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

void dfs(const UndiGraph<int>& g, vector<int>& color, int cur) {
    
    if (color[cur] == 1) {
        vector<int> dfs_next;
        for (int id: g.adj[cur]) {
            auto edge = g.edges[id];
            int v = cur ^ edge.to ^ edge.from;
            
            if (color[v] == 0) {
                dfs_next.push_back(v);
                color[v] = 2;
            }
        }
        
        for (int w: dfs_next) {
            dfs(g, color, w);
        }
    } else {
        for (int id: g.adj[cur]) {
            auto edge = g.edges[id];
            int v = cur ^ edge.to ^ edge.from;
            
            if (color[v] == 0) {
                color[v] = 1;
                dfs(g, color, v);
            }
        }
    }
}

void SolveTestCase(int testCase = 1) {
    int n, m;
    cin >> n >> m;
    
    UndiGraph<int> g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        
        g.add(u, v);
    }
    
    vector<int> color(n, 0);
    color[0] = 1;
    dfs(g, color, 0);
    
    bool exist = true;
    vector<int> res;
    for (int i = 0; i < n; i++) {
        if (color[i] == 0) {
            exist = false;
            break;
        }
        if (color[i] == 1) {
            res.push_back(i);
        }
    }
    
    if (!exist) {
        cout << "NO" << '\n';
    } else {
        cout << "YES" << '\n';
        cout << res.size() << '\n';
        for (int i = 0; i < (int) res.size(); i++) {
            if (i > 0) {
                cout << ' ';
            }
            cout << res[i] + 1;
        }
        cout << '\n';
    }
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

