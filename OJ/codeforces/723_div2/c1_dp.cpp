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
const ll mod = 1000000007;
int rnd(int x) { return mrand() % x;}
ll mulmod(ll a, ll b) {ll res = 0; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = (res + a) % mod; a = 2 * a % mod;} return res;}
ll powmod(ll a, ll b) {ll res = 1; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = res * a % mod; a = a * a % mod;} return res;}
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a;}
//head


const int N = 2010;
ll a[N];
ll dp[N][N];

void solve() {
    int n; cin >> n;
    for (int i = 1; i <= n ; i ++) cin >> a[i];

    memset(dp, 0xcf, sizeof dp);
    dp[1][0] = 0;
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++)
        for (int k = 0; k <= i; k++) {
            dp[i][k] = dp[i - 1][k];
            if (dp[i - 1][k - 1] + a[i] >= 0 && k >= 1) {
                dp[i][k] = max(dp[i - 1][k], dp[i - 1][k - 1] + a[i]);
            }
        }

    int res  = -2e9;
    for (int i = 0; i <= n; i++) {
        if (dp[n][i] >= 0) res = max(res, i);
    }
    cout << res << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // int t; cin >> t;
    int t = 1;
    while (t --) {
        solve();
    }

    return 0;
}