#include <bits/stdc++.h>
using namespace std;

/*2021 9.11 update
题意思就是最少去掉多少个点使一个无向图不连通

此题有个重要细节就是对于无向图的拆点技巧

注意到拆后的一个点自身的两点之间只加边一次，但是其他的点要加边2次互相
add函数里面也是正向边为边权，反向边直接边权为0，意思就是单向边

这是因为，拆点内部的边加成有向，不影响正确性，因为图是对称的，也就是你从某个角度看过去的最大流
和反方向来看的最大流是一样的，你反向跑不通，但是当枚举ST恰好反过来时候就可以跑通了，一样的。

还有一个技巧就是，拆点内部的边为1，其余原来的双向边权都是INF，可以保证最小割的边一定在拆点内部的边出现
保证了最小割一定等价于去掉点的总数。
*/

const int N = 110, M = 5210, INF = 0x3f3f3f3f;

int n, m, S, T;
int h[N], e[M], ne[M], f[M], idx;
int q[N], d[N], cur[N];

void add(int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], f[idx] = c, h[a] = idx++;
    e[idx] = a, f[idx] = 0, ne[idx] = h[b], h[b] = idx++;
}

bool bfs() {
    int hh = 0, tt = 0;
    memset(d, -1, sizeof d);
    q[0] = S, d[S] = 0, cur[S] = h[S];
    while (hh <= tt) {
        int t = q[hh++];
        for (int i = h[t]; i != -1; i = ne[i]) {
            int ver = e[i];
            if (d[ver] == -1 && f[i]) {
                d[ver] = d[t] + 1; //层数
                cur[ver] = h[ver];
                if (ver == T) return true;
                q[++tt] = ver;
            }
        }
    }
    return false;
}

int find(int u, int limit) { //当前u 从S到u最大的可增加流量是limit
    if (u == T) return limit;
    int flow = 0; //从当前点往后流的流量最多是多少
    for (int i = cur[u]; i != -1 && flow < limit; i = ne[i]) {
        cur[u] = i; //当前搜的弧
        int ver = e[i];
        if (d[ver] == d[u] + 1 && f[i]) { //只搜下一层的点 防止环的干扰
            int t = find(ver, min(f[i], limit - flow));
            if (!t) d[ver] = -1; //当前边到终点没有增广路 就层数设为-1，之后不会再搜到了
            f[i] -= t, f[i ^ 1] += t, flow += t; //存在增广路 就更新残留网络
        }
    }
    return flow;
}

int dinic() {
    int r = 0, flow;
    while (bfs())
        while (flow = find(S, INF)) r += flow;
    return r;
}

void solve() {
    while (cin >> n >> m) {
        memset(h, -1, sizeof h);
        idx = 0;
        for (int i =  0; i < n; i++) add(i, n + i, 1);
        while (m --) {
            int a, b;
            scanf(" (%d,%d)", &a, &b);
            add(n + a, b, INF);
            add(n + b, a, INF);
        }
        int res = n;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < i; j++) {
                S = n + i;
                T = j;
                for (int k = 0; k < idx; k += 2) {
                    f[k] += f[k ^ 1];
                    f[k ^ 1] = 0;
                }
                res = min(res, dinic());
            }
        cout << res << endl;
    }
}

int main() {
    solve();
    return 0;
}