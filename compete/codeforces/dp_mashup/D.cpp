#include <iostream>
#include <vector>

using namespace std;

const int N = (int) 1e5 + 3;

int missed[N];

int main() {

    int n, k;
    cin >> n >> k;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    int total_grasped = 0;
    
    for (int i = 1; i <= n; ++i) {
        int sleeping_status;
        cin >> sleeping_status;
        
        total_grasped += (a[i - 1] * sleeping_status);
        missed[i] += missed[i - 1];
        missed[i] += (a[i - 1] * (sleeping_status ^ 1));
    }
    
    int ans = total_grasped;
    
    for (int i = 1; i + k - 1 <= n; i++) {
        ans = max(ans, total_grasped + missed[i + k - 1] - missed[i - 1]);
    }
    
    cout << ans << endl;
}
