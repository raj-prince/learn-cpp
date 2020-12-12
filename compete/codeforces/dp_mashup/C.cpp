#include <iostream>

using namespace std;

const int N = 1001;
const int MAX_VITAMIN_MASK = 8;
const int INF = (int) 1e6;

int f[N][MAX_VITAMIN_MASK];

int main() {
    int n;
    cin >> n;
    
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j < MAX_VITAMIN_MASK; ++j) {
            f[i][j] = INF;
        }
    }
    
    f[0][0] = 0;
    
    for (int i = 1; i <= n; ++i) {
        int cost;
        string vitamin;
        
        cin >> cost >> vitamin;
        
        int vitamin_mask = 0;
        
        for (char c: vitamin) {
            int type = (c - 'A');
            
            vitamin_mask |= (1 << type);
        }
        
        for (int mask = 0; mask < MAX_VITAMIN_MASK; ++mask) {
            f[i][mask] = min(f[i][mask], f[i - 1][mask]);
            f[i][mask | vitamin_mask] = min(f[i - 1][mask] + cost, f[i][mask | vitamin_mask]);
        }
        
    }
    
    int ans = f[n][7];
    if (ans == INF)
        ans = -1;
        
    cout << ans << endl;
    
    
}
