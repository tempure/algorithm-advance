#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
值得注意的是无解的条件：
对于同余方程，10^x≡1(mod p) 如果10,p不互质，则方程无解，因为如果不互质
那么p有公因子2或5，如果有2，那么p是偶数，10^x mod p绝不可能是1
如果有5，那么p是5的倍数，10^x mod p 也不可能是1

此题快速幂相乘会爆掉long long，需要写快速乘取模

定理：a^x≡1(mod c) 的最小正整数解x一定能整除phi(c)
所以直接枚举phi(c) 的约数带入方程检验是否是解，然后取min即可
*/

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

ll get_euler(ll c) {
    ll res = c;
    for (int i = 2; i <= c / i; i++)
        if (c % i == 0) {
            while (c % i == 0) c /= i;
            res = res / i * (i - 1);
        }
    if (c > 1) res = res / c * (c - 1);
    return res;
}

ll qmul(ll a, ll b, ll p) {
    ll res = 0;
    while (b) {
        if (b & 1) res = (res + a) % p;
        a = (a + a) % p;
        b >>= 1;
    }
    return res;
}

ll qmi(ll a, ll b, ll p) {
    ll res = 1;
    while (b) {
        if (b & 1) res = qmul(res, a, p);
        a = qmul(a, a, p);
        b >>= 1;
    }
    return res;
}

void solve() {
    int T = 1;
    ll l;
    while (cin >> l && l) {
        ll d = gcd(l, 8);
        ll c = 9 * l / d;
        ll phi = get_euler(c);
        ll res = 1e18;
        if (gcd(10, c) != 1) res = 0;
        else {
            for (ll d = 1; d <= phi / d; d++)
                if (phi % d == 0) {
                    if (qmi(10, d, c) == 1) res = min(res, d);
                    if (qmi(10,  phi / d, c) == 1) res = min(res, phi / d); //d是约数 那么phi / d也是约数
                }
        }
        cout << "Case " << T ++ << ": ";
        cout << res << endl;
    }
}

int main() {
    solve();
    return 0;
}