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

#ifdef LOCAL
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

using ll = long long;

void SolveTestCase(int testCase = 1) {
    int n;
    cin >> n;
    
    assert(n == 1);
    
    int m;
    cin >> m;
    
    vector<int> x(m);
    for (int i = 0; i < m; i++) {
        cin >> x[i];
    }
    
    vector<ll> fp(m, 0), fn(m, 0), bp(m, 0), bn(m, 0);
    for (int i = 0; i < m ; i++) {
        fp[i] = (int) (x[i] > 0);
        fn[i] = (int) (x[i] < 0);
        if (i - 1 >= 0) {
            fp[i] += fp[i - 1];
            fn[i] += fn[i - 1];
        }
    }
    
    for (int i = m - 1; i >= 0; i--) {
        bp[i] = (int) (x[i] > 0);
        bn[i] = (int) (x[i] < 0);
        if (i + 1 < m) {
            fp[i] += fp[i + 1];
            fn[i] += fn[i + 1];
        }
    }
    
    ll ans = 0;
    for (int i = 0; i < m; i++) {
        ll ansi = 0;
        if (x[i] > 0) {
            if (fn[i] > 0) ansi += (i > 0 && x[i - 1] < 0) ? i : max(0, i - 1);
        } else {
            if (bp[i] > 0) ans += (i + 1 < m && x[i + 1] > 0) ? (m - 1 - i) : max(0, m - 1 - i - 1);
        }
        ans += ansi;
    }
    
    cout << ans / 2 << '\n';
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

