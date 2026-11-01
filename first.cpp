#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, W;

    cin >> n >> W;

    vector<int> weight(n + 1);
    vector<int> value(n + 1);

    for (int i = 1; i <= n; i++) {
        cin >> weight[i] >> value[i];
    }
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= W; j++) {

            if (weight[i] <= j) {
                dp[i][j] = max(
                    value[i] + dp[i - 1][j - weight[i]],
                    dp[i - 1][j]
                );
            }
            else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    cout << "Maximum Profit: " << dp[n][W] << endl;
    return 0;
}