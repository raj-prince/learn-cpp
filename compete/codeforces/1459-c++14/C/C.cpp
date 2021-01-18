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

template <typename T>
T gcd(T a, T b) {
    return (a == 0) ? b : gcd(b % a, a);
}

template <typename T>
T lcm(T a, T b) {
    return a / gcd(a, b) * b;
}

using ll = long long;

void SolveTestCase(int testCase = 1) {
    int n, m;
    cin >> n >> m;
    vector<ll> a(n), b(m);
    for (ll &x: a) cin >> x;
    for (ll &y: b) cin >> y;
    
    ll g = 0;
    ll mn = *min_element(a.begin(), a.end());
    for (int i = 0; i < n; i++) {
        ll d = a[i] - mn;
        g = gcd<ll>(g, d);
    }
    
    for (int i = 0; i < m; i++) {
        if (i > 0) cout << ' ';
        
        ll ans = gcd<ll>(g, b[i] + mn);
        cout << ans;
    }
    
    cout << '\n';
    
}
 
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int test = 1;
//    cin >> test;
    
    for (int tc = 1; tc <= test; tc++)
        SolveTestCase(tc);
        
    return 0;
}

