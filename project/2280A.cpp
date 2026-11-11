
#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;

    vector<int> a(n), b(n);

    int evenA = 0, oddA = 0;
    int evenB = 0, oddB = 0;

    for (int i = 0; i < n; i++) {
        cin >> a[i];

        if (a[i] % 2 == 0) evenA++;
        else oddA++;
    }

    for (int i = 0; i < n; i++) {
        cin >> b[i];

        if (b[i] % 2 == 0) evenB++;
        else oddB++;
    }

    if (k % 2 == 0) {
        cout << (oddA >= oddB ? "YES\n" : "NO\n");
    }
    else {
        cout << (evenA >= evenB ? "YES\n" : "NO\n");
    }
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
