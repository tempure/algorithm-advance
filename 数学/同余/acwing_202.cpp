#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
typedef vector<int> vi;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
mt19937 mrand(random_device{}());
const ll mod = 1000000007;
int rnd(int x) { return mrand() % x;}
ll mulmod(ll a, ll b) {ll res = 0; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = (res + a) % mod; a = 2 * a % mod;} return res;}
ll powmod(ll a, ll b) {ll res = 1; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = res * a % mod; a = a * a % mod;} return res;}
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a;}
//snippet-head

//分解质因子求欧拉函数 复杂度sqrt(n)
ll get_euler(ll c) {
    ll res = c;
    for (int i = 2; i <= c / i; i++)
        if (c % i == 0) {
            while (c % i == 0) c /= i;
            res = res / i  * (i - 1);
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


ll qmi(ll a, ll k, ll b) {
    ll res = 1;
    while (k)
    {
        if (k & 1) res = qmul(res, a, b);
        a = qmul(a, a, b);
        k >>= 1;
    }
    return res;
}

int main() {
    ll l;
    int T = 1;
    while (cin >> l, l) {
        ll d = gcd(l, 8);
        ll c = 9 * l / d;
        ll phi = get_euler(c);

        ll res = 1e18;

        if (gcd(10, c) != 1) res = 0;
        else {
            //枚举phi(c) 的约数 然后快速幂得到结果 然后判断
            for (ll d = 1; d <= phi / d; d++)
                if (phi % d == 0) {
                    if (qmi(10, d, c) == 1) res = min(res, d);
                    if (qmi(10,  phi / d, c) == 1) res = min(res, phi / d); //d是约数 那么phi / d也是约数
                }
        }

        cout << "Case " << T ++ << ": ";
        cout << res << endl;
    }
    return 0;
}