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

bool check(const string& s) {
    
    int n = s.size();
    
    if (n < 4)
        return false;
        
    string first_2 = s.substr(0, 2);
    string last_2 = s.substr(n - 2, 2);
    
    if (first_2 == "20" && last_2 == "20")
        return true;
        
    string first_1 = s.substr(0, 1);
    string last_3 = s.substr(n - 3, 3);
    if (first_1 == "2" && last_3 == "020")
        return true;
        
    string first_3 = s.substr(0, 3);
    string last_1 = s.substr(n - 1, 1);
    if (first_3 == "202" && last_1 == "0")
        return true;
        
    string first_4 = s.substr(0, 4);
    string last_4 = s.substr(n - 4, 4);
    
    if (first_4 == "2020" || last_4 == "2020")
        return true;
        
    return false;
    
}

void SolveTestCase(int testCase = 1) {
    int n;
    cin >> n;
    
    string s;
    cin >> s;
    
    string ans = check(s) ? "YES" : "NO";
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
