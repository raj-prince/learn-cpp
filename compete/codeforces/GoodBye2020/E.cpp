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
    int n;
    cin >> n;
    
    vector<int> a(n);
    /* brute force */
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    int bruteForce = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                bruteForce += ((a[i] & a[j]) * (a[j] | a[k]));
            }
        }
    }
    cout << bruteForce << '\n';
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