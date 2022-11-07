#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define fi first
#define se second
const int N = 1e6 + 1;
int n, m, q;
int a[11];
int b[21];
ll w[51], x[51], y[51], z[51];

//https://atcoder.jp/contests/abc165/submissions/12592498
//暴力


int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> q;
    for (int i = 1; i <= q ; i++) {
        cin >> w[i] >> x[i] >> y[i] >> z[i];
    }
    for (int i = 1; i <= m - 1 ; i++) {
        b[i] = 0;
    }
    for (int i = m; i <= m + n - 1 ; i++) b[i] = 1;
    ll ans = 0;
    do {
        {
            int x = 1, y = 1;
            for (int i = 1; i <= m + n - 1 ; i++) {
                if (b[i] == 0) x++;
                else {
                    a[y++] = x;
                }
            }
        }
        ll res = 0;
        for (int i = 1; i <= q ; i++) {
            if (a[x[i]] - a[w[i]] == y[i]) res += z[i];
        }
        ans = max(ans, res);
    } while (next_permutation(b + 1, b + m + n));
    cout << ans << '\n';
}