/*同最大流,求新图后的s-t图残余流量减去t到s的最大流*/
const int N = 50010, M = (N + 125003) * 2;
const int INF = INT_MAX;
int n, m, S, T;
int h[N], e[M], ne[M], f[M]; //f是残留网络权值
int idx, q[N], d[N], cur[N], A[N];
void add(int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], f[idx] = c, h[a] = idx ++;
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
int find(int u, int limit) {
    if (u == T) return limit;
    int flow = 0; //从当前点往后流的流量最多是多少
    for (int i = cur[u]; i != -1 && flow < limit; i = ne[i]) {
        cur[u] = i; //当前搜的弧
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
int main() {
    int s, t; //题目给定的源点汇点 S T 为新加
    scanf("%d%d%d%d", &n, &m, &s, &t);
    memset(h, -1, sizeof h);
    S = 0, T = n + 1;
    while (m --) {
        int a, b, c, d;
        scanf("%d%d%d%d", &a, &b, &c, &d);
        add(a, b, d - c); //边权为上界减去下界
        A[a] -= c, A[b] += c;
    }
    int tot = 0;
    for (int i = 1; i <= n; i++)
        if (A[i] > 0) add(S, i, A[i]), tot += A[i];
        else if (A[i] < 0) add(i, T, -A[i]);
    add(t, s, INF); //加新边 构成无源汇图
    if (dinic() < tot) puts("No Solution"); //没有满流 无解
    else {
        int res = f[idx - 1];
        S = t, T = s;
        f[idx - 1] = f[idx - 2] = 0;
        //减去终点t到起点s最大流即可
        printf("%d\n", res - dinic());
    }
    return 0;
}