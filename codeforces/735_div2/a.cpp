#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int N = 1e5 + 10;
int a[N];

void solve() {
    int n;
    cin >> n;
    // bool flag = false;
    // int max1 = -1;
    // int pos = -1;
    ll res = 0;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n - 1; i++) {
        res = max(res, 1ll * a[i] * a[i + 1]);
        if (i != 0) res = max(res, 1ll * a[i] * a[i - 1]);
    }
    cout << res << endl;
}

int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}