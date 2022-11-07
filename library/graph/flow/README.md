## Temporary graph theory cheat sheet for 15th BUPT Campus Contest Final

### 最大流
- 二分图无权匹配
- 上下界可行流
- 多源汇最大流
- 最大流关键边
- 拆点最大流

### 最小割
- 最大权闭合图
- 最大密度子图
- 最小点权覆盖集
- 最大点权独立集
- 杂项建图技巧

### 费用流
- 二分图带权匹配
- 最大权不相交路径
- 网格图模型
- 上下界费用流
- 费用流拆点

### 图论杂项
- 2-SAT
- 最小树形图(Edmonds 算法)
- Prufer序列

### 二分图杂项

- 最小点覆盖，最大独立集，最小路径覆盖（最小路径重复覆盖）
- 最大匹配数 = 最小点覆盖 = 总点数 - 最大独立集 = 总点数 - 最小路径覆盖
- 最小路径重复覆盖：DAG 跑 Floyd 后再求最小路径覆盖即可

### 计算几何基础
- 凸多边形面积交 ---- 半平面交 S&I 算法/极角排序 $O(N \times logN)$
- 最小圆覆盖 ---- `random_shuffle`/三角形增量算法 $O(N)$
- 三维凸包 ---- 点增量算法 $O(N^2)$
- 平面最远点对 ---- 旋转卡壳/凸包 $O(N \times logN)$
- 最小矩形覆盖 ---- 旋转卡壳/凸包 $O(N \times logN)$
- 圆和简单多边形面积交 ---- 三角剖分 $O(N)$
- 矩形面积并 ---- 扫描线 $O(N^2 \times logN)$
- 三角形面积并 ---- 扫描线 $O(N^3 \times logN)$
- 圆的面积并 ---- 自适应辛普森积分 $O((R-L) \times \sum (H(x)))$ $H(x)$ 为求出 $F(x)$ 的复杂度
- 多面体欧拉定理：顶点数 - 棱长数 + 表面数 = 2
- 皮克定理：点阵中顶点在格点上的多边形面积公式该公式可以表示为: $S = a + b/2 - 1$
其中 $a$ 表示多边形内部的点数，$b$ 表示多边形边界上的点数，$S$ 表示多边形的面积

#### 速记（必要条件特例）
- 最小点覆盖：用最少的点覆盖所有的边，使得每条边都最少有一个端点被覆盖。考虑最普通的二分图：

```md
*
*   *
*   *
*   *
*
```
假设右列三个点有3条边连向左边，答案显示就是右列的点的最大匹配数就是3。

- 最大独立集：最大的点的集合，集合所有点之间没有边相连
依然考虑上图，那么一个最大独立集就是左列所有点，就是所有点减去最大匹配数，而最大匹配数又是右列的点数

- 最小路径覆盖：选出不重复的路径，也就是所有路径都不能有相同的点，覆盖所有DAG上的点
- 最小路径重复覆盖：可以有重复的点，也就是多个路径经过同一个点
考虑下图：

```md
    *
*   *
    *
```
左边的点向右边三个点都连接有向边，这是一个DAG。最小路径覆盖显然三条边都要选择，而此图的最大匹配数是1,
同时最小路径覆盖数3等于总点数减去最大匹配数。


#### 多源汇最大流

$n$ 个点 $m$ 条边的有向图，给定每条边的容量，边的容量非负。
 $S_c$ 个源点，$T_c$ 个汇点,图中可能存在重边和自环,求最大流。
输入格式:
第一行四个整数 $n,m,S_c,T_c$,第二行包含 $S_c$ 个整数，表示所有源点的编号。第三行包含 $T_c$ 个整数，表示所有汇点的编号。
接下来 $m$ 行，每行三个整数 $u,v,c$，表示从点 $u$ 到点 $v$ 一条有向边，容量为 $c$,点的编号从 $1$ 到 $n$。


解法:建立虚拟远点和虚拟汇点，虚拟源点向所有源点连边，容量无穷大，汇点也一样
然后在新图上 Dinic 求一遍最大流即可，因为新图的可行流集合对应于原图的可行流集合
所以新图的最大流就是原图的最大流。

```cpp
const int N = 10010, M = (1e5 + N) * 2, INF = 0x3f3f3f3f;
int n, m, S, T;
int h[N], e[M], f[M], ne[M], idx;
int q[N], d[N], cur[N];
void add(int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a],  f[idx] = c, h[a] = idx ++;
    e[idx] = a,  f[idx] = 0, ne[idx] = h[b], h[b] = idx ++;
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
    int sc, tc;
    scanf("%d%d%d%d", &n, &m, &sc, &tc);
    memset(h, -1, sizeof h);
    S = 0, T = n +  1; //虚拟源汇点
    while (sc--) {
        int x;
        scanf("%d", &x);
        add(S, x, INF);
    }
    while (tc--) {
        int x;
        scanf("%d", &x);
        add(x, T, INF);
    }
    while (m--) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c);
    }
    printf("%d\n", dinic());
    return 0;
}
```

#### 最大流关键边


增加一个边的容量能让整个图的最大流变大，就是一个关键边。
首先当前最大流的图里面，不满的边直接不用考虑，因为增大了容量依然还是流不满，被前边的容量小的边卡脖子了,所以只需要考虑满流的边即可。考虑简单路径 $s-u-v-t$ 如果 $s-u$ 和 $v-t$ 边都没有满流，只有 $u-v$ 满流，那么 $u-v$ 边就是关键边,
如果一条边是满流，而且两个端点都同时存在到起点和终点的增广路径，那么增大这条边的容量可以构造出一个增广路径，让最大流变大。

