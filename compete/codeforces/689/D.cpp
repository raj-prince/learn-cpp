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

/** Code Starts */

set<long long> possible;

void traverse(const vector<int>& a, const vector<long long>& sum, int l, int r) {
    
    long long cur_sum = sum[r] - ((l > 0) ? sum[l - 1] : 0);
    possible.insert(cur_sum);
    
    if (a[l] == a[r])
        return;
        
    int pvt = (a[l] + a[r]) / 2;
    
    int low = l, high = r;
    while (low < high) {
        
        int mid = low + (high - low + 1) / 2;
        
        if (a[mid] <= pvt) {
            low = mid;
        } else {
            high = mid - 1;
        }
    }
    
//    dbg(l, r, low);
    
    traverse(a, sum, l, low);
    traverse(a, sum, low + 1, r);
}
 
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int test;
    cin >> test;
    
    while (test-- > 0) {
        int n, q;
        cin >> n >> q;
        
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(a.begin(), a.end());
        
        vector<long long> pre_sum(n);
        for (int i = 0; i < n; i++) {
            pre_sum[i] = a[i];
            
            if (i > 0) {
                pre_sum[i] += pre_sum[i - 1];
            }
        }
        
        possible.clear();
        traverse(a, pre_sum, 0, n - 1);
//        debug(possible.begin(), possible.end());
    
        while (q-- > 0) {
            int s;
            cin >> s;
            
            cout << ((possible.find(s) != possible.end()) ? "Yes" : "No") << '\n';
        }
        
    }
    
    return 0;
}
