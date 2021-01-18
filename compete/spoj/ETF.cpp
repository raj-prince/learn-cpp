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
#include <functional>
#include <cmath>

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

/* Euler Totient Function (Phi): number of x in [1, n] suh that gcd(x, n) = 1 */
class PhiCache {
public:
    PhiCache(int nn) : n(nn) {
        phi.resize(n + 1);
        iota(phi.begin(), phi.end(), 0);
        RunSieve();
    }
    
    int GetPhi(int x) {
        return phi[x];
    }
private:
    void RunSieve() {
        for (int i = 2; i <= n; i++) {
            if (phi[i] == i) {
                for (int j = i; j <= n; j += i) {
                    phi[j] -= (phi[j] / i);
                }
            }
        }
    }
    
    vector<int> phi;
    int n;
};

void SolveTestCase(int testCase = 1) {
    int N = 1000000;
    PhiCache phi(N);
    int t;
    cin >> t;
    
    while (t-- > 0) {
        int n;
        cin >> n;
        
        cout << phi.GetPhi(n) << '\n';
    }
    
}
 
int main() {
#ifdef FILE_IO
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
