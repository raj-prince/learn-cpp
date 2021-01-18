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

struct Result {
    int subTreeMax = 0;
    int longestPathFromRoot = 0;
};

Result DFS(const Graph& g, int cur, int parent) {
    
    Result current;
    priority_queue<int, vector<int>> pq;
    for (int nbr: g.GetNeighbours(cur)) {
        
        if (nbr == parent) continue;
        
        Result child = DFS(g, nbr, cur);
        current.subTreeMax = max(current.subTreeMax, child.subTreeMax);
        current.longestPathFromRoot = max(current.longestPathFromRoot, child.longestPathFromRoot + 1);
        pq.push(1 + child.longestPathFromRoot);
    }
    
    if (pq.size() >= 2) {
        int mx1 = pq.top(); pq.pop();
        int mx2 = pq.top(); pq.pop();
        
        current.subTreeMax = max(current.subTreeMax, mx1 + mx2);
    }
    
//    dbg(cur, current.subTreeMax, current.longestPathFromRoot);
    current.subTreeMax = max(current.subTreeMax, current.longestPathFromRoot);
    return current;
}

int GetLongestPathLength(const Graph& g) {
    return DFS(g, 0, -1).subTreeMax;
}

void SolveTestCase(int testCase = 1) {
    int n;
    cin >> n;
    
    Graph g(n);
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        
        g.add(a, b);
    }
    cout << GetLongestPathLength(g) << '\n';
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