POJ3204：第一行包含 $N$ 和 $M$，表示城市和道路的数量。
接下来 $M$ 行，每行包含三个整数 $a,b,c$，表示存在一条道路从城市 $a$ 通往城市 $b$，且运输能力为 $c$。
所有道路都是有方向的。城市编号从 $0$ 到 $N - 1$。起点 $0$ 号点，终点为 $N - 1$ 号城市。

输出格式:
输出一个整数 $K$，表示存在 $K$ 条关键边。

```cpp
const int N = 510, M = 5010 * 2, INF = 0x3f3f3f3f;
int n, m, S, T;
int h[N], e[M], ne[M];
int q[N], f[M], d[N], cur[N], idx;
bool vis_s[N], vis_t[N]; //能到S和能到T的点
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
```
#### 最大流拆点
USACO 2007 Open Gold: 农夫约翰一共烹制了 $F$ 种食物，并提供了 $D$ 种饮料。
约翰共有 $N$ 头奶牛，其中第 $i$ 头奶牛有 $F_i$ 种喜欢的食物以及 $D_i$ 种喜欢的饮料。
约翰需要给每头奶牛分配一种食物和一种饮料，并使得有吃有喝的奶牛数量尽可能大。
每种食物或饮料都只有一份，所以只能分配给一头奶牛食用（即一旦将第 $2$ 种食物分配给了一头奶牛，就不能再分配给其他奶牛了）

输入格式:
第一行包含三个整数 $N,F,D$

接下来 $N$ 行，其中第 $i$ 行描述第 $i$ 头奶牛的饮食喜好，首先包含两个整数 $F_i$ 和 $D_i$，表示其喜欢的食物和饮料数量，然后包含 $F_i$ 个整数表示其喜欢的食物的种类编号，最后包含 $D_i$ 个整数表示其喜欢的饮料的种类编号。食物编号从 $1$ 到 $F$，饮料编号从 $1$ 到 $D$

输出格式:输出一个整数，表示能够有吃有喝的奶牛的最大数量。

最大流拆点求三分图匹配：将食物，牛，饮料都分别看成一竖排，再加上源点 $S$ 和汇点 $T$
源点 $S$ 向所有食物连边，所有饮料向 $T$ 连边，每个牛匹配的食物向牛连边,每个牛向其匹配的饮料向后连边。

考虑如果每个牛可以多进多出边，那么就不能满足题目的 “给每头奶牛分配一种食物和一种饮料” 条件，所以必须把牛的点拆开
拆点后注意编号问题，以及数组的点数计算问题。

```cpp
const int N = 410, M = 41000, INF = 0x3f3f3f3f;
int n, F, D, S, T;
int h[N], e[M], ne[M], f[M], idx;
int q[N], d[N], cur[N];
//建图点的顺序：所有牛的入点1~n，所有牛的出点n + 1 ~ 2n, 食物2n + 1~ 2n + F, 饮料2n + F + 1 ~ 2n + F  + 1 + D
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
    while (bfs())  //bfs同时建立分层图 以及返回是否有增广路
        while (flow = find(S, INF)) r += flow; //所有能够增广的流量累加
    return r;
}
int main() {
    scanf("%d%d%d", &n, &F, &D);
    S = 0, T = n * 2 + F + D + 1;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= F; i++) add(S, n * 2 + i, 1); //源点向所有食物连边
    for (int i = 1; i <= D; i++) add(2 * n + F + i, T, 1); //饮料向汇点连边
    for (int i = 1; i <= n; i++) {
        add(i, n + i, 1); //牛的拆点后的入点到出点连边权为1的边
        int a, b, t;
        scanf("%d%d", &a, &b);
        while (a --) {
            scanf("%d", &t);
            add(n * 2 + t, i, 1); //牛匹配的食物向牛的入点连边
        }
        while (b --) {
            scanf("%d", &t);
            add(i + n, n * 2 + F + t, 1); //牛的出点向牛匹配的饮料连边
        }
    }
    printf("%d\n", dinic());
    return 0;
}
```

#### 最小割之最大权闭合图

NOI2006最大获利：$N$ 个通讯信站,第 $i$ 个用户群为 $A_i,B_i$ 和 $C_i$：使用中转站 $A_i$ 和中转站 $B_i$ 进行通讯，获益 $C_i$

输入格式：
第一行有两个正整数 $N$ 和 $M$。

第二行中有 $N$ 个整数描述每一个通讯中转站的建立成本，依次为 $P_1,P_2,…,P_N$ 。

以下 $M$ 行，第 $i+2$ 行的三个数 $A_i,B_i$ 和 $C_i$ 描述第 $i$ 个用户群的信息。输出一个整数，表示公司可以得到的最大净获利

建立虚拟源点 $S$ 和汇点 $T$，如果点权为正就向源点 $S$ 连边，边权为点权，如果点权为负就向汇点连边，但是边权依然为正数值大小等于点权
除了源汇点之外的所有点之间边权都是 INF
此图的最大权闭合图权值和 = 所有权值为正的点权值和 - 最小割(最大流)

所有中转站的点权都是 $-pi$, 意思是建站需要花费 $pi$，然后每个用户群向其需要的 $2$ 个中转站连边，用户群的点权为 $+ci$
代表收益 $ci$，用户群和中转站之间的边权为 INF, 可以发现此时就是一个闭合图，然后要求最大权闭合图，就求出了最大收益

