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

void SolveTestCase(int testCase = 1) {
    
    LL n, x;
    cin >> n >> x;
    
    vector<pair<LL, LL>> v;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        
        v.push_back(make_pair(a, 1));
    }
    
    for (int i = 0; i < (int) v.size(); i++) {
        LL a = v[i].first;
        LL copy = v[i].second;
        
        if (a % x == 0) {
            a /= x;
            copy *= x;
            v.push_back(make_pair(a, copy));
        } else break;
    }
    
    LL ans = 0;
    for (int i = 0; i < (int) v.size(); i++) {
        ans += (v[i].first * v[i].second);
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
