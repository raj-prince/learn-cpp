#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <algorithm>
#include <assert.h>

using namespace std;

struct node {
    int o, c, m;

    node(int _o = 0, int _c = 0, int _m = 0): o(_o), c(_c), m(_m) {}
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

    inline void pull(int x, int z) {
        tree[x] = unite(tree[x + 1], tree[z]);
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
        int match = min(a.o, b.c);
		int _o = a.o + b.o - match;
		int _c = a.c + b.c - match;
		int _m = a.m + b.m + match + match;
		return node(_o, _c, _m);
    }

    inline void clear() {
        tree.clear();
    }
};

int main() {
	ios::sync_with_stdio(false);
  	cin.tie(0);
	string s;
	cin >> s;
	int m;
	cin >> m;
	vector<node> v;
	for (int i = 0; i < (int)s.size(); i++) {
		if (s[i] == '(') {
			v.emplace_back(node(1, 0, 0));
		} else {
			v.emplace_back(node(0, 1, 0));
		}
	}
	SegmentTree st(v);
	for (int i = 0; i < m; i++) {
		int l, r;
		cin >> l >> r;
		l--; r--;
		cout << st.query(l, r).m << '\n';
	}
}