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

class Solver {
    
public:
    int Solve(const vector<int>& v, int k) {
        Init(v, k);
        
        int low = 0, high = (int) height.size();
        
        while (low < high) {
            int mid = low + ((high - low) >> 2);
            
            if (IsOkay(mid)) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        
        if (IsOkay(low)) {
            return low + 1;
        } else {
            return -1;
        }
    }
    
private:
    void Init(const vector<int>& v, int _k) {
        height = v;
        k = _k;
        
        for (int &ht: height) {
            if (ht > k) ht = k;
        }
        
        sort(height.begin(), height.end());
        reverse(height.begin(), height.end());
    }
    
    bool IsOkay(int lastIndex) {
    
        if (lastIndex >= (int) height.size())
            return false;
            
        int totalSum = 0;
        for (int i = 0; i <= lastIndex; i++) {
            totalSum += height[i];
        }
        
        if (totalSum < (k + k)) return false;
        
        vector<bool> exists(k + k + 1, false);
        
        exists[0] = true;
        for (int i = 0; i <= lastIndex; i++) {
            for (int j = k + k; j >= height[i]; j--) {
                if (exists[j - height[i]]) {
                    exists[j] = true;
                }
            }
        }
        
        for (int j = k; j <= (k + k); j++) {
            if (exists[j]) {
                if (totalSum - j >= k) {
                    return true;
                }
            }
        }
        return false;
    }
    
    vector<int> height;
    int k;
};

void SolveTestCase(int testCase = 1) {
    int n, k;
    cin >> n >> k;
    
    vector<int> a(n);
    for (int &x: a) {
        cin >> x;
    }
    
    Solver solver;
    cout << solver.Solve(a, k) << '\n';
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
