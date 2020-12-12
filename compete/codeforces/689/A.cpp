#include <iostream>

using namespace std;

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int test;
    cin >> test;
    
    while (test-- > 0) {
        int n, k;
        cin >> n >> k;
        
        string s;
        for (int i = 0; i < n; i++) {
            char c = (i % 3) + 'a';
            s.push_back(c);
        }
        
        cout << s << '\n';
    }
    
    return 0;
    
}

