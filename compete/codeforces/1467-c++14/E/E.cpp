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
class Forest : public Graph<T> {
public:
    using Graph<T>::edges;
    using Graph<T>::adj;
    using Graph<T>::n;
    
    Forest(int _n) : Graph<T>(_n) {}
    
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

template <typename T>
class DFSForest : public Forest<T> {
public:
    using Forest<T>::edges;
    using Forest<T>::adj;
    using Forest<T>::n;
    
    vector<int> pv; // parent vertex
    vector<int> pe; // parent edge
    vector<int> order; // dfs order
    vector<int> spos; // start position of subtree rooted at i
    vector<int> epos; // end position of subtree rooted at i
    vector<int> sz; // size of a subtree rooted at i
    vector<int> root; // root of the tree in which i present
    vector<int> depth; // depth of ith node in the tree
    vector<T> dist;
    
    DFSForest(int _n) : Forest<T>(_n) {
        Init();
    }
    
    void DoDFS(int v, bool reInitEverything = false) {
        if (reInitEverything) {
            Clear();
            Init();
        }
        dfsFrom(v);
    }
    
    void DoDFSAll() {
        for (int i = 0; i < n; i++) {
            if (depth[i] == -1) {
                dfsFrom(i);
            }
        }
    }
    
private:
    void dfs(int v) {
        spos[v] = (int) order.size();
        order.push_back(v);
        sz[v] = 1;
        
        for (int id: adj[v]) {
            if (id == pe[v]) continue;
            const auto& e = edges[id];
            
            int to = e.from ^ e.to ^ v;
            depth[to] = depth[v] + 1;
            dist[to] = dist[v] + e.cost;
            pv[to] = v;
            pe[to] = id;
            root[to] = (root[v] != -1) ? root[v] : to;
            dfs(to);
            sz[v] += sz[to];
        }
        epos[v] = (int) order.size() - 1;
    }
    
    void dfsFrom(int v) {
        depth[v] = 0;
        dist[v] = T{};
        root[v] = v;
        pv[v] = pe[v] = -1;
        dfs(v);
    }
    
    void Init() {
        pv.resize(n, -1);
        pe.resize(n, -1);
        order.clear();
        spos.resize(n, -1);
        epos.resize(n, -1);
        sz.resize(n, 0);
        root.resize(n, -1);
        depth.resize(n, -1);
        dist.resize(n);
    }
    
    void Clear() {
        pv.clear();
        pe.clear();
        order.clear();
        spos.clear();
        epos.clear();
        sz.clear();
        root.clear();
        depth.clear();
        dist.clear();
    }
};

void SolveTestCase(int testCase = 1) {
    int n;
    cin >> n;
    
    int compressorId = 0;
    map<int, int> compress;
    vector<int> a(n);
    for (int &x: a) {
        cin >> x;
        
        if (compress.find(x) == compress.end())
            compress[x] = compressorId++;
            
        x = compress[x];
    }
    
    DFSForest<int> tree(n);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        
        tree.add(u, v);
    }
    tree.DoDFS(0);
    
    /* Initialize a[i] to order sequence id mapping */
    /* here orderSequences[x] vector of all the sequenceId whose value is x. */
    vector<vector<int>> orderSequences(n, vector<int>());
    for (int v: tree.order) {
        orderSequences[a[v]].push_back(tree.spos[v]);
    }
    
    /* Get Count with value as val in the subtree rooted at node */
    auto GetCountInSubtree = [&] (int node, int val) -> int {
        int low = lower_bound(orderSequences[val].begin(), orderSequences[val].end(), tree.spos[node]) - orderSequences[val].begin();
        int high = upper_bound(orderSequences[val].begin(), orderSequences[val].end(), tree.epos[node]) - orderSequences[val].begin();
        
        return high - low;
    };
        
    /* Initialize children vector for every node */
    vector<vector<int>> children(n, vector<int>());
    for (int i = 0; i < n; i++) {
        if (tree.pv[i] != -1)
            children[tree.pv[i]].push_back(i);
    }
    
    vector<int> sum(n + 1, 0);
    for (int i = 0; i < n; i++) {
        
        int totalCount = orderSequences[a[i]].size();
        dbg(i, totalCount);
        
        for (int child : children[i]) {
        
            int subtreeCount = GetCountInSubtree(child, a[i]);
            
            if (subtreeCount > 0) {
                sum[0]++;
                sum[tree.spos[child]]--;
                
                sum[tree.epos[child] + 1]++;
                sum[n]--;
            }
        }
        
        int curCount = GetCountInSubtree(i, a[i]);
        dbg(i, curCount);
        
        if (curCount < totalCount) {
            sum[tree.spos[i]]++;
            sum[tree.epos[i] + 1]--;
        }
    }
    
    for (int i = 1; i < n; i++) {
        sum[i] += sum[i - 1];
    }
    
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (sum[i] == 0) ans++;
    }
    
    cout << ans << '\n';
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

