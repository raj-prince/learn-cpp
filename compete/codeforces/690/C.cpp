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

long long rev(long long a) {
    
    long long ret = 0;
    while (a > 0) {
        ret = ret * 10 + (a % 10);
        a = a / 10;
    }
    
    return ret;
}

long long solve(int x) {
    
    if (x > 45)
        return -1;
        
    if (x < 10)
        return x;
        
    if (x <= 17)
        return (x - 9) * 10 + 9;
    
    long long ans = 0;
    for (int i = 9; i >= 1; i--) {
        
        if (x >= i) {
            ans = (ans * 10) + i;
            x -= i;
        }
    }
    
//    dbg(ans);
//    
//    if (x > 0) {
//        ans = (ans * 10) + x;
//    }
    
    return rev(ans);
        
    
        
        
}

void SolveTestCase(int testCase = 1) {
    
    int x;
    cin >> x;
    
    cout << solve(x) << '\n';
    
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
