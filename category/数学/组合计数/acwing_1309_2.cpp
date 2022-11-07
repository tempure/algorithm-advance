#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2010;
const int mod = 100003;
ll fact[N], infact[N];

ll qmi(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1)res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
ll A(int a, int b) {
    if (a < b) return 0;
    return fact[a] * infact[a - b] % mod;
}

ll C(int a, int b) {
    if (a < b) return 0;
    return fact[a] * infact[a - b] * infact[b] % mod;
}

//预处理阶乘和阶乘逆元
void init() {
    fact[0] = infact[0] = 1;
    for (int i = 1; i < N; i++) {
        fact[i] = fact[i - 1] * i %  mod;
        infact[i] = infact[i - 1] * qmi(i, mod - 2) % mod;
    }
}

void solve() {
    int a, b, c, d, k;
    cin >> a >> b >> c >> d >> k;
    init();
    ll res = 0;
    for (int i = 0; i <= k; i++)
        res = (res + 1ll * C(b, i) * A(a, i)  % mod * C(d, k - i) * A(a + c - i, k - i)) % mod;
    cout << res << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}