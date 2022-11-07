/*左边集合每个点可以和右边多个点配对，求最大配对数
左边编号1~m,右边m+1~n,-1 -1表示边结束。复杂度O(M*sqrt(N))
1<n,m<100,边数最多为C(n,2)*2 + 2*n */
const int N = 110, M = 11000, INF = 0x3f3f3f3f;
int n, m, S, T;
int h[N], e[M], ne[M], f[M], idx;
int q[N], cur[N], d[N];
void add(int a, int b, int c) {
    e[idx] = b, f[idx] = c, ne[idx] = h[a], h[a] = idx ++;
    e[idx] = a, f[idx] = 0, ne[idx] = h[b], h[b] = idx ++;
}
bool bfs() {
    int hh = 0, tt = 0;
    memset(d, - 1, sizeof d);
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
    for (int i = h[u]; i != -1 && flow < limit; i = ne[i]) {
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
    memset(h, -1, sizeof h);
    scanf("%d%d", &m, &n);
    S = 0, T = n + 1;
    //左边点集到S连边权是1的边
    for (int i = 1; i <= m; i++) add(S, i, 1);
    //右边集合的点向终点连边
    for (int i = m + 1; i <= n; i++) add(i, T, 1);
    int a, b;
    while (cin >> a >> b, a != -1) add(a, b, 1);
    printf("%d\n", dinic());
    //残余流量是0边就是匹配成功的边 一共有idx个边
    //枚举所有正向边 这些边横跨2个集合 端点在另一个集合
    for (int i = 0; i < idx; i += 2)
        if (e[i] > m && e[i] <= n && !f[i])
            printf("%d %d\n", e[i ^ 1], e[i]);
    return 0;
}
/*《圆桌问题》：m个单位每个单位ri个人n个桌子，一桌要无同单位的人。有解在第1行输出1否则输出0,以及m行每个单位所有人的桌号，有解输出任意方案即可。
左边点集为每个单位,右边为每个桌子
S向左边连权值为该单位的人数,T向右边连桌子的容纳人数
最大流等于总人数就是可行方案，否则无解*/
const int N = 430, M = (150 * 270 + N) * 2;//2倍边
const int INF = 0x3f3f3f3f;
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
int main() {
    scanf("%d%d", &m, &n);
    S = 0, T = m + n + 1; //源点和汇点
    memset(h, -1, sizeof h);
    //原点0 左边点集1~m 右边m+1~m+n 汇点m+n+1
    int tot = 0;
    for (int i = 1; i <= m; i++) {
        int c; scanf("%d", &c);
        add(S, i, c);
        tot += c; //总人数
    }
    for (int i = 1; i <= n; i++) {
        int c; scanf("%d", &c);
        add(m + i, T, c);
    }
    //每个单位的所有人向桌子连边
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            add(i, m + j, 1);
    if (dinic() != tot) puts("0");
    else {
        puts("1");
        for (int i = 1; i <= m; i++) {
            //遍历每个点对面匹配的点输出
            for (int j = h[i]; j != -1; j = ne[j])
                //满流也就是匹配的边才会输出 残留图中是0
                if (e[j] > m && e[j] <= m + n && !f[j])
                    printf("%d ", e[j] - m);
            puts("");
        }
    }
}