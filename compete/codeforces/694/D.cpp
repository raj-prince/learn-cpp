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
 
#ifdef LOCAL
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

class Solver {
    static const int N = (int) 1e6 + 100;
    
public:
    Solver() {
        a.resize(N, 1);
        PreProcess();
    }
    
    inline int GetAdjacent(int x) const {
        return a[x];
    }
    
private:
    void PreProcess() {
        for (int i = 2; i < N; i++) {
            int tmp = i;
            for (int j = 2; j * j <= i; j++) {
                
                if (tmp % j == 0) {
                    int cnt = 0;
                    while (tmp % j == 0) {
                        cnt++;
                        tmp /= j;
                    }
                    
                    if (cnt % 2 == 1) {
                        a[i] *= j;
                    }
                }
            }
            
            if (tmp > 1) {
                a[i] *= tmp;
            }
        }
    }
    
    vector<int> a;
};

void SolveTestCase(const Solver& solver) {
    int n;
    cin >> n;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i] = solver.GetAdjacent(a[i]);
    }
    
//    sort(a.begin(), a.end());
//    debug(a.begin(), a.end());
    
    map<int, int> m;
    for (int x: a) {
        m[x] += 1;
    }
    
    int one_count = 0;
    int mx = 0;
    int evenmx = 0;
    for (auto p: m) {
        if (p.first == 1) {
            one_count = p.second;
        } else {
            if (p.second % 2 == 0) {
                evenmx += p.second;
            }
        }
        mx = max(mx, p.second);
    }
    
    dbg(mx, evenmx, one_count);
    
    int q;
    cin >> q;
    while (q--) {
        long long w;
        cin >> w;
        
        int ans = (w == 0) ? mx : max(mx, evenmx + one_count);
        cout << ans << '\n';
    }
}
 
int main() {
//#ifdef LOCAL
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
//#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    Solver solver;
 
    int test = 1;
    cin >> test;
    
    for (int tc = 1; tc <= test; tc++)
        SolveTestCase(solver);
        
    return 0;
}
