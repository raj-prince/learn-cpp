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

bool IsFeasible(int d, const vector<int>& pos, int c) {
    
    int cow = 1;
    int diff = 0;
    for (int i = 1; i < (int) pos.size(); i++) {
        
        diff += (pos[i] - pos[i - 1]);
        
        if (diff >= d) {
            cow++;
            diff = 0;
        }
    }
    
    return (cow >= c);
}

void SolveTestCase(int testCase = 1) {
    int n, c;
    cin >> n >> c;
    
    vector<int> pos(n);
    for (int &x: pos)
        cin >> x;
    
    sort(pos.begin(), pos.end());
    
    int low = 0;
    int high = pos.back() - pos.front();
        
    while (low < high) {
        
        int mid = low + (high - low + 1) / 2;
        if (IsFeasible(mid, pos, c)) {
            low = mid;
        } else {
            high = mid - 1;
        }
    }
    
    cout << low << '\n';
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
