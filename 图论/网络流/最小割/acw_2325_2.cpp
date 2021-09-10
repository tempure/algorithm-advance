#include <bits/stdc++.h>
using namespace std;

/*
二分图最小点权覆盖集 = 最小割
由于二分图中间的边都是INF，所以割边只会S到左列边，或者右列边到T，边权等于点权

求方案直接从S DFS 一次即可
*/



const int N = 210, M = (N + 5000 + 10) * 2, INF = 0x3f3f3f3f;

int n, m, S, T;
int h[N], e[M], ne[M], idx, f[M];
int q[N], d[N], cur[N];
bool st[N];

void add(int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], f[idx] = c, h[a] = idx++;
    e[idx] = a, ne[idx] = h[b], f[idx] = 0, h[b] = idx++;
}

bool bfs() {
    int hh  = 0, tt = 0;
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
    for (int i = cur[u]; ~i && flow < limit; i = ne[i]) {
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
    while (bfs())
        while (flow = find(S, INF)) r += flow;
    return r;
}

void dfs(int u) {
    st[u] = true;
    for (int i = h[u]; ~i; i = ne[i])
        if (f[i] && !st[e[i]])
            dfs(e[i]);
}

void solve() {
    cin >> n >> m;
    S = 0, T = 2 * n  + 1;
    memset(h, -1, sizeof h);

    for (int i = 1; i <= n; i++) {
        int w;
        cin >> w;
        add(S, i, w);
    }

    for (int i = 1; i <= n; i++) {
        int w;
        cin >> w;
        add(n + i, T, w);
    }

    while (m --) {
        int a, b;
        cin >> a >> b;
        add(b, n + a, INF);
    }

    cout << dinic() << endl;

    dfs(S);

    int cnt = 0;
    for (int i =  0; i < idx; i += 2) {
        int a = e[i ^ 1];
        int b = e[i];
        if (st[a] && !st[b])
            cnt++;
    }
    cout << cnt << endl;

    for (int i = 0; i < idx; i += 2) {
        int a = e[i ^ 1];
        int b = e[i];
        if (st[a] && !st[b]) {
            if (a == S) printf("%d +\n", b);
        }
    }

    for (int i =  0; i < idx; i += 2) {
        int a = e[i ^ 1], b = e[i];
        if (st[a] && !st[b])
            if (b == T) printf("%d -\n", a - n);
    }
}

int main() {
    solve();
    return 0;
}