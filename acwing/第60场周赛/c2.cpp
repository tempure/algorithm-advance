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

//组合数做法
//https://www.acwing.com/solution/content/126109/

int n, m, k;

ll qmi(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

//阶乘
ll f(ll x) {
    ll res = 1;
    for (ll i = 1; i <= x; i++) res = res * i % mod;
    return res % mod;
}

//素数逆元
ll inv(ll x) {
    return qmi(x, mod - 2);
}

ll getC(ll a, ll b) {
    return f(a) * inv(f(a - b) * f(b) % mod) % mod;
}

void solve() {
    cin >> n >> m >> k;
    cout << (getC(n - 1, k)*m % mod)*qmi(m - 1, k) % mod << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}