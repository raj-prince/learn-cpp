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

using LL = long long;

struct Range {
    LL mx;
    LL mn;
};

inline bool Can(int k, const Range& prev, Range &r, LL h, bool last = false) {
    r.mx = min(prev.mx + k - 1, h + (last ? 0 : (k - 1)));
    r.mn = max(h, prev.mn - k + 1);
    
    if (r.mn > r.mx) {
        return false;
    }
    
    return true;
}

void SolveTestCase(int testCase = 1) {
    int n, k;
    cin >> n >> k;
    
    vector<LL> h(n);
    for (LL &hh: h)
        cin >> hh;
    
    vector<Range> dp(n);
    
    dp[0] = {h[0], h[0]};
    
    for (int i = 1; i < n - 1; i++) {
        if (!Can(k, dp[i - 1], dp[i], h[i])) {
            cout << "NO" << '\n';
            return;
        }
    }
    
    if (!Can(k, dp[n - 2], dp[n - 1], h[n - 1], true)) {
        cout << "NO" << '\n';
    } else {
        cout << "YES" << '\n';
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
