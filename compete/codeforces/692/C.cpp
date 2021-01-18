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

// Appending Code for: union_find
class UnionFind {

public:
    UnionFind(int n = 0) {
        r.resize(n, 0);
        p.resize(n, 0);
        sz.resize(n, 1);
        for (int i = 0; i < n; i++) {
            p[i] = i;
        }
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
    
    int GetNumberOfDisjointSet() {
        int n = static_cast<int>(p.size());
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            
            if (p[i] == i)
                cnt++;
        }
        
        return cnt;
    }
    
    /* Get size of set in which x belongs to.*/
    int GetSizeOfSet(int x) {
        int px = FindSet(x);
        return sz[px];
    }
    
private:
    bool IsInSameSet(int x, int y) {
        return FindSet(x) == FindSet(y);
    }
    
    vector<int> p, r, sz; // parent, rank and size.
};



void SolveTestCase(int testCase = 1) {
    int n, m;
    cin >> n >> m;
    
    UnionFind uf(n);
    
    int ans = 0;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        
        x--;
        y--;
        
        if (x != y) {
            ans++;
            
            if (!uf.UnionSet(x, y)) {
                ans++;
            }
        }
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
    cin >> test;
    
    for (int tc = 1; tc <= test; tc++)
        SolveTestCase(tc);
        
    return 0;
}
