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

bool Isfeasible(int x, int step) {
    return (step >= x && ((step - x) % 2 == 0));
}

inline bool okay(int x, int y, int n) {
    int absx = (x > 0) ? x : -1 * x;
    int absy = (y > 0) ? y : -1 * y;
    
    int stepx = n / 2;
    int stepy = n - stepx;
    
    bool ok1 = Isfeasible(absx, stepx) && Isfeasible(absy, stepy);
    bool ok2 = Isfeasible(absx, stepy) && Isfeasible(absy, stepx);
    
    return ok1 || ok2;
}

void SolveTestCase(int testCase = 1) {
    int n;
    cin >> n;
    
    int limit = 1000;
    
    int ans = 0;
    for (int x = -limit; x <= limit; x++) {
        for (int y = -limit; y <= limit; y++) {
            if (okay(x, y, n)) {
                ans++;
            }
        }
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
//    cin >> test;
    
    for (int tc = 1; tc <= test; tc++)
        SolveTestCase(tc);
        
    return 0;
}

