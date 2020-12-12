#include <iostream>

using namespace std;

const int ALPHA_COUNT = 26;

int main() {

    int n, k;
    
    cin >> n >> k;
    
    string s;
    cin >> s;
    
    bool typeable[ALPHA_COUNT];
    for (int i = 0; i < ALPHA_COUNT; i++) {
        typeable[i] = false;
    }
    
    for (int i = 0; i < k; i++) {
        char c;
        cin >> c;
        typeable[c - 'a'] = true;
    }
    
    long long ans = 0, count = 0;
    
    for (int i = 0; i < n; i++) {
        
        if (typeable[s[i] - 'a']) {
            count++;
        } else {
            ans += count * (count + 1) / 2;
            count = 0;
        }
        
    }
    
    ans += count * (count + 1) / 2;
    
    cout << ans << endl;
}
