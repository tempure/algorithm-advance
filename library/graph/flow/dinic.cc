/*n个点m条边的有向图，边的容量非负。存在重边和自环。求S到T最大流。第一行包含四个整数 n,m,S,T。m行每行u,v,c，表示从点 u 到点 v 存在一条有向边，容量为 c。点的编号从 1 到 n。
输出S到T的最大流。如果S无法到达T输出0*/
//bfs处理分层图 dfs处理增广路 O(n^2*m)残留网络边开2倍
const int N = 10010, M = 2e5 + 10, INF = 0x3f3f3f3f;
int h[N], ne[M], e[M], f[M], idx;
int n, m, S, T;
int q[N], d[N], cur[N]; //d是分层图层数 cur是当前弧优化
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
//当前u 从S到u最大的可增加流量是limit
int find(int u, int limit) {
    if (u == T) return limit;
    int flow = 0; //从当前点往后流的流量最多是多少
    for (int i = cur[u]; i != -1 && flow < limit; i = ne[i]) {
        cur[u] = i; //当前搜的弧
        int ver = e[i];
        //只搜下一层的点 防止环的干扰
        if (d[ver] == d[u] + 1 && f[i]) {
            int t = find(ver, min(f[i], limit - flow));
            //当前边到终点没有增广路层数设为-1，之后不会再搜到
            if (!t) d[ver] = -1;
            //存在增广路 就更新残留网络
            f[i] -= t, f[i ^ 1] += t, flow += t;
        }
    }
    return flow;
}
int dinic() {
    int r = 0, flow;
    while (bfs())  //bfs同时建立分层图 以及返回是否有增广路
        //所有能够增广的流量累加
        while (flow = find(S, INF)) r += flow;
    return r;
}
int main() {
    scanf("%d%d%d%d", &n, &m, &S, &T);
    memset(h, -1, sizeof h);
    while (m --) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c);
    }
    printf("%d\n", dinic());
    return 0;
}