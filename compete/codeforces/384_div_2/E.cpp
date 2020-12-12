#include <iostream>

using namespace std;

const int N = 1010;
const int MASK = (1 << 8);

/* f[i][j] : represents for the given len, how many
 card will occur len + 1 time in the chosen subsequence. */
int f[N][MASK];
int cnt[8];
int a[N];
int mask_present = 0;

/* -1 signifies, there is no such valid subsequence. */
int solve(int len, int n) {
    
    memset(f, -1, sizeof(f));
    
    for (int i = 0; i < n; i++) {
        f[i][0] = 0;
    }
    
    for (int i = 0; i < 8; i++) {
        cnt[i] = 0;
    }
    
    for (int i = 0; i < MASK; i++) {
        f[n][i] = 0;
    }
    
    for (int i = n - 1; i >= 0; i--) {
        for (int mask = 0; mask < MASK; mask++) {
            
            for (int k = 0; k < 8; k++) {
                
                if ((mask & (1 << k)) > 0) {
                    
                    if (cnt[k] < len) break;
                    
                    int ctr = 0;
                    for (int j = i + 1; j < n; j++) {
                        
                        if (a[j] == k) ctr++;
                        
                        int new_mask = mask ^ (1 << k) ;
                        
                        if (ctr == len) {
                            if (f[j + 1][new_mask] != -1) f[i][mask] = max(f[i][mask], f[j + 1][new_mask] + 1);
                        }
                        
                        if (ctr == len + 1) {
                            if (f[j + 1][new_mask] != -1) f[i][mask] = max(f[i][mask], f[j + 1][new_mask] + 1);
                        }
                    }
                }
            }
        }
        cnt[a[i]]++;
    }
        
    return f[0][mask_present];
}

int main() {
    int n;
    cin >> n;
    
    mask_present = 0;
    
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
        mask_present |= (1 << a[i]);
    }
    
    cout << mask_present << endl;

    int lower = 0, upper = n;
    while (lower < upper) {
        int mid = lower + ((upper - lower + 1) >> 1);
        
        if (solve(mid, n) != -1) {
            lower = mid;
        } else {
            upper = mid - 1;
        }
    }
    
    cout << lower << endl;
    
    int z = solve(lower, n);
    int ans = lower * (8 - z) + z * (lower + 1);
    cout << ans << endl;
}
