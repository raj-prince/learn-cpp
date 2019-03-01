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

    inline int get_size() {
        int _sz = static_cast<int>(v.size());
        return _sz;
    }
};

int main() {
    FenwickTree<int> fenwick_tree(10);
    for (int i = 0; i < 10; i++) {
        fenwick_tree.add(i, i);
    }
    cout << "[0, 3] Sum: " << fenwick_tree.range_sum(0, 3) << endl;
    return 0;

}