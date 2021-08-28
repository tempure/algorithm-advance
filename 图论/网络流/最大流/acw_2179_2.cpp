#include <bits/stdc++.h>
using namespace std;

//圆桌问题 二分图多重匹配
//左边点集为每个单位的所有人 右边为每个桌子
//S向左边每个单位连接权值为单位的人数的边 T向右边连接是桌子的容纳人数
//然后每个单位向所有右边的桌子连边，边权为1
//这样建图 边初始就是网络的容量
//最大流等于总人数 就是一个可行的最大流 也就是可行方案

/*
输出方案直接判断左右点集之间的边是否残留网络流量为0即可，为0就是满流
*/

const int N = 430, M = (150 * 270 + N) * 2,  INF = 0x3f3f3f3f;

int n, m, S, T;
int h[N], ne[M], e[M], idx, f[M];
int q[N], d[N], cur[N];

void add(int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], f[idx] = c, h[a] = idx ++;
    e[idx] = a, ne[idx] = h[b], f[idx] = 0, h[b] = idx ++;
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
    cin >> m >> n;
    S = 0, T = m + n + 1;
    memset(h, -1, sizeof h);

    int tot = 0;
    for (int i = 1; i <= m; i++) {
        int c; cin >> c;
        add(S, i, c);
        tot += c;
    }
    for (int i = 1; i <= n; i++) {
        int c; cin >> c;
        add(m + i, T, c);
    }
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++) {
            add(i, m + j, 1);
        }
    if (dinic() != tot) cout << 0 << endl;
    else {
        cout << 1 << endl;
        for (int i = 1; i <= m; i++) {
            for (int j = h[i]; ~j; j = ne[j]) {
                if (e[j] > m && e[j] <= m + n && !f[j])
                    cout << e[j] - m << ' ';
            }
            cout << endl;
        }
    }
}

int main() {
    solve();
    return 0;
}