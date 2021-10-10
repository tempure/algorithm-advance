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

#define int long long

const int N = 1e5 + 10;
int r[N];
double w[N];
int h[N], e[N], ne[N], idx;
bool st[N];
int q[N];
bool flag;

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

// void dfs(int u, int fa) {
//     st[u] = true;
//     for (int i = h[u]; ~i; i = ne[i]) {
//         int j = e[i];
//         if (j == fa) continue;
//         dfs(j, u);
//     }
// }

void bfs(int u) {
    // puts("*********");
    // cout<< "est" << endl;
    int hh = 0, tt = 0;
    q[0] = u;
    st[u] = true;
    while (hh <= tt) {
        auto t = q[hh++];
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (st[j]) continue;
            if (w[j]) {
                if (fabs(w[j] * r[j] + w[t] *r[t]) > 1e-4) {
                    flag = false;
                    return;
                }
                q[++tt] = j;
                st[j] = true;
            }
            else {
                w[j] = 1.0 * (-r[t]) * w[t] / r[j];
                q[++tt] = j;
                st[j] = true;
            }
        }
    }
}

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    memset(h, -1, sizeof h);
    // for (int i = 1; i <= n; i++) w[i] = -2e9;

    for (int i = 1; i <= n; i++) cin >> r[i];
    while (m --) {
        int a, b;
        cin >> a >> b;
        add(a, b);
    }
    while (k --) {
        int p;
        int v;
        cin >> p >> v;
        w[p] = v;
    }
    flag = true;
    for (int i = 1; i <= n; i++) {
        // puts("-----------------");
        if (w[i] && !st[i]) {
            // puts("---------");
            bfs(i);
        }
    }
    if (!flag) {
        cout << 0 << endl;
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (w[i] == 0) {
            cout << -1 << endl;
            return;
        }
    }
    for (int i = 1; i <= n; i++) printf("%.8lf ", w[i]);
}

signed main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}