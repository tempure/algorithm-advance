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

const int N = 2e5 + 10;
ll dp[2][N]; int A[2][N], n;
vi adj[N];


//dp[0][v]: v为root的子树的最大答案 且v的值选lv
//dp[1][v]: v为root的子树的最大答案 且v的值选rv
void dfs(int v, int p = -1) {
    dp[0][v] = dp[1][v] = 0;
    for (auto u : adj[v]) {
        if (u == p) continue; //不搜反向边
        dfs(u, v);
        dp[0][v] += max(abs(A[0][v] - A[1][u]) + dp[1][u], dp[0][u] + abs(A[0][v] - A[0][u]));
        dp[1][v] += max(abs(A[1][v] - A[1][u]) + dp[1][u], dp[0][u] + abs(A[1][v] - A[0][u]));
    }
}

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> A[0][i] >> A[1][i]; // lv rv
    fill(adj + 1, adj + 1 + n, vector<int>());
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    dfs(1); //注意点编号从1开始
    cout << max(dp[0][1], dp[1][1]) << endl;; //倒序DFS/DP 最大值就是1号节点的选lv还是rv取max
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t; cin >> t;
    while (t --) solve();

    return 0;
}