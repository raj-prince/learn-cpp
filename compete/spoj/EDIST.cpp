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

void SolveTestCase(int testCase = 1) {
    string a, b;
    cin >> a >> b;
    
    int na = (int) a.size();
    int nb = (int) b.size();
    
    vector<vector<int>> dp(na + 1);
    for (int i = 0; i <= na; i++) {
        dp[i].resize(nb + 1, 0);
    }
    
    for (int i = na; i >= 0; i--) {
        for (int j = nb; j >= 0; j--) {
            if (i == na || j == nb) {
                dp[i][j] = max(na - i, nb - j);
            } else {
                // dp[i][j] = max(dp[i][j + 1] + 1, dp[i + 1][j] + 1, dp[i + 1][j + 1] + (s[i] != s[j]))
                dp[i][j] = min(dp[i][j + 1] + 1, min(dp[i + 1][j] + 1, dp[i + 1][j + 1] + (int) (a[i] != b[j])));
            }
        }
    }
    
    cout << dp[0][0] << '\n';
    
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
