#include <bits/stdc++.h>
using namespace std;
 
const int MOD = 1e9 + 7;
 
int main() {
    int n, x;
    cin >> n >> x;
 
    vector<int> coin(n);
 
    for (int i = 0; i < n; i++) {
        cin >> coin[i];
    }
 
    vector<int> dp(x + 1, 0);
 
    dp[0] = 1;
 
    for (int sum = 1; sum <= x; sum++) {
        for (int c : coin) {
            if (sum >= c) {
                dp[sum] = (dp[sum] + dp[sum - c]) % MOD;
            }
        }
    }
 
    cout << dp[x] << '\n';
 
    return 0;
}