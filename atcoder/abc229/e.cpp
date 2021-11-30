#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define um unordered_map
#define pq priority_queue
#define sz(x) ((int)(x).size())
#define x first
#define y second
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


//https://atcoder.jp/contests/abc229/editorial/2985

const int N = 2e5 + 10;
int p[N];
int n, m;

int find(int x) {
    if (x != p[x]) p[x] = find(p[x]);
    return p[x];
}

void solve() {
    cin >> n >> m;
    vector<vector<ll>>v(n + 1);
    for (int i = 0; i <= n; i++) p[i] = i;

    while (m--) {
        ll a, b; cin >> a >> b;
        v[a].push_back(b);
    }

    vector<ll> res = {0};
    ll ans = 0;
    for (int i = n; i >= 2; i--) {
        ans ++;
        int pi = find(i);
        // if (sz(v[i]) == 1) {
        //     continue;
        // }
        for (auto j : v[i]) {
            int pj = find(j);
            if (pi != pj) {
                // int pi = find(i), pj = find(j);
                // if(pi)
                p[pj] = pi;
                // id[j] = id[i];
                ans --;
            }
        }
        res.pb(ans);
    }
    reverse(res.begin(), res.end());
    for (auto x : res)cout << x << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}