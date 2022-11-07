/*n个点m条边的有向图,每条边都有流量下界上界。给定源点S和汇点T，求源点到汇点的最大流。先将源点s和汇点t连边，这样就是无源汇的图，然后添加新的S和T，边权改为减去下界，在新图上求最大流(满流)就是原图的一个可行流。接着去掉原来加的s到t的边，然后从s开始到t,Dinic求一次最大流*/
//边数:(点数+题目的边数)*2,新的S和T向所有点连边维持守恒
const int N = 210, M = (N + 10010) * 2;
const int INF = 0x3f3f3f3f;
int n, m, S, T;
int h[N], e[M], ne[M], f[M]; //f是残留网络权值
//A是入边流量和减去出边流量和 cur当前弧优化
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
            //当前边到终点无增广路层数设为-1之后不会再搜到
            if (!t) d[ver] = -1;
            //存在增广路 就更新残留网络
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
        //加上新加的边的反向边的残余流量 然后去掉
        int res = f[idx - 1];
        //直接改变源汇点 就是相当于去掉了S T还有其余的边
        S = s, T = t;
        //删去新加边,新边最后加idx就是2个正反向边
        f[idx - 1] = f[idx - 2] = 0;
        printf("%d\n", res + dinic());
    }
    return 0;
}