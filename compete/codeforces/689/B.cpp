#include <iostream>
#include <cstring>

using namespace std;

const int N = 510;

int a[N][N];
int cum[N][N];
int dp[2][N][N];

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int test;
    cin >> test;
    
    while (test-- > 0) {
        int n, m;
        cin >> n >> m;
        
        memset(a, 0, sizeof(a));
        memset(cum, 0, sizeof(cum));
        memset(dp, 0, sizeof(dp));
        
        for (int i = 1; i <= n; i++) {
            
            string s;
            cin >> s;
            
            int j = 1;
            
            for (char c: s) {
                if (c == '.')
                    a[i][j++] = 0;
                else
                    a[i][j++] = 1;
            }
        }
        
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                cum[i][j] = (cum[i][j - 1] + a[i][j]);
                dp[1][i][j] = a[i][j];
                
                ans += a[i][j];
            }
        }
        
        
        for (int k = 2; k <= n; k++) {
            
            for (int i = 1; i <= n; i++) {
                
                for (int j = 1; j <= m; j++) {
                    
                    if (a[i][j] && dp[((k - 1) & 1)][i - 1][j - 1]) {
                    
                        int lastJ = j - (2 * k - 1) + 1;
                        
                        if (lastJ >= 1) {
                            int len = j - lastJ + 1;
                            int sum = cum[i][j] - cum[i][lastJ - 1];
                            
//                            if (k == 2) cout << len << " " << sum << endl;
                            if (len == sum) dp[(k & 1)][i][j] = dp[((k - 1) & 1)][i - 1][j - 1];
                            else dp[(k & 1)][i][j] = 0;
                        } else {
                            dp[(k & 1)][i][j] = 0;
                        }
                    } else {
                        dp[(k & 1)][i][j] = 0;
                    }
                    
                    ans += dp[(k & 1)][i][j];
                }
            }
        }
        
        cout << ans << '\n';
        
    }
    
}

