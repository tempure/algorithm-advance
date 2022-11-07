#include <bits/stdc++.h>
using namespace std;

const int N = 510, M = 5010 * 2, INF = 0x3f3f3f3f;
int n, m, S, T;
int h[N], e[M], ne[M];
int q[N], f[M], d[N], cur[N], idx;
bool vis_s[N], vis_t[N]; //能到S和能到T的点

/*
增加一个边的容量能让整个图的最大流变大，就是一个关键边，求所有关键边的数量

考虑增广路的思路，但是不是整个增广路径，而是一条边的两个端点到起点和终点的增广路径
如果一条边是满流，而且两个端点都同时存在到起点和终点的增广路径，那么增大这条边的容量可以构造出一个增广路径，让最大流变大
*/

void add(int a, int b, int c) {
    e[idx] = b, f[idx] = c, ne[idx] = h[a], h[a] = idx ++;
    e[idx] = a, f[idx] = 0, ne[idx] = h[b], h[b] = idx ++;
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
    while (bfs()) while (flow = find(S, INF)) r += flow;
    return r;
}

void dfs(int u, bool st[], int t) {
    st[u] = true; //标记已经走过
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = i ^ t; //i^t 作用是从S搜是正向边 从T搜是反向边
        int ver = e[i];
        if (f[j] && !st[ver]) //当前邻边没有满流并且没有被搜过
            dfs(ver, st, t);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    S = 0, T = n - 1;
    memset(h, -1, sizeof h);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c);
    }

    dinic();
    dfs(S, vis_s, 0); //不需要反向边
    dfs(T, vis_t, 1); //从汇点反向搜需要用到反向边 因为汇点开始走的边都是反向边，而关键边是正向边

    int res = 0;
    for (int i = 0; i < m * 2; i += 2)
        //一个边是满流并且起点能到S，终点能到T，就是一条关键边
        if (!f[i] && vis_s[e[i ^ 1]] && vis_t[e[i]]) //!f[i]就是满流，此时f是残留网络的流量
            res++;

    printf("%d\n", res);

    return 0;
}