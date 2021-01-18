
/* Think as dynamic array to get cumulative sum: 0-indexing [0, n - 1] */
template <class T>
class FenwickTree {

public:
    FenwickTree(int n = 0) {
        v.resize(n + 1, 0);
    }

    /* Increment with val on index in the original array x */
    void Increment(int x, T val) {
        x++; // 0-indexing.
        int sz = (int) v.size();
        while (x < sz) {
            v[x] += val;
            x = (x | (x - 1)) + 1; // add: value as last significant bit.
        }
    }

    /* Returns sum of the value from [0, x] in the original array. */
    T GetCumulativeSum(int x) {
        x++; // 0-indexing.
        T ans = 0;
        while (x > 0) {
            ans += v[x];
            x &= (x - 1); // remove: value as last significant bit.
        }
        return ans;
    }

    T GetRangeSum(int l, int r) {
        return GetCumulativeSum(r) - GetCumulativeSum(l - 1);
    }

    // lower-bound over cumulative-sum array.
    int LowerBound(T x) {
        int sz = (int) v.size();
        int mask = (1 << MaxSetBit(sz));
        int idx = 0;
        while (mask > 0 && idx < sz) {
            int tempIdx = idx + mask;
            if (x >= v[tempIdx]) {
                idx = tempIdx;
                x -= v[tempIdx];
            }
            mask >>= 1;
        }
        return (idx - 1); // for 0-indexing.
    }

    // upper-bound over cumulative-sum array.
    int UpperBound(T x) {
        return UpperBound(x + 1);
    }
    
private:
    inline int MaxSetBit(int x) {
        return (31 - __builtin_clz(x)); // 0-indexing.
    }
    
    vector<T> v;
};