```cpp
const int N = (50000 + 5000 + 10), M = (50000 * 3 + 5000 + 10) * 2;
const int INF = 0x3f3f3f3f;
int n, m, S, T;
int h[N], ne[M], e[M], idx;
int q[N], f[M], d[N], cur[N];
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
    while (bfs())  //bfs同时建立分层图 以及返回是否有增广路
        while (flow = find(S, INF)) r += flow; //所有能够增广的流量累加

    return r;
}
/*
在代码中并不需要体现点权值的正负，只需要建立正权的边即可
*/
int main() {
    scanf("%d%d", &n, &m);
    S = 0, T = n + m + 1; //一共有n + m个点
    //用户是1到m  中转站是m + 1到m + n
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; i++) {
        int p;
        scanf("%d", &p);
        //花费，向汇点连边
        add(m + i, T, p);
    }
    int tot = 0; // 正数点的权值和
    for (int i = 1; i <= m; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(S, i, c); //S向用户连边 权值为收益
        add(i, m + a, INF); //用户向中转站连边 权值INF
        add(i, m + b, INF);
        tot += c;
    }
    printf("%d\n", tot - dinic());
    return 0;
}
```

#### 最小割之最大密度子图

POJ3155生活的艰辛：输入第一行包含两个整数 $n$ 和 $m$。
接下来 $m$ 行，每行包含两个整数 $a_i$ 和 $b_i$，$a_i$ 和 $b_i$ 之间有无向边,点编号从 $1$ 到 $n$。

输出格式：首先输出一个整数 $k$，表示子图的点数。
接下来 $k$ 行，升序输出每个点的编号，每行一个。
如果答案不唯一，则输出任意一种即可。注意：至少要选择一个点。

子图的密度定义为子图的总边数/总点数，是对于无向图定义的。
建图方式：如果是原图的边，那么边权是 $1$，正反边都是 $1$，
虚拟源点 $S$ 向所有点连边，边权为 $m$，就是总共的原图边数，反向边权值为 $0$，
每个点向虚拟汇点连边，边权为 $m + 2g - d[i]$，$g$ 是二分的 $mid$, $d[i]$ 是这个点的总度数。
每一次二分，也就是每一次 Dinic 都是重新建图。
二分检验 $(m * n - dinic(mid)) / 2$ 是否大于 $0$ 如果大于 $0$ 说明当前二分的密度存在而且可以更大。

```cpp
const int N = 110, M = (1000 + N * 2) * 2, INF = 0x3f3f3f3f;
const double eps = 1e-8;
int n, m, S, T;
int h[N], ne[M], e[M], idx;
double f[M];
int q[N], d[N], cur[N];
int dg[N]; //每个点的度数
int ans;
bool st[N]; //能不能被遍历到 答案要输出点方案
struct Edge {
    int a, b;
} edges[M];
void add(int a, int b, double c1, double c2) {
    e[idx] = b, f[idx] = c1, ne[idx] = h[a], h[a] = idx ++;
    e[idx] = a, f[idx] = c2, ne[idx] = h[b], h[b] = idx ++;
}
void build(double g) {
    memset(h, -1, sizeof h);
    idx = 0;
    for (int i = 0; i < m; i++) add(edges[i].a, edges[i].b, 1, 1);
    for (int i = 1; i <= n; i++) {
        add(S, i, m, 0);
        add(i, T, m + g * 2 - dg[i], 0);
    }
}
void dfs(int u) { //寻找可行方案 也就是一个最大密度子图的点集
    st[u] = true;
    if (u != S) ans ++; //虚拟源点不算
    for (int i = h[u]; i != -1; i = ne[i]) {
        int ver = e[i];
        if (!st[ver] && f[i] > 0)
            dfs(ver);
    }
}
double find(int u, double limit) {
    if (u == T) return limit;
    double flow = 0;
    for (int i = cur[u]; i != -1 && flow < limit; i = ne[i]) {
        cur[u] = i;
        int ver = e[i];
        if (d[ver] == d[u] + 1 && f[i] > 0) {
            double t = find(ver, min(f[i], limit - flow));
            if (t <= 0) d[ver] = -1;
            f[i] -= t, f[i ^ 1] += t, flow += t;
        }
    }
    return flow;
}
bool bfs() {
    int hh = 0, tt = 0;
    memset(d, -1, sizeof  d);
    q[0] = S, d[S] = 0, cur[S] = h[S];
    while (hh <= tt) {
        int t = q[hh++];
        for (int i = h[t]; i != -1; i = ne[i]) {
            int ver = e[i];
            if (d[ver] == -1 && f[i] > 0) {
                d[ver] = d[t] + 1;
                cur[ver] = h[ver];
                if (ver == T) return true;
                q[++tt] = ver;
            }
        }
    }
    return false;
}
double dinic(double g) {
    build(g);
    double r = 0, flow;
    while (bfs()) while (flow = find(S, INF)) r += flow;
    return r;
}
int main() {
    scanf("%d%d", &n, &m);
    S = 0, T = n + 1;
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        dg[a]++, dg[b]++; //无向边度数
        edges[i] = {a, b};
    }
    //二分 最坏情况 m 个边 一个点
    double l = 0, r = m;
    while (r - l > eps) {
        double mid = (l + r) / 2;
        double t = dinic(mid);
        if (m * n - t > 0) l = mid;
        else r = mid;
    }
    dinic(l);
    dfs(S);
    if (!ans) puts("1\n1");
    else {
        printf("%d\n", ans);
        for (int i = 1; i <= n; i++)
            if (st[i])
                printf("%d\n", i);
    }
    return 0;
}
```

#### 最小割之二分图最小点权覆盖集

