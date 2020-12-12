#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_PERSON = (int) 1e3 + 3;
const int MAX_KEY = (int) 2e3 + 3;
const int INF = (int) 2e9 + 7;

inline int AbsDiff(int a, int b) {
    return (a > b) ? a - b : b - a;
}

inline int GetTimeToReach(int person, int key, int office) {
    
    return AbsDiff(person, key) + AbsDiff(key, office);
}

inline void debug(const vector<int>& v) {
    for (int x: v)
        cout << x << " ";
        
    cout << endl;
}

int f[MAX_PERSON][MAX_KEY];

int main() {

    int n, k, p;
    cin >> n >> k >> p;
    
    vector<int> a(n), b(k);
    
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    for (int i = 0; i < k; i++) {
        cin >> b[i];
    }
    
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            f[i][j] = INF;
        }
    }
    
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    
//    debug(a);
//    debug(b);
    
    /* DP Starts */
    
    // Base Case: f[0][j] -> 0 for all j [0, k]
    for (int j = 0; j <= k; j++) {
        f[0][j] = 0;
    }
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            
//            // a new person comes, he will go with the last key
//            f[i][j] = min(f[i][j], f[i - 1][j - 1] + GetTimeToReach(a[i - 1], b[j - 1], p));
//
//            // a new key comes, only the last person can take that or can just ignore
//            f[i][j] = min(f[i][j], f[i][j - 1]);
//            f[i][j] = min(f[i][j], f[i - 1][j - 1] + GetTimeToReach(a[i - 1], b[j - 1], p));
            
            f[i][j] = min(max(f[i - 1][j - 1], GetTimeToReach(a[i - 1], b[j - 1], p)), f[i][j - 1]);
        }
    }
    
    cout << f[n][k] << endl;

    
}

