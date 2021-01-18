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

using LL = long long;

void SolveTestCase(int testCase = 1) {
    int n;
    cin >> n;
    
    vector<LL> ans;
    LL sum = 0;
    
    vector<int> wt(n);
    for (int &x: wt) {
        cin >> x;
        sum = sum + x;
    }
    
    
    vector<int> deg(n, 0);
    
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        
        deg[x]++;
        deg[y]++;
    }
    
    vector<pair<int, int>> v;
    for (int i = 0; i < n; i++) {
        v.push_back(make_pair(wt[i], deg[i]));
    }
    
    sort(v.begin(), v.end());
    
    int k = n - 1;
    int j = n - 1;
    while (k-- > 0) {
        ans.push_back(sum);
        
        while (j >= 0 && v[j].second <= 1) {
            j--;
        }
        
        if (j < 0) break;
        
        sum += v[j].first;
        v[j].second--;
    }
    
    for (int i = 0; i < (int) ans.size(); i++) {
        if (i > 0) {
            cout << ' ';
        }
        cout << ans[i];
    }
    cout << '\n';
    
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
