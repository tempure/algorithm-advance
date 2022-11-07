/*
倍增求LCA
给定一棵包含 n 个节点无向树，节点编号互不相同，但不一定是1~n。
有 m 个询问，每个询问给出了一对节点的编号 x 和 y，询问 x 与 y 的祖孙关系。
*/
//规定d[0] = 0 第0层的深度是0 ，以及跳出根节点后 f[x][k] = 0 这样跳出后就不会出界 而是继续判断
//若a是b的祖先 那么lca(a, b) 就是a
const int N = 40010, M = 2 * N;
int n, m;
int h[N], e[M], ne[M], idx;
int depth[N], fa[N][16]; // k最大是log2(N)
int q[N]; //BFS队列
void add(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx ++;
}
void bfs(int root) {
    memset(depth, 0x3f, sizeof depth);
    depth[0] = 0, depth[root] = 1; //根节点所在的层数定义为1
    int hh = 0, tt = 0;
    q[0] = root;
    while (hh <= tt) {
        int t = q[hh++];
        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (depth[j] > depth[t] + 1) {
                depth[j] = depth[t] + 1;
                q[++tt] = j;
                fa[j][0] = t; //跳一步
                for (int k = 1; k <= 15; k++) //处理j的所有祖先节点
                    fa[j][k] = fa[fa[j][k - 1]][k - 1];
            }
        }
    }
}
int lca(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b); //从低的往高的跳
    //跳到同一层
    for (int k = 15; k >= 0; k--)
        if (depth[fa[a][k]] >= depth[b])
            a = fa[a][k];
    if (a == b) return a; //return b 这种情况是b是a的祖先
    //同时往上跳
    for (int k = 15; k >= 0; k--)
        if (fa[a][k] != fa[b][k]) {
            a = fa[a][k];
            b = fa[b][k];
        }
    return fa[a][0]; //或者fa[b][0]
}
int main() {
    scanf("%d", &n);
    int root = 0;
    memset(h, -1, sizeof h);
    for (int i = 0; i < n; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        if (b == -1) root = a;
        else add(a, b), add(b, a);
    }
    bfs(root); //预处理depth数组和倍增数组
    scanf("%d", &m);
    while (m --) {
        int a, b ;
        scanf("%d%d", &a, &b);
        int p = lca(a, b);
        if (p == a) puts("1");
        else if (p == b) puts("2");
        else puts("0");
    }
    return 0;
}
/*次小生成树
给定一张 N 个点 M 条边的无向图，求无向图的严格次小生成树。
设最小生成树的边权之和为sum，严格次小生成树就是指边权之和大于sum的生成树中最小的一个。
*/
//倍增 LCA 优化寻找最大和次大边权的过程 暴力dfs改为倍增求最大次大
//其余步骤不变 先kruskal 然后枚举所有非树边
//d1[i][j] 表示从i开始向上跳2^j步 过程当中，路上的最大边权
//d2[i][j] 表示从i开始向上跳2^j步 路径上的次大边权
const int N = 100010, M = 300010;
const int INF = 0x3f3f3f3f;
int n, m;
int h[N], e[M], w[M], ne[M], idx;
struct Edge {
    int a, b, w;
    bool used; //是否是树边
    bool operator< (const Edge &t) {
        return w < t.w;
    }
} edge[M];
int p[N]; //kruskal的并查集
int depth[N], fa[N][17], d1[N][17], d2[N][17]; //最大边和次大边
int q[N]; //BFS求节点的树深度
void add(int a, int b, int c) {
    e[idx] = b;
    ne[idx] = h[a];
    w[idx] = c;
    h[a] = idx ++;
}
int find(int x) {
    if (x != p[x]) p[x] = find(p[x]);
    return p[x];
}
ll kruskal() {
    for (int i = 1; i <= n; i++) p[i] = i;
    sort(edge, edge + m);
    ll res = 0;
    for (int i = 0; i < m; i++) {
        int a = find(edge[i].a), b = find(edge[i].b), w = edge[i].w;
        if (a != b) {
            p[a] = b;
            res += w;
            edge[i].used = true;
        }
    }
    return res;
}
void build() {
    memset(h, -1, sizeof h);
    for (int i = 0; i < m; i++)
        if (edge[i].used) {
            int a = edge[i].a, b = edge[i].b, w = edge[i].w;
            add(a, b, w); add(b, a, w);
        }
}
void bfs() { //预处理节点深度 以及每个点跳2^k后路径上的最大边和次大边
    memset(depth, 0x3f, sizeof depth);
    depth[0] = 0, depth[1] = 1;
    int hh = 0, tt = 0;
    q[0] = 1;
    while (hh <= tt) {
        int t = q[hh ++];
        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (depth[j] > depth[t] + 1) {
                depth[j] = depth[t] + 1;
                q[++tt] = j;
                fa[j][0] = t;
                d1[j][0] = w[i], d2[j][0] = -INF;
                for (int k = 1; k <= 16; k++) {
                    int anc =  fa[j][k - 1];
                    fa[j][k] = fa[anc][k - 1];
                    //每次更新一段 都是用2小端来更新，先预处理2次都跳2^(k-1)步然后遍历一次求出
                    int distance[4] = {d1[j][k - 1], d2[j][k - 1], d1[anc][k - 1], d2[anc][k - 1]};
                    d1[j][k] = d2[j][k] = -INF;
                    for (int u = 0; u < 4; u++) {
                        int d = distance[u];
                        if (d > d1[j][k]) d2[j][k] = d1[j][k], d1[j][k] = d;
                        else if (d != d1[j][k] && d > d2[j][k]) d2[j][k] = d;
                    }
                }
            }
        }
    }
}
int lca(int a, int b, int w) {
    static int distance[N * 2];  //缓存每一次跳的一段路上的最大和次大 最后取max
    int cnt = 0;
    if (depth[a] < depth[b]) swap(a, b);
    for (int k = 16; k >= 0; k--)
        if (depth[fa[a][k]] >= depth[b]) {
            distance[cnt++] = d1[a][k];
            distance[cnt++] = d2[a][k];
            a = fa[a][k];
        }
    if (a != b) {
        for (int k = 16; k >= 0; k--)
            if (fa[a][k] != fa[b][k]) { //将
                distance[cnt++] = d1[a][k];
                distance[cnt++] = d2[a][k];
                distance[cnt++] = d1[b][k];
                distance[cnt++] = d2[b][k];
                a = fa[a][k], b = fa[b][k];
            }
        distance[cnt++] = d1[a][0];
        distance[cnt++] = d1[b][0]; //最后加上到lca的一步
    }
    int dist1 = -INF, dist2 = -INF;  //最大值和次大值
    for (int i = 0; i < cnt; i++) {
        int d = distance[i];
        if (d > dist1) dist2 = dist1, dist1 = d;
        else if (d != dist1 && d > dist2) dist2 = d;
    }
    if (w > dist1) return w - dist1;
    if (w > dist2) return w - dist2;
    return INF;
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        edge[i] = {a, b, c};
    }
    ll sum = kruskal(); //最小生成树的权值和
    build(); //建图
    bfs(); //预处理
    ll res = 1e18;
    //枚举非树边
    for (int i = 0; i < m; i++)
        if (!edge[i].used) {
            int a = edge[i].a, b = edge[i].b, w = edge[i].w;
            res = min(res, sum + lca(a, b, w)); //lca返回的是加上最大的边 然年减去原来的树边的值
        }
    printf("%lld\n", res);
    return 0;
}
/*
给出 n 个点的一棵树，多次询问两点之间的最短距离。
边是无向的。
所有节点的编号是 1,2,…,n。
输入格式
第一行为两个整数 n 和 m。n 表示点数，m 表示询问次数；
下来 n−1 行，每行三个整数 x,y,k，表示点 x 和点 y 之间存在一条边长度为 k；
再接下来 m 行，每行两个整数 x,y，表示询问点 x 到点 y 的最短距离。
树中结点编号从 1 到 n。
*/
//在线做法 倍增 离线做法Tarjan算法 复杂度O(N + M) N是节点数量 M是询问数量 比倍增更快
//树上2点的最短距离 就是2点的路径长度 求出2个点到root节点的距离求和 然后减去lca到root距离的2倍
const int N = 20010, M = 2 * N; //无向边 开2倍
int n, m;
int h[N], e[M], w[M], ne[M], idx;
int p[N]; //并查集父节点
int res[N]; //询问的结果
int st[N]; //tarjan 过程中的标记数组
int dist[N]; //每个点和root的距离
vector<pii> query[N]; //询问 first 查询的另外一个点 second是查询编号
void add(int a, int b, int c) {
    e[idx] = b;
    ne[idx] = h[a];
    w[idx] = c;
    h[a] = idx ++;
}
int find(int x) {
    if (x != p[x]) p[x] = find(p[x]);
    return p[x];
}
void dfs(int u, int fa) { //预处理到root的距离
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (j == fa) continue; // 防止反向搜
        dist[j] = dist[u] + w[i];
        dfs(j, u);
    }
}
//正在搜的点标记为1 搜过的点也就是回溯过的点 标记为2  还没有搜过的点标记为0
void tarjan(int u) {
    st[u] = 1; //正在搜的点
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (!st[j]) {
            tarjan(j);
            p[j] = u; //遍历u的所有相邻点 然后合并进并查集
        }
    }
    for (auto item : query[u]) { // 遍历所有和u相关的查询
        int y = item.first, id = item.second;
        if (st[y] == 2) { //如果要查询的点 以及被合并过了
            int anc = find(y);
            res[id] = dist[u] + dist[y] - dist[anc] * 2;
        }
    }
    st[u] = 2; //被遍历过了
}
int main() {
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);
    for (int i = 0; i < n - 1; i ++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c); add(b, a, c);
    }
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        if (a != b) { //如果2节点相同 那就是0, res是全局数组 默认就是0
            query[a].pb({b, i}); //和a查询相关的点是b 查询编号是i
            query[b].pb({a, i});
        }
    }
    for (int i = 1; i <= n; i++) p[i] = i; //初始化并查集
    dfs(1, -1); ////随便拿一个点当root即可 从1号点开始
    tarjan(1); //假设1号就是root了
    for (int i = 0; i < m; i++) printf("%d\n", res[i]);
    return 0;
}