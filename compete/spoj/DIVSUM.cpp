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

class DivSumCache {
public:
    vector<int> divsum;
    
    DivSumCache(int n) {
        divsum.resize(n + 1, 1);
        divsum[0] = 0;
        divsum[1] = 0;
        
        for (int i = 2; i <= n; i++) {
            for (int j = i + i; j <= n; j += i) {
                divsum[j] += i;
            }
        }
    }
};

void SolveTestCase(int testCase = 1) {
    DivSumCache cache(500000);
    int t;
    cin >> t;
    
    while (t-- > 0) {
        int n;
        cin >> n;
        
        cout << cache.divsum[n] << '\n';
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