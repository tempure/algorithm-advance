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

//DFS序就是前序遍历
//一棵子树的DFS序在整个树的DFS序中一定是连续的一段，子树的root是该子树DFS序列首次出现

//此题读入节点默认有序 不用再给相邻点排序了

const int N = 2e5 + 10;
int n, m;
vector<int> g[N];
int q[N], p[N], top; //q[] DFS序, p[] 存下标
int sz[N];

void dfs(int u) {
    sz[u] = 1;
    q[top] = u, p[u] = top;
    top++;

    for (auto v : g[u]) {
        dfs(v);
        sz[u] += sz[v];
    }
}

void solve() {
    cin >> n >> m;
    for (int i = 2; i <= n; i++) {
        int t;
        cin >> t;
        g[t].pb(i);
    }
    dfs(1);
    while (m --) {
        int u, k;
        cin >> u >> k;
        if (k > sz[u]) puts("-1");
        else printf("%d\n", q[p[u] + k - 1]);
    }
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}