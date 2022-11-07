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

//https://www.bilibili.com/video/BV1gR4y1j76r?t=3167.2
//dfs 序列，先给叶子节点标号，然后向上递推

const int N = 201000;
int n, u, v, l[N], r[N], tot;;
vi e[N];
void dfs(int u, int f) {
    bool lef = 1;
    l[u] = tot;
    r[u] = tot;
    for (auto v : e[u]) if (v != f) {
            dfs(v, u);
            lef = 0;
            r[u] = r[v];
        }
    if (lef) tot += 1;
}
int main() {
    scanf("%d", &n);
    for (int i = 0; i < n - 1; i ++) {
        scanf("%d%d", &u, &v);
        e[u].pb(v);
        e[v].pb(u);
    }
    tot = 1;
    dfs(1, 0);
    for (int i = 1; i <= n; i ++) printf("%d %d\n", l[i], r[i]);
}