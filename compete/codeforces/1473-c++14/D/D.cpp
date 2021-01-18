//#include <iostream>
//#include <vector>
//#include <stack>
//#include <queue>
//#include <list>
//#include <set>
//#include <map>
//#include <unordered_set>
//#include <unordered_map>
//#include <algorithm>
//#include <cstring>
//#include <iomanip>
//#include <numeric>
//#include <cassert>
#include <bits/stdc++.h>

using namespace std;

#ifdef DEBUG
#define dbg(...) dbs(#__VA_ARGS__, __VA_ARGS__)
#else
#define dbg(...) 42
#endif

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

template <typename T, class F = function<T(const T&, const T&)>>
class SparseTable {
public:
    SparseTable(const vector<T>& a, const F& f) : func(f) {
        n = static_cast<int>(a.size());
        int max_log = 32 - __builtin_clz(n);
        table.resize(max_log);
        table[0] = a;
        
        for (int j = 1; j < max_log; j++) {
            table[j].resize(n - (1 << j) + 1);
            for (int i = 0; i <= n - (1 << j); i++) {
                table[j][i] = func(table[j - 1][i], table[j - 1][i + (1 << (j - 1))]);
            }
        }
    }
    
    T get(int from, int to) const {
        assert(0 <= from && from <= to && to <= n - 1);
        int lg = 32 - __builtin_clz(to - from + 1) - 1;
        return func(table[lg][from], table[lg][to - (1 << lg) + 1]);
    }
    
private:
    int n;
    vector<vector<T>> table;
    F func;
};

inline int GetAnswer(const pair<int, int>& r1, const pair<int, int>& r2) {
    if (r1.second < r2.first ||  r2.second < r1.first) {
        return (r1.second - r1.first + 1) + (r2.second - r2.first + 1);
    }
    
    int mx = max(r1.second, r2.second);
    int mn = min(r1.first, r2.first);
    
    return (mx - mn + 1);
}

void SolveTestCase(int testCase = 1) {
    int n, m;
    cin >> n >> m;
    
    string s;
    cin >> s;
    
    vector<int> a;
    int x = 0;
    a.push_back(x);
    for (int i = 0; i < n; i++) {
        if (s[i] == '-') x--;
        else x++;
        
        a.push_back(x);
    }
    
//    debug(a.begin(), a.end());
    
    auto maxFunc = [] (int a, int b) {
        return max(a, b);
    };
    
    auto minFunc = [] (int a, int b) {
        return min(a, b);
    };
    
    SparseTable<int, decltype(maxFunc)> maxST(a, maxFunc);
    SparseTable<int, decltype(minFunc)> minST(a, minFunc);
    
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        
        auto firstRange = make_pair(minST.get(0, l - 1), maxST.get(0, l - 1));
        
//        dbg(firstRange.first, firstRange.second);
        
        if (r == n) {
            cout << (firstRange.second - firstRange.first + 1) << '\n';
            continue;
        }
        auto secondRange = make_pair(minST.get(r + 1, n), maxST.get(r + 1, n));
        
//        dbg(secondRange.first, secondRange.second);
        
        int diff = a[r] - a[l - 1];
        secondRange.first -= diff;
        secondRange.second -= diff;
        
        cout << GetAnswer(firstRange, secondRange) << '\n';
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
    cin >> test;
    
    for (int tc = 1; tc <= test; tc++)
        SolveTestCase(tc);
        
    return 0;
}

