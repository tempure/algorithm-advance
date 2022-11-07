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

//https://atcoder.jp/contests/abc247/submissions/30857329
//https://www.bilibili.com/video/BV1q5411U73X?t=2768.3
//https://atcoder.jp/contests/abc247/editorial/3773

/*
官方题解说这个叫什么lucas number，，不懂，，，
看了一下dls的DP做法：
首先按照官方题解初步建图之后，就是多个连通块，每个连通块都是一个环
一共n个点n条边
然后分别计算每个连通块 乘法原理

dp[i][0/1][0/1] i表示当前已经枚举的边数，第i条边，第二维是上一条边选不选，第三维是第i条，也就是当前
考虑的最后一条边选不选，，因为不能同时这条和上条都不选，这样一个点就不会被覆盖
当前边选，那么上一条选不选无所谓，当前边不选，那么上一条必须选
*/

#define rep(i,a,n) for (int i=a;i<n;i++)

const int N = 201000;
int p[N], q[N], f[N], n, sz[N];
ll dp[N][2][2], ans[N];

int find(int x) {
    return f[x] == x ? x : f[x] = find(f[x]);
}

void solve() {
    scanf("%d", &n);
    rep(i, 1, n + 1) scanf("%d", p + i);
    rep(i, 1, n + 1) scanf("%d", q + i), f[i] = i;
    rep(i, 1, n + 1) {
        f[find(p[i])] = find(q[i]);
    }
    rep(i, 1, n + 1) sz[find(p[i])]++;
    dp[1][0][0] = 1;
    dp[1][1][1] = 1; //这个DP 初始状态我好像不太能懂，，，只有1条边，，
    ans[1] = 1;
    rep(i, 2, n + 1) {
        rep(s, 0, 2) {
            dp[i][s][0] = dp[i - 1][s][1];
            dp[i][s][1] = (dp[i - 1][s][1] + dp[i - 1][s][0]) % mod;
        }
        ans[i] = (dp[i][1][1] + dp[i][0][1] + dp[i][1][0]) % mod;
        //printf("%d %lld\n",i,ans[i]);
    }
    ll ret = 1;
    //乘法原理，对于一个固定长度的环，此时环上的数字已经无所谓了，答案是固定的
    rep(i, 1, n + 1) if (f[i] == i) ret = ret * ans[sz[i]] % mod;
    printf("%lld\n", ret);
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}