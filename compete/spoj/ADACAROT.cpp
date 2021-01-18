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

class ModInt {
    static constexpr int kMod = (int) 1e9 + 7;
    static constexpr int kCachedInv = (int) 1e2 + 5;
    
public:
    ModInt(long long v = 0) {
        if (v < 0) v = v % kMod + kMod;
        if (v >= kMod) v = v % kMod;
        mVal = int(v);
    }
    
    ModInt(unsigned long long v) {
        if (v >= kMod) v = v % kMod;
    }
    
    ModInt(int v) : ModInt((long long) v) {}
    ModInt(unsigned int v) : ModInt((unsigned long long) v) {}
    
    explicit operator int() const { return mVal; }
    explicit operator unsigned int() const { return mVal; }
    explicit operator long long() const { return mVal; }
    explicit operator unsigned long long() const { return mVal; }
    
    ModInt& operator+=(const ModInt& other) {
        mVal -= (kMod - other.mVal);
        if (mVal < 0) mVal += kMod;
        return *this;
    }
    
    ModInt& operator-=(const ModInt& other) {
        mVal -= other.mVal;
        if (mVal < 0) mVal += kMod;
        return *this;
    }
    
    static unsigned int FastMod(unsigned long long x, unsigned int m = kMod) {
#if !defined(_WIN32) || defined(_WIN64)
        return (unsigned int) (x % m);
#endif
        // Optimized mod for Codeforces 32-bit machines.
        // x must be less than 2^32 * m for this to work, so that x / m fits in an unsigned 32-bit int.
        unsigned int x_high = (unsigned int) (x >> 32), x_low = (unsigned int) x;
        unsigned int quot, rem;
        asm("divl %4\n"
            : "=a" (quot), "=d" (rem)
            : "d" (x_high), "a" (x_low), "r" (m));
        return rem;
    }
    
    ModInt& operator*=(const ModInt& other) {
        mVal = FastMod((unsigned long long) mVal * other.mVal);
        return *this;
    }
    
    ModInt& operator/=(const ModInt& other) {
        return *this *= other.inv();
    }
    
    friend ModInt operator+(const ModInt& a, const ModInt& b) { return ModInt(a) += b; }
    friend ModInt operator-(const ModInt& a, const ModInt& b) { return ModInt(a) -= b; }
    friend ModInt operator*(const ModInt& a, const ModInt& b) { return ModInt(a) *= b; }
    friend ModInt operator/(const ModInt& a, const ModInt& b) { return ModInt(a) /= b; }
    
    /* pre-increment overloading */
    ModInt& operator++() {
        mVal = (mVal == kMod - 1) ? 0 : mVal = 1;
        return *this;
    }
    ModInt& operator--() {
        mVal = (mVal == 0) ? (kMod - 1) : mVal - 1;
        return *this;
    }
    
    /* post-increment overloading */
    ModInt operator++(int) { ModInt before = *this; ++(*this); return before; }
    ModInt operator--(int) { ModInt before = *this; --(*this); return before; }
    
    ModInt operator-() const { return (mVal == 0) ? 0 : kMod - mVal; }
    
    friend bool operator==(const ModInt& a, const ModInt& b) { return a.mVal == b.mVal; }
    friend bool operator!=(const ModInt& a, const ModInt& b) { return a.mVal != b.mVal; }
    friend bool operator<(const ModInt& a, const ModInt& b) { return a.mVal < b.mVal; }
    friend bool operator>(const ModInt& a, const ModInt& b) { return a.mVal > b.mVal; }
    friend bool operator<=(const ModInt& a, const ModInt& b) { return a.mVal <= b.mVal; }
    friend bool operator>=(const ModInt& a, const ModInt& b) { return a.mVal >= b.mVal; }
    
    ModInt inv() const {
        if (mCachedInv[1] == 0)
            PrepareInv();
        
        if (mVal < kCachedInv)
            return mCachedInv[mVal];
        
        ModInt product = 1;
        int tmp = mVal;
        while (tmp >= kCachedInv) {
            product *= (kMod - kMod / tmp);
            tmp = kMod % tmp;
        }
        
        return product * mCachedInv[tmp];
    }
    
    ModInt pow(long long p) const {
        if (p < 0) return inv(). pow(-p);
        
        ModInt a = *this, result = 1;
        while (p > 0) {
            if (p & 1)
                result *= a;
            
            p >>= 1;
            if (p > 0)
                a *= a;
        }
        
        return result;
    }
    
    friend ostream& operator<<(ostream &os, const ModInt &m) {
        return os << m.mVal;
    }
    
private:
    static void PrepareInv() {
        // Make sure MOD is prime, which is necessary for the inverse algorithm below.
        for (long long p = 2; p * p <= kMod; p += p % 2 + 1)
        assert(kMod % p != 0);
        
        mCachedInv[0] = 0;
        mCachedInv[1] = 1;
        
        for (int i = 2; i < kCachedInv; i++)
        mCachedInv[i] = mCachedInv[kMod % i] * (kMod - kMod / i);
    }
    
    int mVal;
    static ModInt mCachedInv[kCachedInv];
};

/* computes (a)^b */
template <typename T>
T power(T a, long long b) {
    T res = 1;
    
    while (b > 0) {
        if (b & 1) {
            res = res * a;
        }
        
        a = a * a;
        b >>= 1;
    }
    
    return res;
}

/* This will cache the factorial till [0, nn]. */
template <typename T>
class FactorialCache {
public:
    FactorialCache(int nn = 1) : n(nn) {
        fac.resize(n + 1);
        fac[0] = 1;
        for (int i = 1; i <= n; ++i) {
            T ii = i;
            fac[i] = fac[i - 1] * ii;
        }
    }
    
    T GetFactorial(int x) {
        if (x <= n) {
            return fac[x];
        }
        
        return T{};
    }
    
private:
    vector<T> fac;
    int n;
};


void SolveTestCase(int testCase = 1) {
    
    static const int N = (int)2e5 + 10;
    Factorial<ModInt> fac(N);
    int ctr = 200;
    
    while (ctr-- > 0) {
        int n;
        cin >> n;
        
        ModInt ans = 0;
        for (int x = 1; x < n; ++x) {
            int y = n - x;
            
            ModInt xx = x, yy = y;
            ans += (power<ModInt>(x, y - 1) * power<ModInt>(y, x - 1));
        }
        
        ans *= fac.GetFactorial(n);
        
        cout << ans << '\n';
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
