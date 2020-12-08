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

//dinic最大流 二分图匹配

const int N = 110, M = 5210, INF = 0x3f3f3f3f;

int n, m, S, T;
int h[N], e[M], ne[M], f[M], idx;
int q[N], cur[N], d[N];

void add(int a, int b, int c) {
    e[idx] = b, f[idx] = c, ne[idx] = h[a], h[a] = idx ++;
    e[idx] = a, f[idx] = 0, ne[idx] = h[b], h[b] = idx ++;
}

bool bfs() {
    int hh = 0, tt = 0;
    memset(d, - 1, sizeof d);
    q[0] = S, d[S] = 0, cur[S] = h[S];

    while (hh <= tt) {
        int t = q[hh++];
        for (int i = h[t]; i != -1; i = ne[i]) {
            int ver = e[i];
            if (d[ver] == -1 && f[i]) {
                d[ver] = d[t] + 1;
                cur[ver] = h[ver];
                if (ver == T) return true;
                q[++tt] = ver;
            }
        }
    }
    return false;
}

int find(int u, int limit) {
    if (u == T) return limit;
    int flow = 0;
    for (int i = h[u]; i != -1 && flow < limit; i = ne[i]) {
        cur[u] = i;
        int ver = e[i];
        if (d[ver] == d[u] + 1 && f[i]) {
            int t = find(ver, min(f[i], limit - flow));
            if (!t) d[ver] = -1;
            f[i] -= t, f[i ^ 1] += t, flow += t;
        }
    }
    return flow;
}

int dinic() {
    int r = 0, flow;
    while (bfs()) while (flow = find(S, INF)) r += flow;

    return r;
}

int main() {
    memset(h, -1, sizeof h);
    scanf("%d%d", &m, &n);
    S = 0, T = n + 1;
    for (int i = 1; i <= m; i++) add(S, i, 1); //左边点集到S连边权是1的边
    for (int i = m + 1; i <= n; i++) add(i, T, 1); //右边向终点连边

    int a, b;
    while (cin >> a >> b, a != -1) add(a, b, 1);
    printf("%d\n", dinic());

    //残余流量是0边就是匹配成功的边 一共有idx个边
    //枚举所有正向边 这些边横跨2个集合 就是端点在另一个集合
    for (int i = 0; i < idx; i += 2)
        if (e[i] > m && e[i] <= n && !f[i])
            printf("%d %d\n", e[i ^ 1], e[i]);

    return 0;
}