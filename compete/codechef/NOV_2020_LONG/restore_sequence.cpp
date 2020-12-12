#include <iostream>
#include <vector>

using namespace std;

const int PRIME_LIMIT = 200;
const int N = 100020;

vector<int> calculate_prime(int n) {

    vector<int> prime;
    
    vector<bool> is_prime(n, true);
    
    is_prime[0] = is_prime[1] = false;
    
    for (int i = 2; i < n; i++) {
        
        if (is_prime[i]) {
            
            for (int j = i + i; j < n; j += i) {
                is_prime[j] = false;
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        
        if (is_prime[i])
            prime.push_back(i);
    }
    
    return prime;
}

int main() {

    
    vector<int> prime = calculate_prime(PRIME_LIMIT);
        
    int test;
    cin >> test;
    
    while (test-- > 0) {
    
        int n;
        cin >> n;
        
        vector<int> b(n), cnt(n + 1, 1);
        
        for (int i = 0; i < n; i++) {
            cin >> b[i];
        }
        
        for (int i = 0; i < n; i++) {
        
            if (i > 0)
                cout << " ";
                
            cout << cnt[b[i]] * prime[b[i]];
            
            
            cnt[b[i]]++;
        }
        
        cout << endl;
        
        
    }

    return 0;
    
}


