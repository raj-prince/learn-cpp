#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

struct Data {
    int l;
    int r;
    int strength;
    
    Data(int l, int r, int s) : l(l), r(r), strength(s) {}
};

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    
    vector<int> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    
    vector<int> l(n), r(n);
    stack<int> st;
    
    for (int i = 0; i < n; i++) {
    
        while (!st.empty() && s[st.top()] >= s[i]) {
            st.pop();
        }
        l[i] = (st.empty()) ? 0 : st.top() + 1;
        st.push(i);
    }
    
    while (!st.empty()) st.pop();
    
    for (int i = n - 1; i >= 0; i--) {
    
        while (!st.empty() && s[st.top()] >= s[i]) {
            st.pop();
        }
        r[i] = (st.empty()) ? n - 1 : st.top() - 1;
        st.push(i);
    }
    
    vector<Data> v;
    
    for (int i = 0; i < n; i++) {
        v.emplace_back(Data(l[i], r[i], s[i]));
    }
    
    sort(v.begin(), v.end(), [] (const Data& a, const Data& b) -> bool {
        return a.strength > b.strength;
    });
    
    vector<int> ans(n + 1, -1);
    
    for (auto d: v) {
        int mx_size = (d.r - d.l + 1);
        
        int sz = mx_size;
        while (sz >= 0 && ans[sz] == -1) {
            ans[sz] = d.strength;
            sz--;
        }
    }
    
    for (int i = 1; i <= n; i++) {
        if (i > 1)
            cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
}
