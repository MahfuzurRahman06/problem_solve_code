
#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int N = 500005;

int a[N];
int pref[N], suf[N], dpvl[N];

void solve() {
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
    }

    for (int i = 0; i <= n; i++) {
        pref[i] = -INF;
        suf[i] = -INF;
        dpvl[i] = -INF;
    }

    pref[0] = 0;

    for (int i = 0; i < n; i++) {

        int x = i - a[i];

        int c = suf[i];

        if (x >= 0) {
            c = max(c, dpvl[x]);
            c = max(c, pref[x]);
        }

        c++;

        // Update prefix DP
        pref[i + 1] = max(pref[i], c);

        // Propagate suffix DP
        suf[i + 1] = max(suf[i + 1], suf[i]);

        if (x >= 0) {

            // Update same painting start
            dpvl[x] = max(dpvl[x], c);

            // Update future compatible positions
            if (x + m <= n) {
                suf[x + m] = max(suf[x + m], c);
            }
        }
    }

    cout << n - max(suf[n], 0) << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
