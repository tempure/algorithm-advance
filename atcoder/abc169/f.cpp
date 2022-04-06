#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define um unordered_map
#define pq priority_queue
#define sz(x) ((int)(x).size())
#define fi first
#define se second
#define endl '\n'
typedef vector<int> vi;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
mt19937 mrand(random_device{}());
const ll mod = 998244353;
int rnd(int x) { return mrand() % x;}
ll mulmod(ll a, ll b) {ll res = 0; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = (res + a) % mod; a = 2 * a % mod;} return res;}
ll powmod(ll a, ll b) {ll res = 1; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = res * a % mod; a = a * a % mod;} return res;}
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a;}
//head

//较为合理的题解：https://www.cnblogs.com/zcr-blog/p/13021952.html

ll n, s;
ll a[3010];
ll f[3010];
ll inv2;


// sigma{f[i][s]} * 2^(n-i) 理解为，先必选i个数，其余n-i个数每个数都可选可不选构成的所有集合

void solve() {
    cin >> n >> s;
    for (ll i = 1; i <= n; i++) cin >> a[i];
    inv2 = powmod(2, mod - 2);
    f[0] = powmod(2, n); //why g[0] = 2^n ? 大概和为0就是不选算一种方案，然后累加 2^(n-i) ?
    for (ll i = 1; i <= n; i++) {
        for (ll k = s; k >= a[i]; k--) {
            f[k] = (f[k] + f[k - a[i]] * inv2) % mod;//除以2等于乘以2的逆元
        }
    }
    cout << f[s];
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}