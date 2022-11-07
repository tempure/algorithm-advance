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

//https://atcoder.jp/contests/abc175/editorial/75
//算是个比较迷的线性DP....

const int N = 3010;
ll dp[N][N][4];
ll v[N][N];

void solve() {
    int r, c, k;
    cin >> r >> c >> k;
    for (int i = 0; i < k; i++) {
        int r, c, val;
        cin >> r >> c >> val;
        --r, --c;
        v[r][c] = val;
    }
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            for (int k = 0; k < 4; k++)
                dp[i][j][k] = -2e9;
    dp[0][0][0] = 0;
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++) {
            for (int k = 2; k >= 0; k--) { //这里为什么k状态要逆序更新？
                if (dp[i][j][k] >= 0)
                    dp[i][j][k + 1] = max(dp[i][j][k + 1], dp[i][j][k] + v[i][j]);
            }
            for (int k = 0; k < 4; k++)
                if (dp[i][j][k] >= 0) {
                    if (i + 1 < r) dp[i + 1][j][0] = max(dp[i + 1][j][0], dp[i][j][k]);
                    if (j + 1 < c) dp[i][j + 1][k] = max(dp[i][j + 1][k], dp[i][j][k]);
                }
        }
    ll ans = -1;
    for (int k = 0; k < 4; k++) ans = max(ans, dp[r - 1][c - 1][k]);
    cout << ans << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}