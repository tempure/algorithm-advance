#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define um unordered_map
#define pq priority_queue
#define sz(x) ((int)(x).size())
#define x first
#define y second
typedef vector<int> vi;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
mt19937 mrand(random_device{}());
// const ll mod = 1000000007;

int rnd(int x) { return mrand() % x;}
ll mulmod(ll a, ll b, ll mod) {ll res = 0; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = (res + a) % mod; a = 2 * a % mod;} return res;}
ll powmod(ll a, ll b, ll mod) {ll res = 1; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = res * a % mod; a = a * a % mod;} return res;}
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a;}
//head

//https://atcoder.jp/contests/abc228/editorial/2954

ll qmi(ll a, ll b, ll p) {
    ll res = 1; a %= p;
    while (b) {
        if (b & 1) res = mulmod(res, a, p);
        b >>= 1;
        a = mulmod(a, a, p);
    }
    return res;
}

void solve() {
    ll mod = 998244353;
    ll n, m, k;
    cin >> n >> k >> m;
    if (m % mod == 0) { //这里不特判会 wa, 因为不满足就不能用费马小定理了
        cout << 0 << '\n';
        return;
    }
    ll r = qmi(k, n, mod - 1);
    ll res = qmi(m, r, mod);
    cout << res << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}