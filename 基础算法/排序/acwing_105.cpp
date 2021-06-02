#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 100010;
ll n, m, t, x, y, a[N], b[N], f[N];

ll calc (ll a[], ll n) {
    for (int i = 2; i <= n; ++i) {
        a[i] -= (a[0] / n);
        f[i] = f[i - 1] + a[i];
    }
    sort(f + 1, f + 1 + n);

    ll mid = (n + 1) >> 1, ans = 0;

    for (int i = 1; i <= n; i++) ans += abs(f[mid] - f[i]);

    return ans;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m >> t;
    for (int i = 1; i <= t; i++) {
        cin  >> x >> y;
        a[x] ++;
        b[y] ++;
    }

    for (int i = 1; i <= n; i++) a[0] += a[i];
    for (int i = 1; i <= m; i++) b[0] += b[i];

    ll as = a[0] % n, bs = b[0] % m; //看看能不能整除行列，不能就不能均分

    if (!as && !bs) cout << "both " << calc(a, n) + calc(b, m);
    else if (!as) cout << "row " << calc(a, n);
    else if (!bs) cout << "column " << calc(b, m);
    else cout << "impossible" ;

    return 0;
}