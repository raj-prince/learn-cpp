#include <iostream>

using namespace std;

inline long long WaysToChoose(long long n, long long k) {
    
    long long ans = 1;
    for (int i = 0; i < k; i++) {
        ans *= (long long) (n - i);
        ans /= (long long) (i + 1);
    }
    
    return ans;
}

inline long long GetAnswer(long long n, long long k) {
    long long ans = 0;
    
    if (k == 0) return 1ll;
    
    /* Ways to choose 2 out of n * number of dearrangement of chosen two */
    if (k == 2) return 1 * WaysToChoose(n, 2);
    
    if (k == 3) return 2 * WaysToChoose(n, 3);
    
    if (k == 4) return 9 * WaysToChoose(n, 4);
    
    return ans;
}

int main() {

    long long n, k;
    cin >> n >> k;
    
    long long ans = 0;
    for (long long r = 0; r <= k; r++)
        ans += GetAnswer(n, r);
        
    cout << ans << endl;
}


