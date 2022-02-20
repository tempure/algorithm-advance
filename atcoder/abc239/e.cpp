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

//https://www.cplusplus.com/reference/vector/vector/resize/
//resize 用法

//https://atcoder.jp/contests/abc239/submissions/29439095


const int N = 1e5 + 10;
int n, q, x[N];
vi e[N], num[N];

void dfs(int u, int f) {
    num[u].pb(x[u]); //root
    for (auto v : e[u]) if (v != f) {
            dfs(v, u);
            for (auto x : num[v]) num[u].pb(x);
        }
    sort(all(num[u])); reverse(all(num[u]));
    if (sz(num[u]) > 20) num[u].resize(20); //optimize
}

void solve() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> x[i];
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        e[u].pb(v);
        e[v].pb(u);
    }
    dfs(1, 0);
    while (q --) {
        int v, k;
        cin >> v >> k;
        -- k;
        cout << num[v][k] << endl;
    }
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}