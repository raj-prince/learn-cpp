#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

// adjacency-list representation.
class Graph {
    vector <vector<int>> g;
    vector <int> state; // white(0), brown(1), black(2)
    
    vector <int> tin, tout; // node visit and node exit time.
                            // useful incase of recursive dfs.
    int n, timer = 0;

public:
    Graph(int _n): n(_n) {
        g.resize(_n);
        timer = 0;
        state.resize(_n, 0);
        tin.resize(_n, -1);
        tout.resize(_n, -1);
    }

    // by default directed graph.
    inline void add(int a, int b, bool directed = true) {
        assert(a >= 0 && a < n);
        assert(b >= 0 && b < n);
        g[a].emplace_back(b);
        if (!directed) {
            g[b].emplace_back(a);
        }
    }

    // recursive.
    void dfs(int a) {
        cout << a << " ";
        state[a] = 1; // not explored yet.
        tin[a] = timer++;
        for (int x: g[a]) {
            if (white(x)) {
                dfs(x);
            }
        }
        tout[a] = timer++;
        state[a] = 2;
    }

    // queue
    void bfs(int start) {
        queue<int> q;
        q.emplace(start);
        state[start] = 1;
        while (!q.empty()) {
            int cur = q.front();
            cout << cur << " ";
            q.pop();
            for (int x: g[cur]) {
                if (white(x)) {
                    q.emplace(x);
                    state[x] = 1;
                }
            }
            state[cur] = 2;
        }
    }

    // stack
    void dfs_stack(int start) {
        stack<int> s;
        s.emplace(start);
        state[start] = 1;
        while (!s.empty()) {
            int cur = s.top();
            cout << cur << " ";
            s.pop();
            // in reverse order, to process first element first in the adjecency list.
            for (auto it = g[cur].crbegin(); it != g[cur].crend(); ++it) {
                int x = *it;
                if (white(x)) {
                    s.emplace(x);
                    state[x] = 1;
                }
            }
            state[cur] = 2;
        }
    }

    inline void reset_flag() {
        timer = 0;
        fill(state.begin(), state.end(), 0);
        fill(tin.begin(), tin.end(), -1);
        fill(tout.begin(), tout.end(), -1);
    }

    inline bool white(int a) {
        return (state[a] == 0);
    }

    inline bool brown(int a) {
        return (state[a] == 1);
    }

    inline bool black(int a) {
        return (state[a] == 2);
    }

    void print() {
        cout << "Tin:";
        for (int x: tin) {
            cout << x << " ";
        }
        cout << "Tout:";
        for (int x: tout) {
            cout << x << " ";
        }
        cout << endl;
    }

};

int main() {
    int n, m;
    cin >> n >> m;
    Graph g(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        g.add(a, b);
    }
    cout << "Recursive DSF: ";
    g.dfs(0);
    cout << endl;
    g.print();
    g.reset_flag();
    cout << "Stack DFS: ";
    g.dfs_stack(0);
    g.reset_flag();
    cout << "\nBFS: ";
    g.bfs(0);
    g.reset_flag();
    cout << endl;
}