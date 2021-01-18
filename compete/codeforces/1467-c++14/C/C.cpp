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

using ll = long long;

void SolveTestCase(int testCase = 1) {
    int n1, n2, n3;
    cin >> n1 >> n2 >> n3;
    
    vector<ll> a(n1), b(n2), c(n3);
    ll suma = 0, sumb = 0, sumc = 0;
    
    for (int i = 0; i < n1; i++) {
        cin >> a[i];
        suma += a[i];
    }
    
    for (int i = 0; i < n2; i++) {
        cin >> b[i];
        sumb += b[i];
    }
    
    for (int i = 0; i < n3; i++) {
        cin >> c[i];
        sumc += c[i];
    }
    
    ll mina = *min_element(a.begin(), a.end());
    ll minb = *min_element(b.begin(), b.end());
    ll minc = *min_element(c.begin(), c.end());
    
    ll ans = 0;
    ans = max(ans, suma + sumb - sumc);
    ans = max(ans, suma + sumc - sumb);
    ans = max(ans, sumc + sumb - suma);
    
    ll total = suma + sumb + sumc;
    ans = max(ans, total - 2 * (mina + minb));
    ans = max(ans, total - 2 * (minb + minc));
    ans = max(ans, total - 2 * (mina + minc));
    
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
//    cin >> test;
    
    for (int tc = 1; tc <= test; tc++)
        SolveTestCase(tc);
        
    return 0;
}

