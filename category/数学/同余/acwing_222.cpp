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

//方程:(m - n) * x - y * l = b - a
//通解 x = x0 + (- d / l)
//最小正整数解就是 模 d / l 正余数

ll exgcd(ll a, ll b, ll &x, ll & y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }

    ll d = exgcd(b, a % b, y, x);
    y -= a / b * x;

    return d;
}

int main() {
    ll a, b, m, n, l; cin >> a >> b >> m >> n >> l;
    ll x, y;
    ll d = exgcd(m - n, -l, x, y);

    if ((b - a) % d) puts("Impossible");
    else {
        x *= (b - a) / d; //exgcd 求出的是 方程右边=gcd(a,b)的x0
        ll t = abs(l / d);

        cout << (x % t + t) % t << endl;
    }

    return 0;
}