POJ2125有向图破坏：$N$ 个点 $M$ 条边的有向图。
在每一步操作中可以选取一个点，并将所有射入该点的边移除或者将所有从该点射出的边移除。
已知，对于第 $i$ 个点，将所有射入该点的边移除所需的花费为 $W_i^+$，将所有从该点射出的边移除所需的花费为 $W_i^-$。
需要将图中的所有边移除，计算最少花费。

覆盖集：一个点集，可以覆盖所有的边，覆盖是指一个边至少有一个端点在这个点集中。
左边集合的所有点与虚拟源点 $S$ 连边，边权为点权，右边集合的所有点和汇点 $T$ 连边，边权为点权,
中间所有点保持自己原来的连边，边权 INF，这样的目的是最小割一定不会包含中间的边。
假设一条有向边是 $a \rightarrow b$ 那么可以花费代价 $a^-$ 删去这条边，也可以花费代价 $b^+$ 删去这条。
所以所有 $+$ 号的点是一个点集，$-$ 号是一个点集，然后 $b+$ 向 $a-$ 连边，边权 INF，这样就是二分图的最小点权覆盖问题。

二分图最小点权覆盖集 = 最小割,
由于二分图中间的边都是INF，所以割边只会 $S$ 到左列边，或者右列边到 $T$，边权等于点权,
求方案直接从源点 $S$ DFS 一次即可。

```cpp
const int N = 210, M = (N + 5010) * 2 + 10, INF = 0x3f3f3f3f;
int n, m, S, T;
int h[N], e[M], f[M], ne[M], idx;
int q[N], d[N], cur[N];
bool st[N];
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
    while (bfs())  //bfs同时建立分层图 以及返回是否有增广路
        while (flow = find(S, INF)) r += flow; //所有能够增广的流量累加

    return r;
}
void dfs(int u) {
    st[u] = true;
    for (int i = h[u]; i != -1; i = ne[i])
        if (f[i] && !st[e[i]])
            dfs(e[i]);
}
int main() {
    scanf("%d%d", &n, &m);
    //左边+号点是1-n, 右边-号点是n+1到2n
    S = 0, T = n * 2 + 1;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; i++) { //+号点
        int w;
        scanf("%d", &w);
        add(S, i, w);
    }
    for (int i = 1; i <= n; i++) { //-号点
        int w;
        scanf("%d", &w);
        add(n + i, T, w);
    }

    while (m --) {
        int a, b;
        scanf("%d%d", &a, &b);
        add(b, n + a, INF); //从左边b+向右边a-连边
    }
    printf("%d\n", dinic());
    //方案
    dfs(S);
    //统计操作数量
    int count = 0;
    for (int i = 0; i < idx; i += 2) {
        int a = e[i ^ 1]; //起点 就是反向边的终点
        int b = e[i]; //终点

        if (st[a] && !st[b]) //只能搜到一个端点，那就是一条割边
            count++;
    }
    printf("%d\n", count);
    //所有+号操作
    for (int i = 0; i < idx; i += 2) {
        int a = e[i ^ 1], b = e[i];
        if (st[a] && !st[b]) {
            if (a == S) printf("%d +\n", b); //该边的起点是S同时是割边，那么就是加号操作
        }
    }
    //-号操作
    for (int i = 0; i < idx; i += 2) {
        int a = e[i ^ 1], b = e[i];
        if (st[a] && !st[b]) {
            if (b == T) printf("%d -\n", a - n); //该边的终点是S同时是割边，那么就是减号操作
        }
    }
    return 0;
}
```

#### 最小割之最大点权独立集
二分图最大权独立集 = 所有点权 - 最小点权覆盖集,
一个定理：一个有向图中，独立集的补集肯定是覆盖集。类比普通二分图无点权求最大独立集，这里只是加上了点权求最大点权独立集。

#### 骑士共存问题（最大权独立集）
$n \times n$ 国际象棋棋盘,棋盘上某些方格设置了障碍，骑士不得进入。
对于给定的 $n \times n$ 棋盘和障碍标志，计算最多可以放置多少个骑士，使得它们彼此互不攻击。

输入格式:第一行有 $2$ 个正整数 $n$ 和 $m$，分别表示棋盘的大小和障碍数。
接下来的 $m$ 行给出障碍的位置。每行 $2$ 个正整数，表示障碍的方格坐标。

输出格式:输出可以共存的最大骑士数量。

对于一个点能攻击到的点，和该点的横坐标差值为 $1$，纵坐标差值为 $2$,
所以横纵坐标之和的奇偶性肯定不同，奇数点为一个集合，偶数点为一个集合，就是二分图的模型。
题目求的就是互不攻击的骑士个数，也就是最大独立集。

虚拟源点 $S$ 向奇数点连边，边权为 $1$，偶数点向汇点 $T$ 连边，边权为 $1$，中间每个点向其周围的 $8$ 个点连边，边权 INF
连边的时候特判一下不能放的位置即可,答案就是总点权和减去最大流。

```cpp
const int N = 40010, M = 400010, INF = 0x3f3f3f3f;
int n, m, S, T;
int h[N], e[M], f[M], ne[M], idx;
int q[N],  d[N], cur[N];
bool g[210][210]; //标记合法位置
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
    while (bfs())  //bfs同时建立分层图 以及返回是否有增广路
        while (flow = find(S, INF)) r += flow; //所有能够增广的流量累加
    return r;
}
int get(int x, int y) { //根据位置返回点的idx
    return (x - 1) * n + y;
}
int main() {
    scanf("%d%d", &n, &m);
    S = 0, T = n * n + 1;
    memset(h, -1, sizeof h);
    while (m --) { //标记不合法的位置
        int x, y;
        scanf("%d%d", &x, &y);
        g[x][y] = true;
    }
    int dx[] = { -2, -1, 1, 2, 2, 1, -1, -2};
    int dy[] = {1, 2, 2, 1, -1, -2, -2, -1};
    int tot = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j ++) {
            if (g[i][j]) continue;
            if (i + j & 1) {
                add(S, get(i, j), 1);
                for (int k = 0; k < 8; k++) {
                    int x = i + dx[k], y = j + dy[k];
                    if (x >= 1 && x <= n && y >= 1 && y <= n && !g[x][y])
                        add(get(i, j), get(x, y), INF);
                }
            }
            else add(get(i, j), T, 1);
            tot ++;
        }
    printf("%d\n", tot - dinic());
    return 0;
}
```

