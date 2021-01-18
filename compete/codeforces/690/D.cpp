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

bool check(const vector<int>& a, int k, int total){

    int n = (int) a.size();
    
    if (total % (n - k) != 0)
        return false;
        
    int req = total / (n - k);
        
    int cur_sum = 0;
    for (int i = 0; i < n; i++) {
        cur_sum += a[i];
        
        if (cur_sum == req) {
            cur_sum = 0;
        } else if (cur_sum > req) {
          return false;
        }
    }
    
    return true;
}

void SolveTestCase(int testCase = 1) {
    int n;
    cin >> n;
    
    int sum = 0;
    
    vector<int> a(n);
    for (auto &x: a) {
        cin >> x;
        sum += x;
    }
        
    int ans = -1;
    for (int i = 0; i < n; i++) {
        
        if (check(a, i, sum)) {
            ans = i;
            break;
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
 
    int test = 1;
    cin >> test;
    
    for (int tc = 1; tc <= test; tc++)
        SolveTestCase(tc);
        
    return 0;
}
