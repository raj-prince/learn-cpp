#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

string mul(const string& b, int x) {
    string res = "";
    
    string a = b;
    
    reverse(a.begin(), a.end());
    
    int carry = 0;
    for (char c: a) {
        int dz = c - '0';
        
        int product = (dz * x) + carry;
        int product_dz = product % 10;
        
        res.push_back((char)('0' + product_dz));
        carry = product / 10;
    }
    
    while (carry > 0) {
        int dz = carry % 10;
        
        res.push_back((char)('0' + dz));
        carry /= 10;
    }
    
    reverse(res.begin(), res.end());
    
    return res;
}

const int N = 101;
vector<string> fac;

void GenerateFact(int n) {

    fac.resize(n);
    fac[0] = "1";
    fac[1] = "1";
    
    for (int i = 2; i < n; i++) {
        fac[i] = mul(fac[i - 1], i);
    }
}

void SolveTestCase(int testCase = 1) {
    
    int n;
    cin >> n;
    
    cout << fac[n] << '\n';
}
 
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    GenerateFact(101);
 
    int test = 1;
    cin >> test;
    
    for (int tc = 1; tc <= test; tc++)
        SolveTestCase(tc);
        
    return 0;
}
