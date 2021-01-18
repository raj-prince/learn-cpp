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


// change mod according to question.
// division only work when mod is prime.

const int mod = (int)1e9 + 7;

// add y to x.
inline void add(int &x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

// subtract y from x.
inline void sub(int &x, int y) {
  x -= y;
  if (x < 0) {
    x += mod;
  }
}

// return x * y.
inline int mul(int x, int y) {
  return (long long) x * y % mod;
}

// return x ^ n.
inline int power(int x, int n) {
  int res = 1;
  while (n > 0) {
    if (n & 1) {
      res = mul(res, x);
    }
    x = mul(x, x);
    n >>= 1;
  }
  return res;
}

// used for division.
inline int invMod(int a) {
  return power(a, mod - 2);
}

// return x / y.
inline int divide(int x, int y) {
  return mul(x, invMod(y));
}


const int N = (int)2e5 + 10;
int f[N];

void CalculateFact() {
    f[0] = 1;
    for (int i = 1; i < N; i++) {
        f[i] = mul(i, f[i - 1]);
    }
}

int CalcNCM(int n, int m) {
//    dbg(n, m);
    if (n < m) return 0;
    
    int ans = f[n];
    int deno = mul(f[m], f[n - m]);
    return divide(ans, deno);
}

void SolveTestCase(int testCase = 1) {
    int n, m, k;
    cin >> n >> m >> k;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    sort(a.begin(), a.end());
    
    int ans = 0;
    
    for (int i = 0; i < n; i++) {
        
        int nxt_pos = upper_bound(a.begin() + i, a.end(), a[i] + k) - a.begin() - 1;
        
        int range_size = nxt_pos - i + 1;
        
        if (range_size >= m) {
//            dbg(i, range_size);
            sub(range_size, 1);
            int NCM = CalcNCM(range_size, m - 1);
//            dbg(NCM, m);
            add(ans, NCM);
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
 
    CalculateFact();
    int test = 1;
    cin >> test;
    
    for (int tc = 1; tc <= test; tc++)
        SolveTestCase(tc);
        
    return 0;
}
