#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 998244353;

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        int M = 3 * n + 3;
        vector<char> pr(M + 1, 0);
        vector<ll> A(M + 1, 0), B(M + 1, 0), C(M + 1, 0);
        for (int i = 0; i < n; i++) {
            int x;
            scanf("%d", &x);
            pr[x] = 1;
        }
        ll T = 0, P = 0;
        for (int v = 1; v <= 3 * n; v++) {
            if (!pr[v]) continue;
            if (v - 1 >= 1 && pr[v - 1]) {
                B[v] = (1 + A[v - 1]) % MOD;
                C[v] = B[v - 1];
                P++;
            }
            if (v - 2 >= 1 && pr[v - 2]) {
                A[v] = (1 + B[v - 2] + C[v - 2]) % MOD;
                P++;
            }
            T = (T + A[v] + B[v] + C[v]) % MOD;
        }
        ll nn = n;
        ll ans = (nn % MOD + (nn * (nn - 1) / 2) % MOD + T - P % MOD + 2 * MOD) % MOD;
        printf("%lld\n", ans);
    }
    return 0;
}