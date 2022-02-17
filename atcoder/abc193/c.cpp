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
const ll mod = 1000000007;
int rnd(int x) { return mrand() % x;}
ll mulmod(ll a, ll b) {ll res = 0; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = (res + a) % mod; a = 2 * a % mod;} return res;}
ll powmod(ll a, ll b) {ll res = 1; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = res * a % mod; a = a * a % mod;} return res;}
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a;}
//head

//这么暴力。。。。。
//https://atcoder.jp/contests/abc193/editorial/820

// void divide(ll x) {
//     for (ll i = 2; i <= x / i; i ++ )
//         if (x % i == 0) {
//             ll s = 0;
//             while (x % i == 0) x /= i, s ++ ;
//             cout << i << ' ' << s << endl;
//         }
//     if (x > 1) cout << x << ' ' << 1 << endl;
//     cout << endl;
// }

void solve() {
    ll n;
    cin >> n;
    set<ll> s;
    for (ll a = 2; a * a <= n; a++) {
        ll x = a * a;
        while (x <= n) {
            s.insert(x);
            x *= a;
        }
    }
    cout << n - sz(s) << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}