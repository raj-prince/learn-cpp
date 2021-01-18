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

using LL = long long;

void SolveTestCase(int testCase = 1) {
    
    while (true) {
        string s;
        cin >> s;
        
        if (s == "0") break;
        
        int n = s.size();
        vector<LL> f(n, 0);
        
        f[0] = 1;
        for (int i = 1; i < n; i++) {
            
            // Case 1: single digit, always valid
            if (s[i] != '0') f[i] = f[i - 1];
            
            // Case 2: Double digit
            if (i >= 1) {
                int dz = (s[i] - '0') + (s[i - 1] - '0') * 10;
                if (dz >= 10 && dz <= 26) {
                    f[i] += ((i >= 2) ? f[i - 2] : 1);
                }
            }
        }
        
        cout << f[n - 1] << '\n';
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
//    cin >> test;
    
    for (int tc = 1; tc <= test; tc++)
        SolveTestCase(tc);
        
    return 0;
}
