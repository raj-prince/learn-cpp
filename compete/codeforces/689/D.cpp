#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

const int N = (int)1e5 + 10;

int a[N];
set<long long> st;

// select pivot and do partition according to them.
inline int doPartition(int l, int r) {
    int i = l - 1;
    int mx = a[l];
    int mn = a[l];
    for (int k = l; k <= r; k++) {
        mx = max(mx, a[k]);
        mn = min(mn, a[k]);
    }
    
    int pvt = (mx + mn) >> 1;
    
    vector<int> v;
    
    for (int j = l; j <= r; j++) {
        if (a[j] <= pvt) {
            v.push_back(a[j]);
        }
    }
    
    int idx = l + v.size() - 1;
    
    for (int j = l; j <= r; j++) {
        if (a[j] > pvt) {
            v.push_back(a[j]);
        }
    }
    for (int j = l; j <= r; j++) {
        a[j] = v[j - l];
    }
    
    return idx;
}

inline void quickSort(int l, int r) {
    if (l < r) {
        int q = doPartition(l, r);
        
        if (q == r) {
            long long sum = 0;
            for (int i = l; i <= r; i++) {
                sum += a[i];
            }
            st.insert(sum);
            return;
        }
        
        long long first_sum = 0;
        long long second_sum = 0;
        
        for (int i = l; i <= r; i++) {
            if (i <= q)
                first_sum += a[i];
            else
                second_sum += a[i];
        }
        
        st.insert(first_sum);
        st.insert(second_sum);
        
        quickSort(l, q);
        quickSort(q + 1, r);
    } else {
        st.insert(a[l]);
    }
    
//    for (int i = l; i <= r; i++) {
//        cout << a[i] << " ";
//    }
//    cout << endl;
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int test;
    cin >> test;
    
    while (test-- > 0) {
        int n, q;
        cin >> n >> q;
        
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        
        st.clear();
        quickSort(0, n - 1);
        
        while (q-- > 0) {
            int s;
            cin >> s;
            
            if (st.find(s) != st.end()) {
                cout << "Yes" << '\n';
            } else {
                cout << "No" << '\n';
            }
        }
    }
}

