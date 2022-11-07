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

//editorial: https://atcoder.jp/contests/abc204/editorial/2033

const int N = 110, M = 1e3 + 10;
bool dp[N][M * N];

void solve() {
    int n; cin >> n;
    int sum = 0;

    dp[0][0] = 1;
    for (int i = 0; i < n; i++) {
        int y; cin >> y;
        sum += y;
        for (int j = 0; j < N * M; j++)
            if (dp[i][j]) {
                dp[i + 1][j] = 1;
                dp[i + 1][j + y] = 1;
            }
    }

    int ans = 0x3f3f3f3f;
    for (int i = 0; i <= 100000; i++)
        if (dp[n][i]) ans = min(ans, max(i, sum - i));

    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}