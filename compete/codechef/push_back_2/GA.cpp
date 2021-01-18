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

using LL = long long;


vector<string> v;

string Convert(LL a) {
    string res = "";
    while (a > 0) {
        int dz = a % 10;
        res.push_back( (char) dz + '0');
        
        a /= 10;
    }
    
    reverse(res.begin(), res.end());
    return res;
}
void SolveTestCase(int testCase = 1) {
    int k;
    cin >> k;
    
    for (int i = 0; i < k; i++) {
        cout << v[i] << '\n';
    }
}
 
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    v.resize(51);
    
    v[0] = "0";
    v[1] = "01";
    
    LL prev1 = 0;
    LL prev2 = 1;
    for (int i = 2; i <= 50; i++) {
        LL cur = prev1 + prev2;
        
        v[i] = v[i - 1] + Convert(cur);
        
        prev1 = prev2;
        prev2 = cur;
    }
    
    int test = 1;
    cin >> test;
    
    for (int tc = 1; tc <= test; tc++)
        SolveTestCase(tc);
        
    return 0;
}
