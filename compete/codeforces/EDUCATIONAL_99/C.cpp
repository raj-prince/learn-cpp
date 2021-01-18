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

void SolveTestCase(int testCase = 1) {
    int n, x;
    cin >> n >> x;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    if (is_sorted(a.begin(), a.end())) {
        cout << 0 << '\n';
    } else {
        vector<int> b(a);
        sort(b.begin(), b.end());
        
        int pos_x = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] != b[i])
            
        }
        
        if (pos_x == n) {
            cout << -1 << '\n';
        } else {
            int ans = 0;
            
            while (pos_x < n && !is_sorted(a.begin(), a.end())) {
                if (a[pos_x] > x) {
                    swap(a[pos_x], x);
                    ans++;
                }
                pos_x++;
            }
            
//            debug(a.begin(), a.end());
            
            if (is_sorted(a.begin(), a.end())) {
                cout << ans << '\n';
            } else {
                cout << -1 << '\n';
            }
        }
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
