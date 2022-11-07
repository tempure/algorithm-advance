#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 20;
const ll mod = 1e9 + 7;

ll a[N];
int down = 1; //组合数分母不变，不要重复计算

int qmi(int a, int b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = 1ll * res * a % mod;
        a = 1ll * a * a % mod;
        b >>= 1;
    }
    return res;
}

int C(ll a, ll b) {
    if (a < b) return 0;
    int up = 1;
    for (ll i = a; i > a - b; i--) up = 1ll * i % mod * up % mod;
    return 1ll * up * down % mod;
}

int calc(ll n, ll m) {
    for (int j = 1; j <= n - 1; j++) down = 1ll * j * down % mod;
    down = qmi(down, mod - 2);
    int res = 0;
    for (int i = 0; i < 1 << n; i++) {
        ll aa = m + n - 1, b = n - 1;
        int sign = 1;
        for (int j = 0; j < n; j++)
            if (i >> j & 1) {
                sign *= -1; //(-1)^p*C(N+M-...,N-1) 这里解释看算法竞赛进阶指南，不是很好理解
                aa -= a[j] + 1;
            }
        res = (res + C(aa, b) * sign) % mod;
    }
    return (res + mod) % mod;
}

void solve() {
    ll n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> a[i];
    cout << calc(n, m) << endl;
}

int main() {
    solve();
    return 0;
}