#### 费用流模板
最小费用最大流：给定一个包含 $n$ 个点 $m$ 条边的有向图，并给定每条边的容量和费用，边的容量非负。
图中可能存在重边和自环，保证费用不会存在负环。
求从 $S$ 到 $T$ 的最大流，以及在流量最大时的最小费用。

输入格式:第一行包含四个整数 $n,m,S,T$。
接下来 $m$ 行，每行三个整数 $u,v,c,w$，表示从点 $u$ 到点 $v$ 存在一条有向边，容量为 $c$，费用为 $w$。
点的编号从 $1$ 到 $n$。

输出点 $S$ 到点 $T$ 的最大流和流量最大时的最小费用。
如果从点 $S$ 无法到达点 $T$ 则输出 $0 \ 0$

```cpp
const int N = 5010, M = 100010, INF = 0x3f3f3f3f;
int n, m, S, T;
int h[N], e[M], f[M], w[M], ne[M], idx; //w[]是每条边的费用
int q[N], d[N], pre[N], incf[N]; //此处的d是最短路的距离 incf是从起点到当前点的路径中，最小的剩余流量大小
bool st[N];
void add(int a, int b, int c, int d) {
    e[idx] = b, f[idx] = c, w[idx] = d, ne[idx] = h[a], h[a] = idx ++;
    e[idx] = a, f[idx] = 0, w[idx] = -d, ne[idx] = h[b], h[b] = idx ++;
}
bool spfa() {
    int hh = 0, tt = 1;
    memset(d, 0x3f, sizeof d);
    memset(incf, 0, sizeof incf);
    q[0] = S, d[S] = 0, incf[S] = INF;
    while (hh != tt) {
        int t = q[hh++];
        if (hh == N) hh = 0;
        st[t] = false;

        for (int i = h[t]; i != -1; i = ne[i]) {
            int ver = e[i];
            if (f[i] && d[ver] > d[t] + w[i]) {
                d[ver] = d[t] + w[i];
                pre[ver] = i;
                incf[ver] = min(f[i], incf[t]);
                if (!st[ver]) {
                    q[tt++] = ver;
                    if (tt == N) tt = 0;
                    st[ver] = true;
                }
            }
        }
    }
    return incf[T] > 0; //如果大于0说明S可以走到T 不然就不连通
}
void EK(int & flow, int & cost) {
    flow = cost = 0;
    while (spfa()) {
        int t = incf[T]; //当前找到的新的增广路的流量
        flow += t, cost += t * d[T]; //此题没有单位费用，直接费用就是路径长度*流量
        for (int i = T; i != S; i = e[pre[i] ^ 1]) {
            f[pre[i]] -= t;
            f[pre[i] ^ 1] += t;
        }
    }
}
int main() {
    scanf("%d%d%d%d", &n, &m, &S, &T);
    memset(h, -1, sizeof h);
    while (m --) {
        int a, b, c, d; //边的起点 终点 容量 费用
        scanf("%d%d%d%d", &a, &b, &c, &d);
        add(a, b, c, d);
    }
    int flow, cost; //最大流以及最小费用
    EK(flow, cost);
    printf("%d %d\n", flow, cost);
    return 0;
}
```

#### 费用流之二分图带权匹配

分配问题：有 $n$ 件工作要分配给 $n$ 个人做。
第 $i$ 个人做第 $j$ 件工作产生的效益为 $c_{ij}$。
试设计一个将 $n$ 件工作分配给 $n$ 个人做的分配方案。

输入格式：第 $1$ 行有 $1$ 个正整数 $n$，表示有 $n$ 件工作要分配给 $n$ 个人做。
接下来 $n$ 行中，每行有 $n$ 个整数 $c_{ij}$，表示第 $i$ 个人做第 $j$ 件工作产生的效益为 $c_{ij}$。

输出格式：第一行输出最差分配方案下的最小总效益,第二行输出最优分配方案下的最大总效益。

$S$ 向所有人连边，容量为 $1$，费用 $0$,所有工作向 $T$ 连边，容量 $1$，费用 $0$。每个人向所有工作连边，容量 $1$，费用为收益 $c$,求最大费用把边权取反跑最短路即可。

