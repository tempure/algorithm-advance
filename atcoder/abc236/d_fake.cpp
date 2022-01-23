#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll a[10][10];
ll ans = -1;
int n;
bool st[10];

void dfs(ll a[10][10], int u, ll temp, int t) {
    if (u > n) {
        ans = max(ans, temp);
        temp = 0;
        // for (int i = 1; i <= n; i++) st[i] = false;
        return;
    }
    for (int i = 1; i <= t; i++) {
        if (!st[i]) {
            st[i] = true;
            // st[u] = true;
            dfs(a, u + 1, temp xor a[u][i], t - 1);
            st[i] = false;
            // st[u] = false;
        }
    }
}

void solve() {
    cin >> n;
    if (n == 1) {
        int x;
        cin >> x;
        cout << x << endl;
        return;
    }
    n++;
    int t =  n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= t; j++) {
            cin >> a[i][j];
        }
        t--;
    }

    dfs(a, 1, 0, n);
    cout << ans << endl;
}

signed main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}