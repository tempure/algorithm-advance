#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
using ll = long long;
#define x first
#define y second

//2021.9.8 update

/*
所有初始给定的边权取全部都是1

二进制考虑所有点的每一位，单独计算其贡献，每一位都单独重新建图
每次建图都将所有已经标号的点，也就是题目初始给定的点，根据其当前二进制位和S，T连边

最优决策由Dinic算法保证，一个简单例子，考虑 S----a---b--c----T ，此时a点已经在集合S，c点已经在集合T
                                                        \
                                                         d
此时要将bd两点进行最优分类决策，可以选择(a,b) (b,c),({b,c},{b,d}) 等边的分类方案，显然最优的就是最小割方案
比如(a,b),(b,c)这种边的分割，而不是割掉2条边
*/

const int N = 510, M = (3000 + N * 2) * 2, INF = 0x3f3f3f3f; //every point maybe conncet source and end point
int n, m, k, S, T;
int h[N], e[M], ne[M], idx, f[M];
int q[N], d[N], cur[N];
pii edges[3010];
int p[N]; //mark of every point

void add(int a, int b, int c1, int c2) {
    e[idx] = b, ne[idx] = h[a], f[idx] = c1, h[a] = idx++;
    e[idx] = a, f[idx] = c2, ne[idx] = h[b], h[b] = idx++;
}

void build(int k) {
    memset(h, -1, sizeof h);
    idx = 0;
    for (int i =  0; i < m; i++) {
        int a = edges[i].x, b = edges[i].y;
        add(a, b, 1, 1); // biconnected edges
    }
    for (int i = 1; i <= n; i++) {
        if (p[i] >= 0) { //init all p[] is -1, so we need to judge if it's a point's has been marked
            if (p[i] >> k & 1) add(i, T, INF, 0);
            else add(S, i, INF, 0);
        }
    }
}

bool bfs() {
    int hh = 0, tt = 0;
    memset(d, -1, sizeof d);
    q[0] = S, d[S] = 0, cur[S] = h[S];
    while (hh <= tt) {
        int t = q[hh++];
        for (int i = h[t]; ~i; i = ne[i]) {
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
    for (int i = cur[u]; i != -1 && flow < limit; i = ne[i]) {
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

ll dinic(int k) {
    build(k);
    int r = 0, flow;
    while (bfs()) while (flow = find(S, INF)) r += flow;
    return r;
}

void solve() {
    cin >> n >> m;
    memset(h, -1, sizeof h);
    S = 0, T = n + 1;

    for (int i = 0 ; i < m; i++) cin >> edges[i].x >> edges[i].y;
    cin >> k;
    memset(p, -1, sizeof p); //cant'be zero, range is [0, 2^31 - 1]
    while (k --) {
        int a, b;
        cin >> a >> b;
        p[a] = b;
    }
    ll res = 0;
    for (int i =  0; i <= 30; i++) res += dinic(i) << i;
    cout << res << endl;
}

int main() {
    solve();
    return 0;
}