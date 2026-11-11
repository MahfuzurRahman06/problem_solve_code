
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<long long> x(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }

    vector<vector<long long>> dp(n, vector<long long>(n, 0));

    for (int i = 0; i < n; i++) {
        dp[i][i] = x[i];
    }

    for (int len = 2; len <= n; len++) {
        for (int i = 0; i + len <= n; i++) {
            int j = i + len - 1;

            dp[i][j] = max(x[i] - dp[i + 1][j], x[j] - dp[i][j - 1]
            );
        }
    }

    long long total = 0;
    for (int i = 0; i < n; i++) {
        total += x[i];
    }

    cout << (total + dp[0][n - 1]) / 2 << '\n';

    return 0;
}
