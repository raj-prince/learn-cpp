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

//#define LOCAL

#ifdef LOCAL
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

struct Visitor {
    int oldIndex;
    int sz; /* size of the group */
    int price; /* total they can spend for the food. */
    
    Visitor(int oi, int s, int p) : oldIndex(oi), sz(s), price(p) {}
};

struct Table {
    int oldIndex;
    int capacity;
    
    Table(int oi, int cap) : oldIndex(oi), capacity(cap) {}
};

/*
c[i] = size of the ith group
p[i] = price we can make after serving ith group

k = number of table
r[i] = number of seat for the ith table (where i from 0 to k - 1)

So, we need find out total maximum money we can get and any one of the arrangement

f[i][j] = max profit by considering the tables (table[i], table[i + 1]...table[k - 1])
 and list of visitors (visitor[j], visitor[j + 1]...visitor[n - 1]);

So our answer will be f[0][0];

pf[i][j] = if we transitioned from

f[i][j] -> f[i + 1][j + 1] it will be pf[i][j] = (i + 1, j + 1) else
f[i][j] -> f[i + 1][j] then pf[i][j] = (i + 1, j)
f[i][j] -> f[i][j + 1] then pf[i][j] = (i, j + 1);
*/
void SolveTestCase(int testCase = 1) {
    int n;
    cin >> n;
    
    vector<Visitor> visitor;
    for (int i = 0; i < n; i++) {
        int c, p;
        cin >> c >> p;
        
        visitor.push_back(Visitor(i + 1, c, p));
    }
    
    sort(visitor.begin(), visitor.end(), [&] (const Visitor& a, const Visitor& b) {
        return a.sz > b.sz;
    });
    
    int k;
    cin >> k;
  
    vector<Table> table;
    for (int i = 0; i < k; i++) {
        
        int cap;
        cin >> cap;
        
        table.push_back(Table(i + 1, cap));
    }
    
    sort(table.begin(), table.end(), [&] (const Table& a, const Table& b) {
        return a.capacity > b.capacity;
    });
    
    vector<vector<int>> f(k + 1, vector<int>(n + 1));
    vector<vector<pair<int, int>>> pf(k + 1, vector<pair<int, int>>(n + 1));
    for (int i = k; i >= 0; --i) {
        for (int j = n; j >= 0; --j) {
            if (i == k || j == n) {
                f[i][j] = 0;
                pf[i][j] = make_pair(-1, -1);
            } else {
                vector<pair<int, pair<int, int>>> candidate;
                candidate.push_back(make_pair(f[i][j + 1], make_pair(i, j + 1)));
                candidate.push_back(make_pair(f[i + 1][j], make_pair(i + 1, j)));
                
                if (table[i].capacity >= visitor[j].sz)
                    candidate.push_back(make_pair(f[i + 1][j + 1] + visitor[j].price, make_pair(i + 1, j + 1)));
                
                auto mx = *max_element(candidate.begin(), candidate.end());
                
                f[i][j] = mx.first;
                pf[i][j] = mx.second;
            }
        }
    }
    
    int mxProfit = f[0][0];
    vector<pair<int, int>> solution;
    
    int i = 0, j = 0;
    while (i >= 0 && j >= 0) {
            
        if (pf[i][j].first == i + 1 && pf[i][j].second == j + 1) {
            solution.push_back(make_pair(i, j));
        }
        
        int tmpi = pf[i][j].first;
        j = pf[i][j].second;
        i = tmpi;
    }
        
    cout << solution.size() << ' ' << mxProfit << '\n';
    for (auto z: solution) {
        dbg(z.first, z.second);
        cout << visitor[z.second].oldIndex << ' ' << table[z.first].oldIndex << '\n';
    }
}

 
int main() {
//#ifdef LOCAL
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
//#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int test = 1;
//    cin >> test;
    
    for (int tc = 1; tc <= test; tc++)
        SolveTestCase(tc);
        
    return 0;
}
