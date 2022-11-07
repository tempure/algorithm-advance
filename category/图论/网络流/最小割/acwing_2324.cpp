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


/*
最大密度子图是对于无向图定义的
建图方式：如果是原图的边，那么边权是1，正反边都是1
虚拟源点S向所有点连边，边权为m，就是总共的原图边数，反向边权值为0
每个点向虚拟汇点连边，边权为m + 2g - d[i]，g是二分的mid, d[i]是这个点的总度数
每一次二分，也就是每一次dinic都是重新建图
二分检验(m * n - dinic(mid)) / 2 是否大于0 如果大于0说明当前二分的密度存在可以更大
*/

const int N = 110, M = (1000 + N * 2) * 2, INF = 0x3f3f3f3f;
const double eps = 1e-8;

int n, m, S, T;
int h[N], ne[M], e[M], idx;
double f[M];
int q[N], d[N], cur[N];
int dg[N]; //每个点的度数

int ans;
bool st[N]; //能不能被遍历到 答案要输出点方案

struct Edge {
    int a, b;
} edges[M];

void add(int a, int b, double c1, double c2) {
    e[idx] = b, f[idx] = c1, ne[idx] = h[a], h[a] = idx ++;
    e[idx] = a, f[idx] = c2, ne[idx] = h[b], h[b] = idx ++;
}

void build(double g) {
    memset(h, -1, sizeof h);
    idx = 0;
    for (int i = 0; i < m; i++) add(edges[i].a, edges[i].b, 1, 1);
    for (int i = 1; i <= n; i++) {
        add(S, i, m, 0);
        add(i, T, m + g * 2 - dg[i], 0);
    }
}

void dfs(int u) { //寻找可行方案 也就是一个最大密度子图的点集
    st[u] = true;
    if (u != S) ans ++; //虚拟源点不算
    for (int i = h[u]; i != -1; i = ne[i]) {
        int ver = e[i];
        if (!st[ver] && f[i] > 0)
            dfs(ver);
    }
}

double find(int u, double limit) {
    if (u == T) return limit;
    double flow = 0;
    for (int i = cur[u]; i != -1 && flow < limit; i = ne[i]) {
        cur[u] = i;
        int ver = e[i];
        if (d[ver] == d[u] + 1 && f[i] > 0) {
            double t = find(ver, min(f[i], limit - flow));
            if (t <= 0) d[ver] = -1;
            f[i] -= t, f[i ^ 1] += t, flow += t;
        }
    }
    return flow;
}

bool bfs() {
    int hh = 0, tt = 0;
    memset(d, -1, sizeof  d);
    q[0] = S, d[S] = 0, cur[S] = h[S];
    while (hh <= tt) {
        int t = q[hh++];
        for (int i = h[t]; i != -1; i = ne[i]) {
            int ver = e[i];
            if (d[ver] == -1 && f[i] > 0) {
                d[ver] = d[t] + 1;
                cur[ver] = h[ver];
                if (ver == T) return true;
                q[++tt] = ver;
            }
        }
    }
    return false;
}

double dinic(double g) {
    build(g);
    double r = 0, flow;
    while (bfs()) while (flow = find(S, INF)) r += flow;
    return r;
}

int main() {
    scanf("%d%d", &n, &m);
    S = 0, T = n + 1;
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        dg[a]++, dg[b]++; //无向边度数
        edges[i] = {a, b};
    }

    //二分 最坏情况 m 个边 一个点
    double l = 0, r = m;

    while (r - l > eps) {
        double mid = (l + r) / 2;
        double t = dinic(mid);
        if (m * n - t > 0) l = mid;
        else r = mid;
    }

    dinic(l);
    dfs(S);

    if (!ans) puts("1\n1");
    else {
        printf("%d\n", ans);
        for (int i = 1; i <= n; i++)
            if (st[i])
                printf("%d\n", i);
    }
    return 0;
}
