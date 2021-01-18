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
    while (true) {
        int k;
        cin >> k;
        
        if (k == 0) break;
        
        string s;
        cin >> s;
        
        int n = s.size();
        
        string s1 = "";
        for (int i = 0; i < n / k; i++) {
            string sub = s.substr((i * k), k);
            
            if (i & 1) {
                reverse(sub.begin(), sub.end());
            }
            
            s1 = s1 + sub;
        }
        
//        dbg(s1);
        
        string res = "";
        for (int kk = 0; kk < k; kk++) {
            for (int i = 0; i < (n / k); i++) {
                res.push_back(s1[kk + i * k]);
            }
        }
        
        cout << res << '\n';
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
