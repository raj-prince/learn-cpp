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

void SolveTestCase(int testCase = 1) {
    int n;
    cin >> n;
    
    vector<int> a(n);
    for (int &x: a)
        cin >> x;
    
    vector<int> b = a;
    sort(b.begin(), b.end());
    
    map<int, int> sortedIndex;
    for (int i = 0; i < n; i++) {
        sortedIndex[b[i]] = i;
    }
    
    FenwickTree<long long> ft(n);
    long long ans = 0;
    for (int i = n - 1; i >= 0; i--) {
        int si = sortedIndex[a[i]];
        ans += ft.GetCumulativeSum(si);
        ft.Increment(si, 1);
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
