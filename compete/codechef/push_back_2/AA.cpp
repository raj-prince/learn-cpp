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


vector<int> prime;
 
// Generates prime in the range [0, n)
void GeneratePrime(int n) {
    
    vector<bool> isPrime(n, true);
    isPrime[0] = false;
    isPrime[1] = false;
    
    for (int i = 2; i * i <= n; i++) {
        
        if (isPrime[i]) {
            for (int j = i + i; j < n; j += i) {
                isPrime[j] = false;
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        if (isPrime[i]) {
            prime.push_back(i);
        }
    }
    
//    debug(prime.begin(), prime.end());
}
 
bool IsPrime(int x) {
 
    if (x <= 1)
        return false;
        
    for (int p: prime) {
    
        if (p * p > x)
            break;
            
        if (x % p == 0)
            return false;
    }
    
    return true;
}

bool check(int n, int k) {
    if (n < 2 * k) return false;
    
    if (k == 1) return IsPrime(n);
    
    if (k == 2) {
        if (n % 2 == 0) {
            return true;
        }
        
        return IsPrime(n - 2);
    }
    
    return true;
}

void SolveTestCase(int testCase = 1) {
    int n, k;
    cin >> n >> k;
    cout << check(n, k) << '\n';
    
}
 
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    GeneratePrime(100022);
 
    int test = 1;
    cin >> test;
    
    for (int tc = 1; tc <= test; tc++)
        SolveTestCase(tc);
        
    return 0;
}
