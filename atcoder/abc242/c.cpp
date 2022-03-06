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

//https://atcoder.jp/contests/abc242/editorial/3525
//题解做法2较易理解

const int N = 1e6 + 10;
int dp[N][10];

void solve() {
    int n;
    cin >> n;
    for (int i = 1; i <= 9; i++) dp[1][i] = 1;//第一位初始化
    for (int d = 2; d <= n; d++) //从第二位开始DP
        for (int i = 1; i <= 9; i++)
            for (int j = max(1, i - 1); j <= min(9, i + 1); j++) {
                dp[d][j] += dp[d - 1][i];
                dp[d][j] %= mod;
            }
    int res = 0;
    for (int i = 1; i <= 9; i++) {
        res += dp[n][i];
        res %= mod;
    }
    cout << res << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}