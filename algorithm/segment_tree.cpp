#include <iostream>
#include <vector>

using namespace std;

struct node {
    int mx = -1;

    node(int _mx = -1) {
        mx = _mx;
    }
};

class SegmentTree {
    vector<node> tree;
    int n;

public:
    SegmentTree(int _n) { // initialize with default value.
        assert(_n > 0);
        n = _n;
        tree.resize(2 * _n - 1);
        build(0, 0, _n - 1);
    }

    SegmentTree(const vector<node>& v) { // initialize with initial array.
        int _n = static_cast<int>(v.size());
        n = _n;
        tree.resize(2 * _n - 1);
        build(0, 0, _n - 1, v);
    }

    void build(int x, int l, int r) {
        if (l == r) {
            // do something here if required.
            return;
        }
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        build(x + 1, l, y);
        build(z, y + 1, r);
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
        tree[x] = unite(tree[x + 1], tree[z]);
    }

    // put val at x.
    void modify(int x, int l, int r, int pos, int val) {
        if (l == r) {
            tree[x] = node(val);
            return;
        }
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        if (pos <= y) {
            modify(x + 1, l, y, pos, val);
        } else {
            modify(z, y + 1, r, pos, val);
        }
        tree[x] = unite(tree[x + 1], tree[z]);
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

    // user-friendly
    inline node query(int ll, int rr) {
        return query(0, 0, n - 1, ll, rr);
    }

    // user-friendly.
    inline void modify(int pos, int val) {
        modify(0, 0, n - 1, pos, val);
    }

    // modify it accordingly.
    inline node unite(const node& a, const node& b) {
        return node(max(a.mx, b.mx));
    }

    inline void clear() {
        tree.clear();
    }
};

int main() {
    int n;
    cin >> n;
    vector<node> v;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        v.emplace_back(node(x));
    }

    SegmentTree st(v);

    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int q, a, b;
        cin >> q >> a >> b;
        if (q == 1) {
            cout << st.query(a, b).mx << endl;
        } else {
            st.modify(a, b);
        }
    }
}