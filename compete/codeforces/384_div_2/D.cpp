#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int N = (int)2e5 + 10;
const long long INF = (long long) 1e17 + 10;

vector<int> g[N];
long long sum[N], ans[N], a[N], max_sum[N];
int indeg[N];

void dfs(int cur, int par) {
        
    sum[cur] = a[cur];
    ans[cur] = -INF;
    max_sum[cur] = -INF;
    
    priority_queue<long long, vector<long long>> pq;
        
    for (int x: g[cur]) {
        if (x == par) continue;
        dfs(x, cur);
        ans[cur] = max(ans[cur], ans[x]);
        sum[cur] += sum[x];
        max_sum[cur] = max(max_sum[cur], max_sum[x]);
        pq.push(max_sum[x]);
    }
    
    if (pq.size() >= 2) {
        long long top1 = pq.top(); pq.pop();
        long long top2 = pq.top();
        
        ans[cur] = max(ans[cur], top1 + top2);
    }
    
    max_sum[cur] = max(max_sum[cur], sum[cur]);
}

int main() {
    
    int n;
    cin >> n;
    
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        
        g[a].push_back(b);
        g[b].push_back(a);
        indeg[a]++;
        indeg[b]++;
    }
    
    bool impossible = true;
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            if (indeg[i] >= 2) {
                impossible = false;
                break;
            }
        } else {
            if (indeg[i] >= 3) {
                impossible = false;
                break;
            }
        }
    }
    
    if (impossible) {
        cout << "Impossible" << endl;
        return 0;
    }
        
    dfs(0, -1);
    cout << ans[0] << endl;
}
