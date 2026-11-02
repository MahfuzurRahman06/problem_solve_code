#include <bits/stdc++.h>
using namespace std;
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    int n;
    cin >> n;
 
    vector<int> dp(n + 1, 1e9);
    dp[0] = 0;
 
    for (int i = 1; i <= n; i++) {
        int temp = i;
        while (temp > 0) {
            int digit = temp % 10;
            if (digit > 0) {
                dp[i] = min(dp[i], dp[i - digit] + 1);
            }
            temp /= 10;
        }
    }
 
    cout << dp[n] << "\n";
 
    return 0;
}