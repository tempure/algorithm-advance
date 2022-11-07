#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define um unordered_map
#define pq priority_queue
#define sz(x) ((int)(x).size())
#define x first
#define y second
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

const int N = 1e5 + 10, M = 2 * N;
int h[N], e[M], ne[M], idx, a[N];
int val[N];
int n, k;
int tot, cur;

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void dfs(int u, int fa) {
    val[u] = a[u];
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (j == fa) continue;
        dfs(j, u);
        val[u] ^= val[j];
    }
    if (val[u] == tot) {
        cur++;
        val[u] = 0;
    }
    // if(cur >= 3) return;
}

void solve() {
    memset(h, -1, sizeof h);
    // memset(val, 0, sizeof val);
    // memset(a, 0, sizeof a);
    tot = cur = 0;
    idx = 0;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        tot ^= a[i];
    }
    if (tot == 0) {
        puts("YES");
        return;
    }
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b);
        add(b, a);
    }
    dfs(1, 0);

    bool flag = false;
    if (cur >= 3 && k >= 3) flag = true;

    if (flag) puts("YES");
    else puts("NO");
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(0);
    int t = 1;
    // cin >> t;
    scanf("%d", &t);
    while (t --) solve();
    return 0;
}