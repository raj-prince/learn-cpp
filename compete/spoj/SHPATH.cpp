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


//#ifdef LOCAL
#define dbg(...) dbs(#__VA_ARGS__, __VA_ARGS__)
//#else
//#define dbg(...) 42
//#endif

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

const int kINF = 2147483647;

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

template <typename T>
class Dijkstra {
    using Edge = typename Graph<T>::Edge;
    
public:
    vector<int> pv;
    vector<T> dist;
    
    Dijkstra(const DiGraph<T>& g, int s, T inf) {
        dist.resize(g.n, inf);
        pv.resize(g.n, -1);
        pq = priority_queue<PQNode, vector<PQNode>, Comp>();
        
        RunAlgorithm(g, s);
    }

private:
    void Relaxation(int v, const Edge& e) {
        int w = v ^ e.from ^ e.to;
        if (dist[w] > dist[v] + e.cost) {
            dist[w] = dist[v] + e.cost;
            pv[w] = v;
            pq.push({dist[w], w});
        }
    }
    
    void RunAlgorithm(const DiGraph<T>& g, int source) {
        dist[source] = 0;
        pv[source] = -1;
        pq.push({0, source});
        
        while (!pq.empty()) {
            auto node = pq.top(); pq.pop();
                        
            if (node.d > dist[node.v])
                continue;
            
            for (int id: g.adj[node.v]) {
                Relaxation(node.v, g.edges[id]);
            }
        }
    }
    
    struct PQNode {
        T d; // works as key
        int v; // vertex corresponding to d
        
        PQNode(T dd, int vv) : d(dd), v(vv) {}
    };
    
    struct Comp {
        bool operator()(const PQNode& a, const PQNode& b) {
            return a.d > b.d;
        }
    };
    
    priority_queue<PQNode, vector<PQNode>, Comp> pq;
};


void SolveTestCase(int testCase = 1) {
    int n;
    cin >> n;
    
    map<string, int> index;
    DiGraph<int> g(n);
    for (int i = 0; i < n; i++) {
        string cityName;
        cin >> cityName;
        
        index[cityName] = i;
        
        int nbr;
        cin >> nbr;
        for (int j = 0; j < nbr; j++) {
            int v, cost;
            cin >> v >> cost;
            v--;
            g.add(i, v, cost);
        }
    }
    
    int m;
    cin >> m;
    while (m--) {
        string src, des;
        cin >> src >> des;
        
        int ss = index[src];
        int dd = index[des];
        
        Dijkstra<int> dj(g, ss, kINF);
        cout << dj.dist[dd] << '\n';
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
