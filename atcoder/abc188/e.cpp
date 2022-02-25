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

//https://cp-wiki.vercel.app/en/tutorial/atcoder/ABC188/#problem-e-peddler
//https://atcoder.jp/contests/abc188/editorial/555

//官方题解那个bfs我怎么没理解。。。最大和最小难道不是反了吗。。。什么考虑第二小就不用考虑最小（？）

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].emplace_back(v);
    }
    //hi[i] The highest price of gold in the towns that is reachable from town i
    //逆序递推 假设从当前枚举的点买入，来更新答案
    vector<int> hi(n + 1, -1e9); //0xcfcfcfcf 会 WA...
    int res = -1e9;
    for (int i = n; i >= 1; i--) {
        for (auto v : adj[i])
            hi[i] = max(hi[i], hi[v]);
        res = max(res, hi[i] - a[i]);
        hi[i] = max(hi[i], a[i]);
    }
    cout << res << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}