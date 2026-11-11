#include <bits/stdc++.h>
using namespace std;

int n;
vector<long long> a;

bool feasible(long long X) {
    vector<int> bad;
    vector<int> pre(n, 0);
    for (int i = 0; i + 1 < n; i++) {
        long long d = llabs(a[i] - a[i + 1]);
        if (d > X) bad.push_back(i);
        pre[i + 1] = pre[i] + (2 * d > X ? 1 : 0);
    }
    if (bad.empty())
        return true;

    if (bad.size() > 2)
        return false;

    auto check = [&](int l, int r) -> bool {
        if (l > r) return false;
        if (pre[r] - pre[l] != 0) return false;
        if (l > 0 && llabs(a[l - 1] - 2 * a[r]) > X) return false;
        if (r < n - 1 && llabs(2 * a[l] - a[r + 1]) > X) return false;
        return true;
    };

    if (bad.size() == 2) {
        return check(bad[0] + 1, bad[1]);
    }
    int e = bad[0];
    for (int r = e + 1; r < n; r++)
        if (check(e + 1, r)) return true;
    for (int l = 0; l <= e; l++)
        if (check(l, e)) return true;
    return false;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        a.assign(n, 0);
        for (auto &x : a)
            scanf("%lld", &x);

        long long lo = 0, hi = 0;
        for (int i = 0; i + 1 < n; i++)
            hi = max(hi, llabs(a[i] - a[i + 1]));

        while (lo < hi) {
            long long mid = (lo + hi) / 2;
            if (feasible(mid)) hi = mid;
            else lo = mid + 1;
        }
        printf("%lld\n", lo);
    }
    return 0;
}