#include <bits/stdc++.h>
using namespace std;
 
int main() {
    int len1, len2;
    cin >> len1 >> len2;
    vector<int> a(len1), b(len2);
 
    for (int i = 0; i < len1; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < len2; i++) {
        cin >> b[i];
    }
    vector<vector<int> > lcs(len1 + 1,vector<int>(len2 + 1, 0));
 
    for (int i = 1; i <= len1; i++) {
 
        for (int j = 1; j <= len2; j++) {
 
            if (a[i - 1] == b[j - 1]) {
                lcs[i][j] = lcs[i - 1][j - 1] + 1;
            }
            else {
                lcs[i][j] = max(lcs[i - 1][j], lcs[i][j - 1]);
            }
        }
    }
 
    int i = len1;
    int j = len2;
 
    vector<int> out;
 
    while (i > 0 && j > 0) {
        if (a[i - 1] == b[j - 1]) {
            out.push_back(a[i - 1]);
            i--;
            j--;
        }
        else if (lcs[i - 1][j] >= lcs[i][j - 1]) {
            i--;
        }
        else {
            j--;
        }
    }
    reverse(out.begin(), out.end());
 
    cout << lcs[len1][len2] << endl;
 
    for (int i = 0; i < out.size(); i++) {
        cout << out[i] << ' ';
    }
    cout << endl;
    return 0;
}
