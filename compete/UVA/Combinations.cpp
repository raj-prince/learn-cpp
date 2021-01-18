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

#define LOCAL

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
/*
nCk = {n * (n - 1)... * (n - k + 1)} / {k * (k - 1)... * 1}
*/
template <typename T>
T WaysToChoose(T n, T k) {
    if (k > n) return 0;
    
    if (k > n - k) k = n - k;
    
    T ans = 1;
    for (T i = 0; i < k; ++i) {
        ans *= (n - i);
        ans /= (i + 1);
    }
    
    return ans;
}

/*
c[n][k] = 1 if (k == 0)
c[n][k] = c[n - 1][k - 1] + c[n - 1][k];
*/
template <typename T>
class BinomialCoefficient {
public:
    BinomialCoefficient(int nn, bool cacheAll = false) : n(nn) {
        InitPascalTraingle();
    }
    
    inline T WaysToChoose(int n, int k) {
        if (k > n | k < 0)
            return 0;
            
        k = min(k, n - k);
        return c[n][k];
    }

private:
    void InitPascalTraingle() {
        c.resize(n + 1);
        c[0].push_back(1);
        for (int i = 1; i <= n; i++) {
            c[i] = c[i - 1];
            for (int k = 1; k < (int) c[i - 1].size(); k++) {
                c[i][k] += c[i - 1][k - 1];
            }
            
            if (i % 2 == 0) {
                c[i].push_back(2 * c[i - 1].back());
            }
        }
    }
    
    int n;
    vector<vector<T>> c;
};

void SolveTestCase(int testCase = 1) {

    BinomialCoefficient<long long> bc(100, true);
    while (true) {
        int n, k;
        cin >> n >> k;
        
        cout << WaysToChoose<long long>(n, k) << '\n';
        if (n == 0 && k == 0) break;
        cout << bc.WaysToChoose(n, k) << '\n';
    }
}
 
int main() {
//#ifdef LOCAL
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
//#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int test = 1;
//    cin >> test;
    
    for (int tc = 1; tc <= test; tc++)
        SolveTestCase(tc);
        
    return 0;
}
