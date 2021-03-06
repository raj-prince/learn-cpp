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

struct node {
    int maxSum = 0;
    int lMaxSum = 0;
    int rMaxSum = 0;
    int totalSum = 0;
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
        res.totalSum = a.totalSum + b.totalSum;
        res.lMaxSum = max(a.lMaxSum, a.totalSum + b.lMaxSum);
        res.rMaxSum = max(a.rMaxSum + b.totalSum, b.rMaxSum);
        
        res.maxSum = max(a.maxSum, b.maxSum);
        res.maxSum = max(res.maxSum, res.lMaxSum);
        res.maxSum = max(res.maxSum, res.rMaxSum);
        res.maxSum = max(res.maxSum, a.rMaxSum + b.lMaxSum);
        
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
    int n;
    cin >> n;
    
    vector<node> a(n);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        
        a[i] = {x, x, x, x};
    }
    
        
    SegmentTree st(a);
    int m;
    cin >> m;
    
    while (m--) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        
        cout << st.query(x, y).maxSum << '\n';
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
//    cin >> test;
    
    for (int tc = 1; tc <= test; tc++)
        SolveTestCase(tc);
        
    return 0;
}
