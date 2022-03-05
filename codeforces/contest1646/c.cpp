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

//https://codeforces.com/contest/1646/submission/148308191
//https://codeforces.com/blog/entry/100584

vector<ll> f;
const ll INF = (ll)1e12 + 3;

int solve() {
    ll n;
    scanf("%lld", &n);
    int ans = __builtin_popcountll(n);
    for (int mask = 0; mask < (1 << (int)f.size()); mask++) {
        int res = 0;
        ll cur = n;
        for (int i = 0; i < (int)f.size(); i++) {
            if (((mask >> i) & 1) == 0) continue;
            res++;
            cur -= f[i];
        }
        if (cur < 0) continue;
        res += __builtin_popcountll(cur);
        ans = min(ans, res);
    }
    cout << ans << endl;
}

int main() {
    ll c = 6;
    ll nxt = 4;
    while (c < INF) {
        f.push_back(c);
        c *= nxt;
        nxt++;
    }
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}