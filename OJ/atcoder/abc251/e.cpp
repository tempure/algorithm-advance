#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef vector<int> VI;
typedef basic_string<int> BI;
typedef long long ll;
typedef pair<int, int> PII;
typedef double db;
mt19937 mrand(random_device{}());
const ll mod = 1000000007;
int rnd(int x) { return mrand() % x;}
ll powmod(ll a, ll b) {ll res = 1; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = res * a % mod; a = a * a % mod;} return res;}
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a;}
// head

//https://atcoder.jp/contests/abc251/submissions/31663993
//环上DP
//当前位置不选，上个位置一定要选
//当前位置选了，上一个无所谓

const int N = 301000;
int n, a[N];
ll dp[N][2], ans = 1ll << 60;
int main() {
    scanf("%d", &n);
    rep(i, 0, n) scanf("%d", a + i);
    rep(bt, 0, 2) { //枚举第一个是否选 下标从0开始
        if (bt == 0) dp[0][0] = 0, dp[0][1] = a[0];
        else dp[0][1] = a[0], dp[0][0] = 1ll << 60; //为什么要这样初始化?
        rep(i, 1, n) {
            dp[i][1] = min(dp[i - 1][0], dp[i - 1][1]) + a[i];
            dp[i][0] = dp[i - 1][1];
        }
        if (bt == 0) ans = dp[n - 1][1];
        else ans = min(ans, min(dp[n - 1][0], dp[n - 1][1]));
    }
    printf("%lld\n", ans);
}
