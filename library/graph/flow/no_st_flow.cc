/*n个点m条边的有向图，每条边都有流量下界和流量上界。
求方案使得在所有点满足流量平衡条件前提下所有边满足流量限制。
假设每条边流量上界是cu下界是cr,新图流量下界是0，新的上界是cu-cr，边流量减去cr转化为只有上界的可行流
定理:新图的一个最大流，对应原图的一个可行流。
建立新图时候对于每个点的流量采取多退少补策略*/
const int N = 210, M = (10200 + N) * 2, INF = 0x3f3f3f3f;
int n, m, S, T;
int h[N], e[M], ne[M], idx, f[M], l[M]; //l记录下界
int q[N], d[N], cur[N];
int A[N]; //记录每个点的入边流量和和出边流量和的差（正负)
void add(int a, int b, int c, int d) {
    e[idx] = b, f[idx] = d - c, l[idx] = c,  ne[idx] = h[a], h[a] = idx++;//反向边下界用不到
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
int main() {
    scanf("%d%d", &n, &m);
    S = 0, T = n + 1; //随便两个范围之外的点
    memset(h, -1, sizeof h);
    for (int i = 0; i < m; i++) {
        int a, b, c, d;
        scanf("%d%d%d%d", &a, &b, &c, &d);
        add(a, b, c, d);
        A[a] -= c, A[b] += c; //同时更新该点出入流量总和
    }
    int tot = 0; //源点到所有点的连边的流量之和 判断满流
    for (int i = 1; i <= n; i++)
        //少流入的更多，源点补充流出
        //少流出的更多 多余的向汇点流去
        if (A[i] > 0) add(S, i, 0, A[i]), tot += A[i];
        else if (A[i] < 0) add(i, T, 0, -A[i]);
    if (dinic() != tot) puts("NO");//判断是否满流
    else {
        puts("YES");
        for (int i = 0; i < m * 2; i += 2)
            //原图中的流量 是此时残留图的反向边的权值
            //最后要加上减去的下界 此时的f记录的是残留图
            printf("%d\n", f[i ^ 1] + l[i]);
    }
    return 0;
}