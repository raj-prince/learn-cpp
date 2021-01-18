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
#include <functional>
#include <cmath>

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

class UnionFind {
public:
    UnionFind(int n = 0) {
        r.resize(n, 0);
        p.resize(n, 0);
        iota(p.begin(), p.end(), 0);
        sz.resize(n, 1);
    }
    
    int FindSet(int x) {
        if (p[x] != x) {
            p[x] = FindSet(p[x]); // path compression heuristic.
        }
        return p[x];
    }
    
    /* true: means both x and y were in different set and now merged. */
    bool UnionSet(int x, int y) {
        
        if (IsInSameSet(x, y))
            return false;
        
        int px = FindSet(x);
        int py = FindSet(y);
        
        /* Rank heuristic: Append in the tree of higher rank. */
        /* Think px as the owner of tree with higher rank. */
        if (r[px] < r[py]) {
            swap(px, py);
        }
        
        p[py] = px;
        sz[px] += sz[py];
        
        if (r[px] == r[py]) {
            r[px]++;
        }
        
        return true;
    }
    
private:
    bool IsInSameSet(int x, int y) {
        return FindSet(x) == FindSet(y);
    }
    
    vector<int> p, r, sz; // parent, rank and size.
};

template <typename T>
vector<int> MinimumSpanningTree(const UndiGraph<T>& g) {
    vector<int> edges(g.edges.size());
    iota(edges.begin(), edges.end(), 0);
    
    sort(edges.begin(), edges.end(), [&] (int a, int b) {
        return g.edges[a].cost < g.edges[b].cost;
    });
    
    vector<int> ans;
    UnionFind uf(g.n);
    for (int id: edges) {
        auto e = g.edges[id];
        
        if (uf.UnionSet(e.from, e.to)) {
            ans.push_back(id);
        }
    }
    
    return ans;
}

using pii = pair<int, int>;

double distance(const pii& a, const pii& b) {
    int dx = (a.first - b.first);
    int dy = (a.second - b.second);
    
    return sqrt(dx * dx + dy * dy);
}

void SolveTestCase(int testCase = 1) {
    int n, w;
    double r, u, v;
    cin >> n >> r >> w >> u >> v;
    
    vector<pii> pts(n);
    for (int i = 0; i < n; ++i) {
        cin >> pts[i].first >> pts[i].second;
    }
    
    UndiGraph<double> g(n);
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            double cost = distance(pts[i], pts[j]);
            g.add(i, j, cost);
        }
    }
    
    vector<int> mstEdge = MinimumSpanningTree<double>(g);
    
    double utpCost = 0, ofCost = 0;
    for (int i = 0; i + w - 1 < (int) mstEdge.size(); i++) {
        double edgeCost = g.edges[mstEdge[i]].cost;
        
        if (edgeCost <= r) {
            utpCost += edgeCost * u;
        } else {
            ofCost += (edgeCost * v);
        }
    }
    
    cout << fixed << setprecision(3) << "Caso #" << testCase << ": " << utpCost << " " << ofCost << '\n';
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
