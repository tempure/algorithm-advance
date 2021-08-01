#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 10;
int a[N];

void solve() {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    ll res = -1e12;
    if (n > 100) {
        for (int i = n - 100; i <= n; i++)
            for (int j = i + 1; j <= n; j++)
                res = max(res, 1ll * i * j - k * (a[i] | a[j]));
    }
    else {
        for (int i = 1; i <= n; i++)
            for (int j = i + 1; j <= n; j++)
                res = max(res, 1ll * i * j - k * (a[i] | a[j]));
    }
    cout << res << endl;
}

int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}