```cpp
const int N = 110, M = 5210, INF = 0x3f3f3f3f;
int n, S, T;
int h[N], e[M], f[M], w[M], ne[M], idx;
int q[N], d[N], pre[N], incf[N];
bool st[N];
void add(int a, int b, int c, int d) {
    e[idx] = b, f[idx] = c, w[idx] = d, ne[idx] = h[a], h[a] = idx ++;
    e[idx] = a, f[idx] = 0, w[idx] = -d, ne[idx] = h[b], h[b] = idx ++;
}
bool spfa() {
    int hh = 0, tt = 1;
    memset(d, 0x3f, sizeof d);
    memset(incf, 0, sizeof incf);
    q[0] = S, d[S] = 0, incf[S] = INF;
    while (hh != tt) {
        int t = q[hh++];
        if (hh == N) hh = 0;
        st[t] = false;

        for (int i = h[t]; i != -1; i = ne[i]) {
            int ver = e[i];
            if (f[i] && d[ver] > d[t] + w[i]) {
                d[ver] = d[t] + w[i];
                pre[ver] = i;
                incf[ver] = min(f[i], incf[t]);
                if (!st[ver]) {
                    q[tt++] = ver;
                    if (tt == N) tt = 0;
                    st[ver] = true;
                }
            }
        }
    }
    return incf[T] > 0; //如果大于0说明S可以走到T 不然就不连通
}
int EK(int & flow, int & cost) {
    flow = cost = 0;
    while (spfa()) {
        int t = incf[T]; //当前找到的新的增广路的流量
        flow += t, cost += t * d[T];
        for (int i = T; i != S; i = e[pre[i] ^ 1]) {
            f[pre[i]] -= t;
            f[pre[i] ^ 1] += t;
        }
    }
    return cost;
}
int main() {
    scanf("%d", &n);
    S = 0, T = n * 2 + 1;
    memset(h, - 1, sizeof h);
    for (int i = 1; i <= n; i++) {
        add(S, i, 1, 0);
        add(n + i, T, 1, 0);
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            int c;
            scanf("%d", &c);
            add(i, n + j, 1, c);
        }
    int flow, cost;
    //最小费用
    printf("%d\n", EK(flow, cost));
    for (int i = 0; i < idx; i += 2) { //边取反
        f[i] += f[i ^ 1], f[i ^ 1] = 0;
        w[i] = -w[i], w[i ^ 1] = -w[i ^ 1];
    }
    //最大费用
    printf("%d\n", -EK(flow, cost));
    return 0;
}
```

#### 费用流之网格图模型
在一个 $N \times N$ 的矩形网格中，每个格子里都写着一个非负整数。
可以从左上角到右下角安排 $K$ 条路线，每一步只能往下或往右，沿途经过的格子中的整数会被取走。
若多条路线重复经过一个格子，只取一次。
求能取得的整数的和最大是多少。

输入格式：第一行包含两个整数 $N$ 和 $K$。
接下来 $N$ 行，每行包含 $N$ 个不超过 $1000$ 的整数，用来描述整个矩形网格。
输出能取得的最大和。

每个点拆点，但是拆点有技巧，点内部要连 $2$ 条边，
一条的容量为 $1$，费用为点权 $c$，代表这个点被当前路径选择掉了，对答案产生贡献，
另外一条边容量 INF,费用为 $0$，代表一个已经被选过的点的存在，但会被其他很多路径选择，对答案没贡献，
虚拟 $S$ 向左上角入点连边，容量 $k$，费用 $0$，右下角出点向 $T$ 连边，容量 $k$，费用 $0$

```cpp
const int N = 5010, M = 20010, INF = 0x3f3f3f3f;
int n, k, S, T;
int h[N], e[M], ne[M], f[M], w[M], idx;
int q[N], d[N], pre[N], incf[N];
bool st[N];
int get(int x, int y, int t) { //0代表入点 1代表出点
    //每个点的入点编号为2 * x 出点为 2 * x + 1
    return (x * n + y) * 2 + t;
}
void add(int a, int b, int c, int d) {
    e[idx] = b, f[idx] = c, w[idx] = d, ne[idx] = h[a], h[a] = idx ++;
    e[idx] = a, f[idx] = 0, w[idx] = -d, ne[idx] = h[b], h[b] = idx ++;
}
bool spfa() {
    int hh = 0, tt = 1;
    memset(d, 0xcf, sizeof d); //注意是求最大费用
    memset(incf, 0, sizeof incf);
    q[0] = S, d[S] = 0, incf[S] = INF;
    while (hh != tt) {
        int t = q[hh++];
        if (hh == N) hh = 0;
        st[t] = false;

        for (int i = h[t]; i != -1; i = ne[i]) {
            int ver = e[i];
            if (f[i] && d[ver] < d[t] + w[i]) {
                d[ver] = d[t] + w[i];
                pre[ver] = i;
                incf[ver] = min(f[i], incf[t]);
                if (!st[ver]) {
                    q[tt++] = ver;
                    if (tt == N) tt = 0;
                    st[ver] = true;
                }
            }
        }
    }
    return incf[T] > 0; //如果大于0说明S可以走到T 不然就不连通
}
int EK() {
    int cost = 0;
    while (spfa()) {
        int t = incf[T]; //当前找到的新的增广路的流量
        cost += t * d[T];
        for (int i = T; i != S; i = e[pre[i] ^ 1]) {
            f[pre[i]] -= t;
            f[pre[i] ^ 1] += t;
        }
    }
    return cost;
}
int main() {
    scanf("%d%d", &n, &k);
    S = 2 * n * n, T = S + 1; //ST编号随便设，只要不和图中的点重合即可
    memset(h, - 1, sizeof h);
    add(S, get(0, 0, 0), k, 0); //虚拟S向左上角的点入点连边
    add(get(n - 1, n - 1, 1), T, k, 0); //右下角出点向T连边
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            int c; scanf("%d", &c);
            add(get(i, j, 0), get(i, j, 1), 1, c); //点内部连第一条边
            add(get(i, j, 0), get(i, j, 1), INF, 0);//点内部第二条边
            if (i + 1 < n) add(get(i, j, 1), get(i + 1, j, 0), INF, 0); //每个点向下连边
            if (j + 1 < n) add(get(i, j, 1), get(i, j + 1, 0), INF, 0); //向右连边
        }
    printf("%d\n", EK());
    return 0;
}
```

