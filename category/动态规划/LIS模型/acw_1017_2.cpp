#include <bits/stdc++.h>
using namespace std;

const int N = 110;
int f[N], a[N];

void solve() {
    memset(f, 0, sizeof f);
    int n;
    cin >> n;
    int res = -1;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {
        f[i] = 1;
        for (int j = 1; j < i; j++)
            if (a[j] < a[i]) {
                f[i] = max(f[i], f[j] + 1);
                res = max(res, f[i]);
            }
    }
    reverse(a + 1, a + 1 + n);
    for (int i = 1; i <= n; i++) {
        f[i] = 1;
        for (int j = 1; j < i; j++)
            if (a[j] < a[i]) {
                f[i] = max(f[i], f[j] + 1);
                res = max(res, f[i]);
            }

    }
    cout << res << endl;
}

int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}