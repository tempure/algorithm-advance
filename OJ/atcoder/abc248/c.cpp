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

//https://atcoder.jp/contests/abc248/editorial/3798
//DP

void solve() {
    int n, m, K;
    cin >> n >> m >> K;
    vector f(n + 1, vector(K + 1, 0));
    f[0][0] = 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < K; j++)
            for (int k = 1; k <= m; k++) {
                if (j + k <= K) f[i + 1][j + k] = ((f[i][j] + f[i + 1][j + k] ) % mod + mod) % mod;
            }
    ll res = 0;
    for (int i = 1; i <= K; i++) {
        res  = ((res + f[n][i]) % mod + mod) % mod;
    }
    cout << res << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}