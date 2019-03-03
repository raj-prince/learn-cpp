#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

struct node {
    int mx;
    int lazy;
    bool on;

    node(int _mx = -1, bool _on = false, int _lazy = 0) {
        mx = _mx;
        on = _on;
        lazy = _lazy;
    }

    // apply lazy on the node.
    void apply(int l, int r, int v) {
        on = true;
        lazy = v;
        mx = v;
    }
};

class SegmentTree {
    vector<node> tree;
    int n;

public:
    SegmentTree(int _n) {
        assert(_n > 0);
        tree.resize(2 * _n - 1);
        n = _n;
        build(0, 0, n - 1);
    }

    SegmentTree(const vector<node>& v) {
        n = static_cast<int>(v.size());
        tree.resize(2 * n - 1);
        build(0, 0, n - 1, v);
    }

    void build(int x, int l, int r) {
        if (l == r) {
            return;
        }
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        build(x + 1, l, y);
        build(z, y + 1, r);
        tree[x] = unite(tree[x + 1], tree[z]);
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

    node query(int x, int l, int r, int ll, int rr) {
        if (l >= ll && r <= rr) {
            return tree[x];
        }
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        push(x, l, r); // push lazy to child before visit.
        node res = {};
        if (rr <= y) {
            res = query(x + 1, l, y, ll, rr);
        } else {
            if (ll > y) {
                res = query(z, y + 1, r, ll, rr);
            } else {
                res = unite(query(x + 1, l, y, ll, rr), query(z, y + 1, r, ll, rr));
            }
        }
        pull(x, z); // collect data from child.
        return res;
    }

    void modify(int x, int l, int r, int ll, int rr, int val) {
        if (l >= ll && r <= rr) {
            tree[x].apply(ll, rr, val);
            return;
        }
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        push(x, l, r);
        if (ll <= y) {
            modify(x + 1, l, y, ll, rr, val);
        }
        if (rr > y) {
            modify(z, y + 1, r, ll, rr, val);
        }
        pull(x, z);
    }

    inline void pull(int x, int z) {
        tree[x] = unite(tree[x + 1], tree[z]);
    }

    inline void push(int x, int l, int r) {
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1 );
        if (tree[x].on) {
            tree[x + 1].apply(l, y, tree[x].lazy);
            tree[z].apply(y + 1, r, tree[x].lazy);
            tree[x].on = false;
        }
    }

    inline node query(int ll, int rr) {
        return query(0, 0, n - 1, ll, rr);
    }

    inline void modify(int ll, int rr, int val) {
        modify(0, 0, n - 1, ll, rr, val);
    }

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
        int q, a, b, val;
        cin >> q;
        if (q == 1) {
            cin >> a >> b;
            cout << st.query(a, b).mx << endl;
        } else {
            cin >> a >> b >> val;
            st.modify(a, b, val);
        }
    }
}