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

inline bool IsLCM(const string& a, const string& b) {
    int la = (int) a.size();
    int lb = (int) b.size();
    
    if (la % lb != 0) return false;
    
    for (int i = 0; i < la; i += lb) {
        if (a.substr(i, lb) != b)
            return false;
    }
    return true;
}

void SolveTestCase(int testCase = 1) {
    string a, b;
    cin >> a >> b;
    
    if (a.size() < b.size())
        swap(a, b);
        
    
    string z = "";
    for (int i = 0; i < (int) b.size(); i++) {
        z = z + a;
        if (IsLCM(z, b)) {
            cout << z << '\n';
            return;
        }
    }
    cout << "-1" << '\n';
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

