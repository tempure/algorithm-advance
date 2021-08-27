#include <bits/stdc++.h>
using namespace std;

/*
当前弧优化就是在dfs找增广路的过程中，如果一个后继点已经被搜过，就不重复求此后继点到T的最大流量
*/

const int N = 10010, M = 2e5 + 10, INF = 0x3f3f3f3f;
int h[N], e[M], ne[M], f[M], idx;
int n, m, S, T;
int q[N], d[N], cur[N];

void add(int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], f[idx] = c, h[a] = idx++;
    e[idx] = a, f[idx]  = 0, ne[idx] = h[b], h[b]  = idx++;
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
    cin >> n >> m >> S >> T;
    memset(h, -1, sizeof h);
    while (m --) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
    }
    cout << dinic() << endl;
}

int main() {
    solve();
    return 0;
}