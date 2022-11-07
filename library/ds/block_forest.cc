/*BZOJ2125给一个 N 个点 M 条边的仙人掌,Q组询问每次询问两点之间的最短路长度。第一行N,M,Q。下接M行，每行v,u,w表示一条无向边v-u长度为 w。最后Q行每行v,u表示询问。
先建圆方树，然后求lca, 还要维护所有点到圆方树root的距离,求出的lca如果是圆点，直接差分求距离即可。如果lca是方点需要特判一下，对环上的2条路径和取min,路径和用前缀和维护*/
const int N = 12010, M = N * 3; //原图双向边+圆方树单向边
int n, m, Q, new_n;
int h1[N], h2[N], e[M], w[M], ne[M], idx;
int dfn[N], low[N], cnt;
//s[]环的前缀和距离 stot[i] i所在环的边权和
//fu[i] i的父节点 fw[i] i和父节点的边权
int s[N], stot[N], fu[N], fw[N];
int fa[N][14], depth[N], d[N]; //倍增lca的数组
int A, B; //方点lca下的2个点 也就是环上的2个点
void add(int h[], int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx ++;
}
void build_circle(int x, int y, int z) { //新图上将环改为树
    int sum = z;  //z是边(x,y)权值， x,y是环的始终点
    //x->....->y是dfs环的顺序 反向求前缀和数组
    for (int k = y; k != x; k = fu[k]) {
        s[k] = sum;
        sum += fw[k];
    }
    s[x] = stot[x] = sum;
    //新图的点从n开始 每个环的根向方点连边 方点和圆点边权为0
    add(h2, x, ++new_n, 0);
    for (int k = y; k != x; k = fu[k]) {
        stot[k] = sum;
        //方点向其他环上的点连边
        add(h2, new_n, k, min(s[k], sum - s[k]));
    }
}
void tarjan(int u, int from) {
    dfn[u] = low[u] = ++cnt;
    for (int i = h1[u]; i != - 1; i = ne[i]) {
        int j = e[i];
        if (!dfn[j]) {
            fu[j] = u, fw[j] = w[i];
            tarjan(j, i);
            low[u] = min(low[u], low[j]);
            //找到一个桥
            if (dfn[u] < low[j]) add(h2, u, j, w[i]);
        }
        else if (i != (from ^ 1)) low[u] = min(low[u], dfn[j]);
    }
    //tarjan的同时找环 然后建树
    for (int i = h1[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (dfn[u] < dfn[j] && fu[j] != u)
            build_circle(u, j, w[i]);
    }
}
//求出所有点到整颗圆方树root的距离
void dfs_lca(int u, int father) {
    depth[u] = depth[father] + 1;
    fa[u][0] = father;
    for (int k = 1; k <=  13; k++)
        fa[u][k] = fa[fa[u][k - 1]][k - 1];
    for (int i = h2[u]; i != -1; i = ne[i]) {
        int j = e[i];
        d[j] = d[u] + w[i];
        dfs_lca(j, u);
    }
}
//倍增lca模板
int lca(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    for (int k = 13; k >= 0; k --)
        if (depth[fa[a][k]] >= depth[b])
            a = fa[a][k];
    if (a == b) return a;
    for (int k = 13; k >= 0; k --)
        if (fa[a][k] != fa[b][k]) {
            a = fa[a][k];
            b = fa[b][k];
        }
    A = a, B = b;
    return fa[a][0];
}
int main() {
    scanf("%d%d%d", &n, &m, &Q);
    new_n = n;
    memset(h1, -1, sizeof h1);
    memset(h2, -1, sizeof h2);
    while (m --) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(h1, a, b, c), add(h1, b, a, c);
    }
    tarjan(1, -1);
    dfs_lca(1, 0);
    while (Q --) {
        int a, b;
        scanf("%d%d", &a, &b);
        int p = lca(a, b);
        if (p <= n) //lca是圆点
            printf("%d\n", d[a] + d[b] - d[p] * 2);
        else {
            //环下边的2条路径长度
            int da = d[a] - d[A], db = d[b] - d[B];
            int l = abs(s[A] - s[B]);
            int dm = min(l, stot[A] - l);
            printf("%d\n", da + dm + db);
        }
    }
    return 0;
}
/*SHOI2008《仙人掌图》定义在图上两点之间的距离为这两点之间最短路径的距离。定义一个图的直径为这张图相距最远的两个点的距离。每条边的权值都是1,求给定的仙人图的直径。
求出每个点作为最高点 向下的最长路径和次长路径 加起来就是经过该点的最长路径 求出所有的路径来更新答案。
建立圆方树之后，最高点分情况讨论，设最长路径d1 次长路径d2:
1.最高点如果是圆点，直接ans = max(ans, d1 + d2)
2.如果是方点，这里要注意不一定这个路径经过环的根，也就是不一定经过这个方点的，因为是个环,也许只是环上的一段劣弧
由于边权都是1，对于环上任意2点 x,y， 设f[i]表示点i向下的最长路径,那么经过xy的这条最长路径长度为f[x] + f[y] + x - y, 这里的xy都是环上加点的下标 所以可以直接用差x - y计算这段劣弧的长度。
枚举所有的xy点对是O(n^2)的不可取，需要用到单调队列优化，也就是滑动窗口。对于一个x，求出一个向后长度为size/2的一段里面的y，使得f[x] + f[y] + x - y 最小，size是环的长度。
公式改为 f[x] + x + f[y] - y; //将f[x] + x看作整体即可,单调队列求的是 f[y] - y的最大值*/
const int N = 100010, M = N * 3, INF = 0x3f3f3f3f;
int n, m, new_n;
int h1[N], h2[N], e[M], w[M], ne[M], idx;
int dfn[N], low[N], cnt;
int s[N], stot[N], fu[N], fw[N];
//d单调队列 q单调队列下标 f存该点到叶子节点的最长距离
int d[N], f[N], q[N];
int ans;
void add(int h[], int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}
void build_cricle(int x, int y, int z) {
    int sum = z;
    for (int k = y; k != x; k = fu[k]) {
        s[k] = sum;
        sum += fw[k];
    }
    s[x] = stot[x] = sum;
    add(h2, x, ++new_n, 0);
    for (int k = y; k != x; k = fu[k]) {
        stot[k] = sum;
        add(h2, new_n, k, min(s[k], sum - s[k]));
    }
}
void tarjan(int u, int from) {
    dfn[u] = low[u] = ++cnt;
    for (int i = h1[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (!dfn[j]) {
            fu[j] = u, fw[j] = w[i];
            tarjan(j, i);
            low[u] = min(low[u], low[j]);
            if (dfn[u] < low[j]) add(h2, u, j, w[i]);//桥连边
        }
        else if (i != (from ^ 1)) low[u] = min(low[u], dfn[j]);
    }
    //每个桥的端点连接的环 建树
    for (int i = h1[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (dfn[u] < dfn[j] && fu[j] != u)
            build_cricle(u, j, w[i]);
    }
}
int dfs(int u) {
    int d1 = 0, d2 = 0;//u为最高点向下最长距离和次长距离
    for (int i = h2[u]; i != -1; i = ne[i]) {
        int j = e[i];
        int t = dfs(j) + w[i];
        if (t >= d1) d2 = d1, d1 = t;
        else if (t > d2) d2 = t;
    }
    f[u] = d1; //点u向下走的最长距离
    if (u <= n) ans = max(ans, d1 + d2); //u是圆点
    else { //u是方点
        int sz = 0;
        d[sz++] = -INF;
        for (int i = h2[u]; i != -1; i = ne[i])
            d[sz++] = f[e[i]]; //先把一个环的点入队列
        //环复制一遍 展开为链
        for (int i = 0; i < sz; i++) d[sz + i] = d[i];
        int hh = 0, tt = -1;
        //固定i滑动窗口来更新
        for (int i = 0; i < sz * 2; i ++) {
            //队列元素小于环长度一半 保证是劣弧
            if (hh <= tt && i - q[hh] > sz / 2) hh++;
            if (hh <= tt) ans = max(ans, d[i] + i + d[q[hh]] - q[hh]);
            while (hh <= tt && d[q[tt]] - q[tt] <= d[i] - i) tt --; //保证单调递减
            q[++tt] = i;
        }
    }
    return f[u];
}
int main() {
    scanf("%d%d", &n, &m);
    new_n = n;
    memset(h1, -1, sizeof h1);
    memset(h2, -1, sizeof h2);
    while (m --) {
        int k, x, y;
        scanf("%d%d", &k, &x);
        for (int i = 0; i < k - 1; i++) {
            scanf("%d", &y);
            add(h1, x, y, 1), add(h1, y, x, 1);
            x = y;
        }
    }
    tarjan(1, -1);
    dfs(1);
    printf("%d\n", ans);
    return 0;
}