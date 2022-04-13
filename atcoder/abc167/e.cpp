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

//组合数学推公式，，
//https://blog.csdn.net/mrcrack/article/details/106062762

const int N = 2e5 + 7;
ll n, m, k;
ll fn[200007]; // f[i]表示c[n][i]的组合数


void solve() {
    scanf("%lld %lld %lld", &n, &m, &k);
    ll ans = 0;
    fn[0] = 1;
    ll base = 1;
    ll cnt = 1;
    for (int i = 1; i < n ; i++) {
        base = base * (n - i);
        base %= mod;
        cnt = cnt * (i);
        cnt %= mod;
        fn[i] = base * powmod(cnt, mod - 2);
        fn[i] %= mod;

    }
    for (int i = 0; i <= k; i++) {
        ans += (m % mod * powmod(m - 1, n - i - 1)) % mod * fn[i];
        ans %= mod;
    }
    cout << ans << endl;

}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}