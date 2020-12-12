#include <iostream>

using namespace std;

const int N = 102;
const int MAX_VELOCITY = 1002;
const int MIN_VALUE = (int) -1e9;

int f[N][MAX_VELOCITY];

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int v1, v2;
    cin >> v1 >> v2;
    
    int total_time, velocity_change;
    cin >> total_time >> velocity_change;
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < MAX_VELOCITY; j++) {
            f[i][j] = MIN_VALUE;
        }
    }
    
    f[0][v1] = 0;
    
    for (int t = 1; t <= total_time; t++) {
        
        for (int v = 0; v < MAX_VELOCITY; v++) {
            
            int ans = MIN_VALUE;
            for (int d = 0; d <= velocity_change; d++) {
                if (v - d >= 0)
                    ans = max(ans, f[t - 1][v - d] + (v - d));
                    
                if (v + d < MAX_VELOCITY)
                    ans = max(ans, f[t - 1][v + d] + (v + d));
            }
            
            f[t][v] = ans;
        }
    }
    
//    cout << f[1][5] << f[1][6] << f[1][7] << endl;
    
    cout << f[total_time - 1][v2] + v2 << '\n';
    
}
