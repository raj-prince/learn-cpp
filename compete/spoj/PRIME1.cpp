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

bool SolveTestCase(int testCase = 1) {
    int l, r;
    cin >> l >> r;
    
    bool somethingPrinted = false;
    
    for (int i = l; i <= r; i++) {
        if (IsPrime(i)) {
            somethingPrinted = true;
            cout << i << '\n';
        }
    }
    
    return somethingPrinted;
}
 
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    GeneratePrime(40000);
 
    int test = 1;
    cin >> test;
    
    for (int tc = 1; tc <= test; tc++) {
        bool printedSomething = SolveTestCase(tc);
        
        if (tc < test && printedSomething)
            cout << '\n';
    }
        
    return 0;
}
