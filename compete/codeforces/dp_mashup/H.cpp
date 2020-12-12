#include <iostream>
#include <vector>

using namespace std;

const int N = 3003;
const int INF = (int) 1e9 + 10;

int f[N][4];

int main() {
    
    int n;
    cin >> n;
    
    vector<int> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    
    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }
    
    for (int i = 1; i < 4; i++) {
        f[n][i] = INF;
    }
    
    f[n][0] = 0;
    
    for (int i = n - 1; i >= 0; i--) {
    
        f[i][1] = f[i + 1][0] + c[i];
        f[i][2] = INF;
        f[i][3] = INF;
        
        for (int j = i + 1; j < n; j++) {
            
            if (s[j] > s[i]) {
                f[i][2] = min(f[i][2], f[j][1] + c[i]);
                f[i][3] = min(f[i][3], f[j][2] + c[i]);
            }
        }
        
//        cout << f[i][3] << endl;
//        cout << f[i][2] << endl;
//        cout << f[i][1] << endl;
//        cout << endl;
    }
    
    int ans = INF;
    
    for (int i = 0; i < n; i++) {
        ans = min(ans, f[i][3]);
    }
    
    if (ans == INF)
        ans = -1;
        
    cout << ans << endl;
    
    
}
