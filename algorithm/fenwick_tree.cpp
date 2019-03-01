#include <iostream>
#include <vector>

using namespace std;

template <class T>
class FenwickTree { // think like 0-based indexing.
    vector<T> v;

public:
    void init(int _sz) {
        v.resize(_sz + 1, 0);
    }

    FenwickTree() {} // default constructor.

    FenwickTree(int _sz = 0) {
        init(_sz);
    } // parameterized constructor.

    // add val on index x.
    void add(int x, T val) {
        x++; // now, think like 0-indexing.
        int sz = get_size();
        while (x < sz) {
            v[x] += val;
            x = (x | (x - 1)) + 1;
        }
    }

    // get sum of elements of [0, x]
    T get(int x) {
        x++; // now will think like 0-indexing.
        T ans = 0;
        while (x > 0) {
            ans += v[x];
            x &= (x - 1);
        }
        return ans;
    }

    T range_sum(int l, int r) {
        return get(r) - get(l - 1);
    }

    void _clear() {
        v.clear();
    }

    // lower-bound over cumulative-sum array.
    int _lower_bound(T x) {
        int sz = get_size();
        int mask = max_power_2(sz);
        int idx = 0;
        while (mask > 0 && idx < sz) {
            int t_idx = idx + mask;
            if (x >= v[t_idx]) {
                idx = t_idx;
                x -= v[t_idx];
            }
            mask >>= 1;
        }
        return (idx - 1); // for 0-indexing.
    }

    // upper-bound over cumulative-sum array.
    int _upper_bound(T x) {
        return _lower_bound(x + 1);
    }

    inline int get_size() {
        int _sz = static_cast<int>(v.size());
        return _sz;
    }

    inline int max_power_2(int x) {
        int last_set_bit = 31 - __builtin_clz(x); // 0-indexing.
        return (1 << last_set_bit);
    }
};

int main() {
    FenwickTree<int> fenwick_tree(10);
    for (int i = 0; i < 10; i++) {
        fenwick_tree.add(i, 1);
    }
    cout << "[0, 3] Sum: " << fenwick_tree.range_sum(0, 3) << endl;
    cout << "Lower Bound: " << fenwick_tree._lower_bound(5) << endl; // 4 (0-indexed)
    cout << "Upper Bound: " << fenwick_tree._upper_bound(5) << endl; // 5 (0-indexed)
    return 0;

}