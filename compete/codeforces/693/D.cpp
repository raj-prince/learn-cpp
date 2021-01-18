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
    
    vector<int> even, odd;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        
        if (x % 2 == 0) even.push_back(x);
        else odd.push_back(x);
    }
    
    sort(even.begin(), even.end());
    sort(odd.begin(), odd.end());
    
    stack<int> evenStack, oddStack;
    for (int x: even) {
        evenStack.push(x);
    }
    
    for (int y: odd) {
        oddStack.push(y);
    }
    
    LL aPoint = 0, bPoint = 0;
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            if (!evenStack.empty() && !oddStack.empty()) {
                int mxEven = evenStack.top();
                int mxOdd = oddStack.top();
                
                if (mxEven > mxOdd) {
                    aPoint += mxEven;
                    evenStack.pop();
                } else {
                    oddStack.pop();
                }
            } else {
                if (!evenStack.empty()) {
                    aPoint += evenStack.top();
                    evenStack.pop();
                } else {
                    oddStack.pop();
                }
            }
            
        } else {
            if (!evenStack.empty() && !oddStack.empty()) {
                int mxEven = evenStack.top();
                int mxOdd = oddStack.top();
                
                if (mxEven > mxOdd) {
                    evenStack.pop();
                } else {
                    bPoint += mxOdd;
                    oddStack.pop();
                }
            } else {
                if (!oddStack.empty()) {
                    bPoint += oddStack.top();
                    oddStack.pop();
                } else {
                    evenStack.pop();
                }
            }
            
        }
    }
    
    string ans = "Tie";
    if (aPoint > bPoint) {
        ans = "Alice";
    } else if (aPoint < bPoint) {
        ans = "Bob";
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
