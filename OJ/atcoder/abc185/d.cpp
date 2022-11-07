#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(), (x).end()

void solve() {
    int n, m;
    cin >> n >> m;
    if (m == 0) {
        cout << 1 << endl;
        return;
    }
    vector<int> a;
    for (int i = 0; i < m; i++) {
        int x;
        cin >> x;
        a.push_back(x);
    }
    if (n == m) {
        cout << 0 << endl;
        return;
    }

    sort(all(a));
    int MIN = 1e9;
    if (a[0] > 1) MIN = a[0] - 1;
    for (int i = 1; i < m; i++) {
        if (a[i] - a[i - 1] == 1) continue;
        MIN = min(MIN, a[i] - a[i - 1] - 1);
    }
    // cout << MIN << endl;
    if (a[m - 1] < n) MIN = min(MIN, n - a[m - 1]);
    int res = 0;
    if (a[0] > 1) res = ((a[0] - 1) + MIN - 1) / MIN;
    for (int i = 1; i < m; i++) {
        if (a[i] - a[i - 1] == 1) continue;
        res += (a[i] - a[i - 1] - 1 + MIN - 1) / MIN;
    }
    if (a[m - 1] < n) res += (n - a[m - 1] + MIN - 1) / MIN;
    cout << res << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}