#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        cout << "? 1 " << n << endl;
        int k;
        cin >> k;
        if (k == -1) return 0;
        if (k == 0 || k == n) {
            cout << "! NO" << endl;
            continue;
        }
        cout << "? 1 " << k << endl;
        int x;
        cin >> x;
        if (x == -1) return 0;
        cout << (x == k ? "! NO" : "! YES") << endl;
    }
    return 0;
}