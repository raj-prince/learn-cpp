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
    int n;
    cin >> n;
    
    vector<int> l(n), r(n);
    vector<pair<int, int>> segments;
    
    for (int i = 0; i < n; i++) {
        cin >> l[i] >> r[i];
        
        segments.emplace_back(make_pair(l[i], r[i]));
    }
    
    sort(l.begin(), l.end());
    sort(r.begin(), r.end());
    
    int del = n - 1;
    for (auto seg: segments) {
        int curseg_del = 0;
        
        curseg_del += (lower_bound(r.begin(), r.end(), seg.first) - r.begin());
        curseg_del += (l.end() - upper_bound(l.begin(), l.end(), seg.second));
        
        del = min(curseg_del, del);
    }
    
    cout << del << '\n';
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
