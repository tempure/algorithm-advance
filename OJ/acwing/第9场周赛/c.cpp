#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

//https://www.acwing.com/video/3324/

const int N = 500010;
int n;
int w[N];
ll l[N], r[N];
int stk[N];

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> w[i];
    int tt = 0;
    for (int i = 1; i <= n; i++) {
        while (tt && w[stk[tt]] >= w[i]) tt--;
        l[i] = l[stk[tt]] + 1ll * (i - stk[tt]) * w[i];
        stk[++tt] = i;
    }
    tt = 0;
    stk[0] = n + 1; //哨兵
    for (int i = n; i; i--) {
        while (tt && w[stk[tt]] >= w[i]) tt--;
        r[i] = r[stk[tt]] + 1ll * (stk[tt] - i) * w[i];
        stk[++tt] = i;
    }
    ll res = 0, k = 0;
    for (int i = 1; i <= n; i ++) {
        ll t = l[i] + r[i + 1];
        if (t > res) res = t, k = i;
    }
    for (int i = k - 1; i; i--)
        w[i] = min(w[i], w[i + 1]);
    for (int i = k + 2; i <= n; i++)
        w[i] = min(w[i], w[i - 1]);
    for (int i = 1; i <= n; i++) cout << w[i] << ' ';
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
}