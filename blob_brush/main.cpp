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

void PrintVector(const vector<pair<float, float>>& v) {
    cout << "{";
    for (int i = 0; i < (int) v.size(); i++) {
        if (i > 0) {
            cout << ", ";
        }
        cout << "{" << v[i].first << ", " << v[i].second << "}";
    }
    cout << "};" << '\n';
}
 
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<pair<float, float>> p;
    while (n-- > 0) {
        string s;
        cin >> s;
        
        float xx, yy;
        cin >> xx >> yy;
        
        if (s == "PrinceSimplePoint") {
            p.push_back(make_pair(xx, yy));
        }
    }
    
    PrintVector(p);
        
    return 0;
}
