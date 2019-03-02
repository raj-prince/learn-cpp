#include <iostream>
#include <vector>

using namespace std;

class UnionFind {
    vector<int> p, r, sz; // parent, rank and size vector.

public:
    UnionFind(int _n = 0) {
        r.resize(_n, 0);
        p.resize(_n, 0);
        sz.resize(_n, 1);
        for (int i = 0; i < _n; i++) {
            p[i] = i;
        }
    }

    inline bool is_same_set(int i, int j) {
        return find_set(i) == find_set(j);
    }

    int find_set(int i) {
        if (p[i] != i) {
            p[i] = find_set(p[i]); // path compression heuristic.
        }
        return p[i];
    }

    void union_set(int i, int j) {
        if (!is_same_set(i, j)) {
            int pi = find_set(i);
            int pj = find_set(j);
            if (r[pi] > r[pj]) { // rank heuristic.
                p[pj] = pi;
                sz[pi] += sz[pj];
            } else {
                p[pi] = pj;
                sz[pj] += sz[pi];
                if (r[pi] == r[pj]) {
                    r[pj]++;
                }
            }
        }
    }

    // return number of disjoint set.
    inline int disjoint_set() {
        int _sz = static_cast<int>(p.size());
        int cnt = 0;
        for (int i = 0; i < _sz; i++) {
            if (p[i] == i) {
                cnt++;
            }
        }
        return cnt;
    }

    // return size of set, in which i belong to.
    inline int size_of_set(int i) {
        int pi = find_set(i);
        return sz[pi];
    }

    inline void clear() {
        p.clear();
        r.clear();
        sz.clear();
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    UnionFind uf(n);
    while (m-- > 0) {
        int x, y;
        cin >> x >> y;
        uf.union_set(x, y);
    }
    cout << uf.disjoint_set() << endl;
    for (int i = 0; i < n; i++) {
        cout << i << " " << uf.size_of_set(i) << endl;
    }
}
