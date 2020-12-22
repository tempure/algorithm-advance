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
多源汇最大流:
给定一个包含 n 个点 m 条边的有向图，并给定每条边的容量，边的容量非负。
其中有 Sc 个源点，Tc 个汇点。图中可能存在重边和自环。求整个网络的最大流。
输入格式
第一行包含四个整数 n,m,Sc,Tc。
第二行包含 Sc 个整数，表示所有源点的编号。
第三行包含 Tc 个整数，表示所有汇点的编号。
接下来 m 行，每行三个整数 u,v,c，表示从点 u 到点 v 存在一条有向边，容量为 c。
点的编号从 1 到 n。
输出格式
输出一个整数表示整个网络的最大流。
数据范围
2<=n<=10000,
1<=m<=105,
0<=c<=10000,
保证源点集合和汇点集合没有交集。
输入样例：
4 5 2 2
2 4
1 3
4 2 30
4 3 20
2 3 20
2 1 30
1 3 40
输出样例：
70
*/

/*
解法:建立虚拟远点和虚拟汇点，虚拟源点向所有源点连边，容量无穷大，汇点也一样
然后在新图上Dinic求一边最大流即可，因为新图的可行流集合对应于原图的可行流集合
所以新图的最大流就是原图的最大流
*/

const int N = 10010, M = (1e5 + N) * 2, INF = 0x3f3f3f3f;

int n, m, S, T;
int h[N], e[M], f[M], ne[M], idx;
int q[N], d[N], cur[N];

void add(int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a],  f[idx] = c, h[a] = idx ++;
    e[idx] = a,  f[idx] = 0, ne[idx] = h[b], h[b] = idx ++;
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
    int sc, tc;
    scanf("%d%d%d%d", &n, &m, &sc, &tc);

    memset(h, -1, sizeof h);

    S = 0, T = n +  1; //虚拟源汇点

    while (sc--) {
        int x;
        scanf("%d", &x);
        add(S, x, INF);
    }
    while (tc--) {
        int x;
        scanf("%d", &x);
        add(x, T, INF);
    }

    while (m--) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c);
    }
    printf("%d\n", dinic());

    return 0;
}