#### 费用流之无源汇上下界可行流

NOI2008志愿者招募：项目需要 $N$ 天才能完成，其中第 $i$ 天至少需要 $A_i$ 个人。
一共有 $M$ 类志愿者可以招募。
其中第 $i$ 类可以从第 $S_i$ 天工作到第 $T_i$ 天，招募费用是每人 $C_i$ 元。

输入格式：第一行包含两个整数 $N,M$，表示完成项目的天数和可以招募的志愿者的种类。
接下来的一行中包含 $N$ 个非负整数，表示每天至少需要的志愿者人数。
接下来的 $M$ 行中每行包含三个整数 $S_i,T_i,C_i$，含义如上文所述。
可以认为每类志愿者的数量都是无限多的，输出最优方案的总费用。

对于一天 $i$，让 $i$ 点向 $i+1$ 点连边。流量下界是 $A_i$、上界是正无穷，费用是 $0$，这条边的流量意味着第 $i$ 天的工作人数，
对于一类志愿者 $j$，让 $T_j+1$ 向 $S_j$ 连一条容量无界限，费用是 $C_i$ 的边，每个志愿者相当于在流网络的一单位的流量流过了一个环，这个问题变成了最小费用无源汇上下界可行流。

```cpp
const int N = 1010, M = 24010, INF = 0x3f3f3f3f;
int n, m, S, T;
int h[N], e[M], f[M], w[M], ne[M], idx;
int q[N], d[N], pre[N], incf[N];
bool st[N];
void add(int a, int b, int c, int d) {
    e[idx] = b, f[idx] = c, w[idx] = d, ne[idx] = h[a], h[a] = idx ++;
    e[idx] = a, f[idx] = 0, w[idx] = -d, ne[idx] = h[b], h[b] = idx ++;
}
bool spfa() {
    int hh = 0, tt = 1;
    memset(d, 0x3f, sizeof d);
    memset(incf, 0, sizeof incf);
    q[0] = S, d[S] = 0, incf[S] = INF;
    while (hh != tt) {
        int t = q[hh++];
        if (hh == N) hh = 0;
        st[t] = false;
        for (int i = h[t]; i != -1; i = ne[i]) {
            int ver = e[i];
            if (f[i] && d[ver] > d[t] + w[i]) {
                d[ver] = d[t] + w[i];
                pre[ver] = i;
                incf[ver] = min(f[i], incf[t]);
                if (!st[ver]) {
                    q[tt++] = ver;
                    if (tt == N) tt = 0;
                    st[ver] = true;
                }
            }
        }
    }
    return incf[T] > 0; //如果大于0说明S可以走到T 不然就不连通
}
int EK() {
    int cost = 0;
    while (spfa()) {
        int t = incf[T]; //当前找到的新的增广路的流量
        cost += t * d[T];
        for (int i = T; i != S; i = e[pre[i] ^ 1]) {
            f[pre[i]] -= t;
            f[pre[i] ^ 1] += t;
        }
    }
    return cost;
}
int main() {
    scanf("%d%d", &n, &m);
    S = 0, T = n + 2;
    memset(h, -1, sizeof h);
    int last = 0; //上一个点的出流量 就是下一个点的入流量
    for (int i = 1; i <= n; i++) {
        int cur; //当前天需要的人数 也就是下界
        scanf("%d", &cur);
        if (last > cur) add(S, i, last - cur, 0);
        else if (last < cur) add(i, T, cur - last, 0);
        add(i, i + 1, INF - cur,  0); //下界cur 上界INF 每个点向下一个点
        last = cur;
    }
    add(S, n + 1, last, 0); //处理最后一个点,连向S，让图无源
    while (m --) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(b + 1, a, INF, c);
    }
    printf("%d\n", EK());
    return 0;
}
```

#### 2-SAT

给定 $n$ 个还未赋值的布尔变量 $x_1∼x_n$。
现在有 $m$ 个条件，每个条件的形式为 “$x_i$ 为 $0/1$ 或 $x_j$ 为 $0/1$ 至少有一项成立”，例如 “$x_1$ 为 $1$ 或 $x_3$ 为 $0$”、“$x_8$ 为 $0$ 或 $x_4$ 为 $0$” 等。
现在，请你对这 $n$ 个布尔变量进行赋值（$0$ 或 $1$），使得所有 $m$ 个条件能够成立。

输入格式：第一行包含两个整数 $n,m$。
接下来 $m$ 行，每行包含四个整数 $i,a,j,b$，用来描述一个条件，表示 “$x_i$ 为 $a$ 或 $x_j$ 为 $b$”。

输出格式：
如果问题有解，则第一行输出 `POSSIBLE`，第二行输出 $n$ 个整数表示赋值后的 $n$ 个变量 $x_1∼x_n$ 的值（$0$ 或 $1$），整数之间用单个空格隔开。
如果问题无解，则输出一行 `IMPOSSIBLE` 即可。
如果答案不唯一，则输出任意一种正确答案即可。

