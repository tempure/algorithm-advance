#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2e5 + 10;
int tr[N], a[N];
int gr[N], lo[N];

int n;

int lowbit(int x) {
    return x & -x;
}

void add(int x, int c) {
    for (int i = x; i <= n; i += lowbit(i)) tr[i] += c;
}

int sum(int x) {
    int res = 0;
    for (int i = x; i; i -= lowbit(i)) res += tr[i];
    return res;
}

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {
        int y = a[i];
        gr[i] = sum(n) - sum(y);
        lo[i] = sum(y - 1);
        add(y, 1);
    }
    memset(tr, 0, sizeof tr);
    ll res1 = 0, res2 = 0;
    for (int i = n; i; i--) {
        int y = a[i];
        res1 += 1ll * gr[i] * (sum(n) - sum(y));
        res2 += 1ll * lo[i] * (sum(y - 1));
        add(y, 1);
    }
    cout << res1 << ' ' << res2 << '\n';
}

int main() {
    int t = 1;
    // cin >>  t;
    while (t --) solve();
    return 0;
}