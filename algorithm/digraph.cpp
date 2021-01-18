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

/* Returns empty vector, in case of such order doesn't exist.*/
template <typename T>
vector<int> GetTopologicalOrder(const DiGraph<T>& g) {
    vector<int> inDeg(n, 0);
    
    for (auto &e: g.edges) {
        inDeg[e.to]++;
    }
    
    vector<int> topoOrder;
    for (int i = 0; i < g.n; i++) {
        if (inDeg[i] == 0) {
            topoOrder.push_back(i);
        }
    }
    
    for (int i = 0; i < (int) topoOrder.size(); i++) {
        int u = topoOrder[i];
        for (int id: g.adj[u]) {
            int to = edges[id].to;
            if (--inDeg[to] == 0) {
                topoOrder.push_back(to);
            }
        }
    }
    
    if ((int) topoOrder.size() != g.n) {
        return vector<int>();
    }
    
    return topoOrder;
}
