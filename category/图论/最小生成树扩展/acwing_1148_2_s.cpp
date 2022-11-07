#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define um unordered_map
#define pq priority_queue
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

const int N = 510, M = 10010;
int n, m;
int dist[N][N], dist2[N][N];
int h[N], e[N * 2], w[N * 2], ne[N * 2], idx;
int p[N];
// int n, m;

struct Edge {
    int a, b, w;
    bool f; //是否为MST的边
    bool operator< (const Edge & t) {
        return w < t.w;
    }
} edge[M];

void add(int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

int find(int x) {
    if (x != p[x]) p[x] = find(p[x]);
    return p[x];
}

void dfs(int u, int fa, int max1, int max2, int d[], int d2[]) {
    d[u] = max1;
    d2[u] = max2;
    for (int i =  h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (j != fa) {
            int t1 = max1, t2 = max2;
            if (w[i] > t1) t2 = t1, t1 = w[i];
            else if (w[i] < t1 && w[i] > t2) t2 = w[i];
            dfs(j, u, t1, t2, d, d2);
        }
    }
}

void solve() {
    cin >> n >> m;
    memset(h, - 1, sizeof h);
    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        edge[i] = {a, b, w};
    }
    sort(edge, edge + m);

    //图中点编号从1开始
    for (int i = 1; i <= n; i++) p[i] = i;
    ll sum = 0;
    for (int i = 0 ; i < m; i++) {
        int a = edge[i].a, b = edge[i].b, w = edge[i].w;
        int pa = find(a), pb = find(b);
        if (pa != pb) {
            p[pa] = pb;
            sum += w;
            add(a, b, w), add(b, a, w); //只加MST的边
            edge[i].f = true;
        }
    }

    //dfs时候只会dfsMST中树上节点之间的距离，完了枚举的才是成环的边
    for (int i = 1; i <= n; i++) dfs(i, -1, 0, 0, dist[i], dist2[i]);
    ll res = 1e18;

    for (int i = 0; i < m; i++)
        if (!edge[i].f) {
            int a = edge[i].a, b = edge[i].b, w = edge[i].w;
            //加上当前成环的边，然后删掉原来MST树中路径的最大边
            //如果最大边和成环的边权一样大，那就删去次大的
            //成环的边权一定比MST中任何边都要大
            if (w > dist[a][b]) res = min(res, sum + w - dist[a][b]);
            else if (w == dist[a][b]) res = min(res, sum + w - dist2[a][b]);
        }
    cout << res << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while (t --) solve();

    return 0;
}