#include <iostream>

using namespace std;

void SolveTestCase(int testCase = 1) {
    int a, b;
    cin >> a >> b;
    
    a = a % 10;
    int ans = 1;
    
    while (b > 0) {
        if (b & 1) {
            ans = (ans * a);
            ans = ans % 10;
        }
        a = (a * a) % 10;
        
        b >>= 1;
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
