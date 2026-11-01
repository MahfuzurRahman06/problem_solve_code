#include <bits/stdc++.h>
using namespace std;

void solve() {
    int m;
    cin >> m;
    
    vector<vector<int>> a(2, vector<int>(m));
    long long sum1 = 0, sum2 = 0;
    
    for (int i = 0; i < m; i++) {
        cin >> a[0][i];
        sum1 += a[0][i];
    }
    for (int i = 0; i < m; i++) {
        cin >> a[1][i];
    }
    
    long long ans = 1e18;
    long long current_sum2 = 0;
    
    for (int i = 0; i < m; i++) {
        sum1 -= a[0][i];
        
        long long max_bob = max(sum1, current_sum2);
        
        ans = min(ans, max_bob);
        
        current_sum2 += a[1][i];
    }
    
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    
    return 0;
}