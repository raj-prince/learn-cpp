#include <iostream>

using namespace std;

int main() {

    int n;
    cin >> n;
    
    long long ans = 0;
    
    if (n % 2 == 0)
        ans = 1ll << (n / 2);
        
    cout << ans << endl;
    
}
