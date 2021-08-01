#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> a(2, vector<int>(n));
    for (int i = 0 ; i < 2; i++)
        for (int j = 0; j < n; j++)
            cin >> a[i][j];
    int ans = 0x3f3f3f3f;
    int sum1 = 0, sum2 = 0;
    for (int i = 0; i < n; i++) sum1 += a[0][i];
    for (int i = 0; i < n; i++) { //枚举alice下转的点
        sum1 -= a[0][i];
        ans = min(ans, max(sum1, sum2));
        sum2 += a[1][i];
    }
    cout << ans << endl;
}

int main() {
    int t = 1;
    cin >> t;
    while (t -- ) solve();
    return 0;
}