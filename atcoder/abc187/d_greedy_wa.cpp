#include <bits/stdc++.h>
using namespace std;
#define int long long
using ll = long long;
using pii = pair<long, long>;
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()

/*
按照和降序贪心是错误的。。。
反例：
Aoki  Takahashi
7       7
12      1
2       1
1       1
贪心就得选第一组和第二组
但是正解是直接选第二组就够了
*/

void solve() {
    int n;
    cin >> n;
    vector<pii> a(n);
    ll suma = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i].fi >> a[i].se;
        suma += a[i].fi;
    }
    sort(all(a), [&](pii a, pii b) {
        return ((a.fi + a.se) < (b.fi + b.se));
    });
    reverse(all(a));
    // for (auto t : a) {
    //     cout << t.fi << ' ' << t.se << endl;
    // }
    ll temp = 0;
    for (int i = 0; i < n; i++) {
        temp += a[i].fi + a[i].se;
        suma -= a[i].fi;
        if (temp > suma) {
            cout << i + 1 << endl;
            return;
        }
    }
}

signed main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}