#include <bits/stdc++.h>
using namespace std;

/*
理解变换后的新图最大流和原图可行流完全等价的理解：

逆向思考，变换后跑完最大流，然后去掉S和T，此时图流量不守恒，然后加上下界流量此时就守恒了
正反向推导都是等价的逻辑，所以等价。

A[]数组的理解：其实完全可以开2个数组，一个记录所有点少出的流量，一个记录所有点少入的流量, 然后相减判断

但是开一个数组也可以实现，只需要将出入流量用正负区分就行了
*/

const int N = 210, M = (10200 + N) * 2, INF = 0x3f3f3f3f;

int n, m, S, T;
int h[N], e[M], ne[M], idx, f[M], l[M]; //l记录下界
int q[N], d[N], cur[N];
int A[N]; //记录每个点的入边流量和和出边流量和的差（正负)

void add(int a, int b, int c, int d) {
    e[idx] = b, f[idx] = d - c, l[idx] = c,  ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, f[idx] = 0, ne[idx] = h[b], h[b] = idx++; //反向边下界用不到
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

int dinic() {
    int r = 0, flow;
    while (bfs()) while (flow = find(S, INF)) r += flow;
    return r;
}

void solve() {
    scanf("%d%d", &n, &m);
    S = 0, T = n + 1; //随便两个范围之外的点

    memset(h, -1, sizeof h);
    for (int i = 0; i < m; i++) {
        int a, b, c, d;
        scanf("%d%d%d%d", &a, &b, &c, &d);
        add(a, b, c, d);
        A[a] -= c, A[b] += c; //同时更新该点的出入流量总和情况 用于后边处理
    }

    int tot = 0; //源点到所有点的连边的流量之和 判断满流
    for (int i = 1; i <= n; i++)
        if (A[i] > 0) add(S, i, 0, A[i]), tot += A[i]; //少流入的更多，源点补充流出
        else if (A[i] < 0) add(i, T, 0, -A[i]); //少流出的更多 多余的向汇点流去

    if (dinic() != tot) puts("NO");
    else {
        puts("YES");
        for (int i = 0; i < m * 2; i += 2)
            printf("%d\n", f[i ^ 1] + l[i]); //最后要加上减去的下界 此时的f记录的是残留图
        //原图中的流量 是此时残留图的反向边的权值
    }
}

int main() {
    solve();
    return 0;
}