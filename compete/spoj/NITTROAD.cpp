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
    
    bool IsOwner(int x) {
        return (p[x] == x);
    }
    
    int SizeOfSet(int x) {
        return sz[FindSet(x)];
    }
    
private:
    bool IsInSameSet(int x, int y) {
        return FindSet(x) == FindSet(y);
    }
    
    vector<int> p, r, sz; // parent, rank and size.
};

int WaysToChooseTwo(int x) {
    return (x * (x - 1)) / 2;
}

void SolveTestCase(int testCase = 1) {
    int n;
    cin >> n;
    
    vector<pair<int, int>> edge(n - 1);
    
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        
        u--; v--;
        
        edge[i] = make_pair(u, v);
    }
    
    int q;
    cin >> q;
    
    set<int> deleteEdge;
    vector<pair<bool, int>> query(q);
    for (int i = 0; i < q; i++) {
        string s;
        cin >> s;
        
        if (s == "Q") {
            query[i] = make_pair(false, 0);
        } else {
            int id;
            cin >> id;
            
            id--;
            deleteEdge.insert(id);
            query[i] = make_pair(true, id);
        }
    }
    
    
    UnionFind uf(n);
    for (int i = 0; i < n - 1; i++) {
        if (deleteEdge.find(i) == deleteEdge.end()) {
            uf.UnionSet(edge[i].first, edge[i].second);
        }
    }
    
    int currentAnswer = WaysToChooseTwo(n);
    for (int i = 0; i < n; i++) {
        if (uf.IsOwner(i)) {
            int sz = uf.SizeOfSet(i);
            currentAnswer -= WaysToChooseTwo(sz);
        }
    }
    
    vector<int> ans(q, -1);
    for (int i = q - 1; i >= 0; i--) {
        if (!query[i].first) {
            ans[i] = currentAnswer;
        } else {
            int id = query[i].second;
            int u = edge[id].first;
            int v = edge[id] .second;
            
            int szU = uf.SizeOfSet(u);
            int szV = uf.SizeOfSet(v);
            
            currentAnswer += WaysToChooseTwo(szU);
            currentAnswer += WaysToChooseTwo(szV);
            
            currentAnswer -= WaysToChooseTwo(szU + szV);
            
            uf.UnionSet(u, v);
        }
    }
    
    for (int i = 0; i < q; i++) {
        if (ans[i] != -1) {
            cout << ans[i] << '\n';
        }
    }
    cout << '\n';
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
