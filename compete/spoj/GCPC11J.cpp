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

#ifdef DEBUG
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

int GetDiameter(const UndiGraph<int>& g) {
    int n = g.n;
    vector<int> level(n, -1);
    
    vector<int> q;
    q.push_back(0);
    level[0] = 0;
    
    for (int i = 0; i < (int) q.size(); i++) {
        int u = q[i];
        for (int id: g.adj[u]) {
            auto e = g.edges[id];
            
            int v = u ^ e.from ^ e.to;
            
            if (level[v] == -1) {
                q.push_back(v);
                level[v] = level[u] + 1;
            }
        }
    }
    
    int s = q.back();
    q.clear();
    q.push_back(s);
    
    level.clear();
    level.resize(n, -1);
    level[s] = 0;
    
    for (int i = 0; i < (int) q.size(); i++) {
        int u = q[i];
        for (int id: g.adj[u]) {
            auto e = g.edges[id];
            int v = u ^ e.from ^ e.to;
            
            if (level[v] == -1) {
                q.push_back(v);
                level[v] = level[u] + 1;
            }
        }
    }
    
    return level[q.back()];
}

void SolveTestCase(int testCase = 1) {
    int n;
    cin >> n;
    
    UndiGraph<int> g(n);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        
        g.add(u, v);
    }
    
    cout << (GetDiameter(g) + 1) / 2 << '\n';
}
 
int main() {
#ifdef FILE_IO
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