```cpp
const int N = 2000010, M = 2000010; //每对关系都要连2条
int n, m;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], ts, stk[N], top;
int id[N], cnt;
bool ins[N];
void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}
void tarjan(int u) {
    dfn[u] = low[u] = ++ts;
    stk[++top] = u, ins[u] = true;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (!dfn[j]) {
            tarjan(j);
            low[u] = min(low[u], low[j]);
        } else if (ins[j]) low[u] = min(low[u], dfn[j]);
    }
    if (low[u] == dfn[u]) {
        int y;
        cnt ++;
        do {
            y = stk[top --], ins[y] = false, id[y] = cnt;
        } while (y != u);
    }
}
void solve() {
    cin >> n >> m;
    memset(h, -1, sizeof h);
    while (m --) {
        int i, a, j, b;
        scanf("%d%d%d%d", &i, &a, &j, &b);
        i--; j-- ; //编号改为从0开始
        add(2 * i + !a, 2 * j + b); //非A->B(A and B)
        add(2 * j + !b, 2 * i + a); //非B->A(B and A)
    }
    for (int i = 0; i < n * 2; i++)
        if (!dfn[i]) tarjan(i);
    for (int i = 0; i < n; i++)
        if (id[i * 2] == id[i * 2 + 1]) {
            puts("IMPOSSIBLE");
            return;
        }
    puts("POSSIBLE");
    for (int i = 0; i < n; i++)
        //2 * i代表假 2 * i + 1代表真
        //tarjan求出的是拓扑序逆序，2-SAT的答案是取拓扑序靠后的变元
        if (id[i * 2] < id[i * 2 + 1]) printf("0 ");
        else printf("1 ");
}
int main() {
    solve();
    return 0;
}
```


#### 最小树形图 O$(n \times m)$
POJ3164指挥网络：多组数据，每组数据第一行包含两个整数 $N,M$，表示点数和边数。
接下来 $N$ 行，其中第 $i$ 行包含两个整数 $x_i,y_i$，表示点 $i$ 的位置坐标为 $(x_i,y_i)$。

接下来 $M$ 行，每行包含两个整数 $a,b$，表示有向边 $(a,b)$。

输出格式：对于每个测试数据，输出结果占一行。
如果有解，则输出树形图所有边权和，保留两位小数。
否则输出 `poor snoopy`。

```cpp
#define x first
#define y second
typedef pair<double, double> pdd;
const int N = 110;
const double INF = 0x3f3f3f3f;
int n, m;
pdd q[N]; //所有的点
bool g[N][N]; //邻接矩阵
double d[N][N], bd[N][N]; //d[][]记录欧几里得距离 bd是缩点的备份数组
int pre[N]; //pre记录每个点的前驱点
int dfn[N], low[N], ts, stk[N], top;
int id[N], cnt;
bool st[N], ins[N];
void dfs(int u) {
    st[u] = true;
    for (int i = 1; i <= n; i++)
        if (g[u][i] && !st[i])
            dfs(i);
}
double get_dist(int a, int b) {
    double dx = q[a].x - q[b].x;
    double dy = q[a].y - q[b].y;

    return sqrt(dx * dx + dy * dy);
}
bool check_con() { //检验连通性
    memset(st, 0, sizeof st);
    dfs(1);
    for (int i = 1; i <= n; i++)
        if (!st[i]) return false;
    return true;
}
void tarjan(int u) { //判断是否存在环
    dfn[u] = low[u] = ++ts;
    stk[++top] = u, ins[u] = true;
    int j = pre[u];
    if (!dfn[j]) {
        tarjan(j);
        low[u] = min(low[u], low[j]);
    } else if (ins[j]) low[u] = min(low[u], dfn[j]);
    if (low[u] == dfn[u]) {
        int y;
        ++cnt;
        do {
            y = stk[top --], ins[y] = false, id[y] = cnt;
        } while (y != u);
    }
}
double work() {
    double res = 0; //结果
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (g[i][j]) d[i][j] = get_dist(i, j);
            else d[i][j] = INF;
    while (1) { //迭代
        for (int i = 1; i <= n; i++) { //找出所有点入边权最小的入点
            pre[i] = i; //初始所有点的前驱点为自身
            for (int j = 1; j <= n; j++)
                if (d[pre[i]][i] > d[j][i])
                    pre[i] = j;
        }
        memset(dfn, 0, sizeof dfn);
        ts = cnt = 0;
        for (int i = 1; i <= n; i++)
            if (!dfn[i])
                tarjan(i);
        if (cnt == n) { //SCC数量等于点的数量 说明不存在环 算法结束
            for (int i = 2; i <= n; i++)
                res += d[pre[i]][i];
            break;
        }
        for (int i = 2; i <= n; i++) //加上所有环的边权
            if (id[pre[i]] == id[i])
                res += d[pre[i]][i];
        //初始化备份数组以及缩点
        for (int i = 1; i <= cnt; i++)
            for (int j = 1; j <= cnt; j++)
                bd[i][j] = INF; //初始化备份数组
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (d[i][j] < INF && id[i] != id[j]) { //i j不在同一个SCC中
                    /*
                    缩点时候，在一个SCC中的点，全部用该SCC的id来表示
                    存在bd[][]数组中，就相当于缩点了
                    */
                    int a = id[i], b = id[j];
                    if (id[pre[j]] == id[j]) //j在环中
                        bd[a][b] = min(bd[a][b], d[i][j] - d[pre[j]][j]);
                    else bd[a][b] = min(bd[a][b], d[i][j]); //普通边 不在环中
                }
        n = cnt;
        memcpy(d, bd, sizeof d);
    }
    return res;
}
int main() {
    while (~scanf("%d%d", &n, &m)) {
        for (int i = 1; i <= n; i++)
            scanf("%lf%lf", &q[i].x, &q[i].y);
        memset(g, 0, sizeof g);
        while (m --) {
            int a, b;
            scanf("%d%d", &a, &b);
            if (a != b && b != 1) g[a][b] = true; //注意判断自环 以及忽略指向起点的边
        }
        if (!check_con()) puts("poor snoopy"); //不连通 无解
        else printf("%.2lf\n", work());
    }
    return 0;
}
```
