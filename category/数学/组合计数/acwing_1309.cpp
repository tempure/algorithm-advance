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
const int mod = 100003;
int rnd(int x) { return mrand() % x;}
ll mulmod(ll a, ll b) {ll res = 0; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = (res + a) % mod; a = 2 * a % mod;} return res;}
ll powmod(ll a, ll b) {ll res = 1; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = res * a % mod; a = a * a % mod;} return res;}
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a;}
//snippet-head

const int N = 2010;
int fact[N], infact[N]; //预处理阶乘和逆元O(N)
//1000003是质数 可以用逆元/费马小定理计算计算组合数取模

ll qmi(int a, int k) {
    ll res = 1;
    a %= mod;
    while (k) {
        if (k & 1) res = (ll) res * a % mod;
        a = 1ll * a * a % mod;
        k >>= 1;
    }
    return res;
}

int C(int a, int b) { //c(a,b)
    if (a < b) return 0;
    return 1ll * fact[a] * infact[a - b] * infact[b] % mod;
}

int A(int a, int b) { //A(a,b)
    if (a < b) return 0;
    return 1ll * fact[a] * infact[a - b] % mod;
}

int main() {
    fact[0] = infact[0] = 1;
    for (int i = 1; i <= N; i++) {
        fact[i] = 1ll * fact[i - 1] * i % mod;
        infact[i] = 1ll *  infact[i - 1] * qmi(i, mod - 2) % mod;
    }

    int a, b , c, d, k;
    cin >> a >> b >> c >> d >> k;
    ll res = 0;

    for (int i = 0; i <= k; i++) {
        res = (res + 1ll * C(b, i) * A(a, i)  % mod * C(d, k - i) * A(a + c - i, k - i)) % mod;
    }

    cout << res << endl;

    return 0;
}