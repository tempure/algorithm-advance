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


//https://atcoder.jp/contests/abc185/editorial/448
//线性DP
//https://atcoder.jp/contests/abc185/submissions/18732226

void solve() {
    int n, m;
    cin >> n >> m;
    vi a(n), b(m);
    for (auto &x : a) cin >> x;
    for (auto &x : b) cin >> x;
    vector dp(n + 1, vector<int>(m + 1, 0x3f3f3f3f));
    dp[0][0] = 0;
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++) {
            if (i > 0) {
                dp[i][j] = min(dp[i][j], dp[i - 1][j] + 1);
            }
            if (j > 0) {
                dp[i][j] = min(dp[i][j], dp[i][j - 1] + 1);
            }
            if (i > 0 && j > 0) {
                dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + 1);
                if (a[i - 1] == b[j - 1]) {
                    dp[i][j] = min(dp[i][j], dp[i - 1][j - 1]);
                }
            }
        }
    cout << dp[n][m] << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}