#include <bits/stdc++.h>
using namespace std;
 
int main() {
    int n, x;
    cin >> n >> x;
 
    vector<int> coin(n);
 
    for (int i = 0; i < n; i++) {
        cin >> coin[i];
    }
 
    const int INF = 1e9;
    vector<int> dp(x + 1, INF);
 
    dp[0] = 0;
 
    for (int i = 1; i <= x; i++) {
 
        for (int c : coin) {
 
            if (i >= c && dp[i - c] != INF) {
                dp[i] = min(dp[i], dp[i - c] + 1);
            }
        }
    }
 
    if (dp[x] == INF)
        cout << -1 << endl;
    else
        cout << dp[x] << endl;
 
    return 0;
}