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

using LL = long long;
const int INF = (int) 1e9 + 10;

struct node {
    int minIndex;
    int val;
};

class SegmentTree {

public:
    SegmentTree(int _n) : n(_n) { // initialize with default value.
        tree.resize(2 * _n - 1);
        build(0, 0, _n - 1);
    }

    SegmentTree(const vector<node>& v) { // initialize with initial array.
        n = (int) v.size();
        tree.resize(2 * n - 1);
        build(0, 0, n - 1, v);
    }

    // user-friendly
    inline node query(int ll, int rr) {
        return query(0, 0, n - 1, ll, rr);
    }

    // user-friendly.
    inline void modify(int pos, const node& val) {
        modify(0, 0, n - 1, pos, val);
    }
    
private:
    inline void pull(int x, int z) {
        tree[x] = unite(tree[x + 1], tree[z]);
    }
    
    // modify it accordingly.
    inline node unite(const node& a, const node& b) {
        node res;
        if (a.val < b.val) {
            res = a;
        } else {
            if (a.val == b.val) {
                res = {min(a.minIndex, b.minIndex), a.val};
            } else {
                res = b;
            }
        }
        
        return res;
        
    }
    
    void build(int x, int l, int r) {
        if (l == r) {
            tree[x] = node();
            return;
        }
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        build(x + 1, l, y);
        build(z, y + 1, r);
        pull(x, z);
    }
    
    void build(int x, int l, int r, const vector<node>& v) {
        if (l == r) {
            tree[x] = v[l];
            return;
        }
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        build(x + 1, l, y, v);
        build(z, y + 1, r, v);
        pull(x, z);
    }
    
    // put val at x.
    void modify(int x, int l, int r, int pos, const node& val) {
        if (l == r) {
            tree[x] = val;
            return;
        }
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        if (pos <= y) {
            modify(x + 1, l, y, pos, val);
        } else {
            modify(z, y + 1, r, pos, val);
        }
        pull(x, z);
    }
    
    // query
    node query(int x, int l, int r, int ll, int rr) {
        if (l >= ll && r <= rr) {
            return tree[x];
        }
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        if (rr <= y) {
            return query(x + 1, l, y, ll, rr);
        } else {
            if (ll > y) {
                return query(z, y + 1, r, ll, rr);
            } else {
                return unite(query(x + 1, l, y, ll, rr), query(z, y + 1, r, ll, rr));
            }
        }
    }
    
    vector<node> tree;
    int n;
};


void SolveTestCase(int testCase = 1) {
    int n, m;
    cin >> n >> m;
    
    vector<int> idx(n);
    for (int i = 0; i < n; i++) {
        cin >> idx[i];
        idx[i]--;
    }
    
    sort(idx.begin(), idx.end());
    
    vector<int> cost(m);
    vector<node> v;
    for (int i = 0; i < m; i++) {
        cin >> cost[i];
        v.push_back({i, cost[i]});
    }
    
    SegmentTree st(v);
    
    LL ans = 0;
    for (int i = 0; i < n; i++) {
        
        int friendIdx = idx[i];
        auto q = st.query(0, friendIdx);
//        dbg(friendIdx, q.val, q.minIndex);
        
        if (q.val == INF || q.val >= cost[friendIdx]) {
            ans += cost[friendIdx];
        } else {
            ans += q.val;
            st.modify(q.minIndex, {q.minIndex, cost[friendIdx]});
        }
//        dbg(ans);
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
