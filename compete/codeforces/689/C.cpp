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
 
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int test;
    cin >> test;
    
    while (test-- > 0) {
        int n, m;
        cin >> n >> m;
        
        vector<int> a(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        
        int lastUnsortedIndex = -1;
        for (int i = n; i > 0; i--) {
            if (a[i] != i) {
                lastUnsortedIndex = i;
                break;
            }
        }
        double ans = 1.0;
        for (int i = 0; i < m; i++) {
            int r;
            double p;
            cin >> r >> p;
            
            if (r >= lastUnsortedIndex) {
                ans *= (1.0 - p);
            }
        }
        
        if (lastUnsortedIndex == -1)
            ans = 0.0;
        
        cout << fixed << setprecision(10) << (1 - ans) << '\n';
    }
    
    
    return 0;
}
