/*
例题:冗余路径
*/
/*
    一些连通分量的性质：
    一个孤立的点是一个点连通分量
    每个割点至少在2个点连通分量中
    两个割点之间的边不一定是桥 一个桥的两个端点也不一定是割点
    点连通分量和边连通分量没有直接关系 也就是点连不一定是边连
    一个树的每个边都是桥 但每个点不一定是割点，比如叶节点
    树中任意一条边的2个端点构成一个点联通
*/
/*
    题意为给定一个无向连通图 求最少需要加多少条边可以变为e-DCC
    路径相互分离的定义是 两条路径所有的边都不一样不能有相同的边
    所以最终的图的状态是任意一条边都至少在一个环中 等价于e-DCC
    解法：先tarjan缩点 然后缩点后的边 全部都是桥而且是拓扑的
    对于所有度数为1的点，度是出度+入度 都肯定需要连边
    而且在树中 度为1的点 就是所有的叶子节点 那么最少的连法 就是尽量多的"配对"
    假设度为1的点是cnt个 那么答案最少就是 (cnt + 1) / 2
*/
const int N = 5010, M = 20010;
int n, m;
int dcc_cnt;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], timestamp;
int stk[N], id[N], top;
// bool in_stk[N];
bool is_bridge[M];  //判断是不是桥
int d[N]; //每个点的度数
void add(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx ++;
}
void tarjan(int u, int from) {
    dfn[u] = low[u] = ++timestamp;
    stk[++top] = u;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (!dfn[j]) {
            tarjan(j, i);
            low[u] = min(low[u], low[j]); //是搜索树的边 用low更新
            if (dfn[u] < low[j]) //如果成立那就是桥
                is_bridge[i] = is_bridge[i ^ 1] = true;
        }
        else if (i != (from ^ 1)) //i不是搜索树的边 用dfn[j]来更新
            low[u] = min(low[u], dfn[j]);
    }
    if (dfn[u] == low[u]) {
        ++ dcc_cnt;
        int y;
        do {
            y = stk[top --];
            // in_stk[y] = false;
            id[y] = dcc_cnt;
        } while (y != u);
    }
}
int main() {
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);
    while (m --) {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b); add(b, a);
    }
    tarjan(1, -1); //连通图 从一个点开始dfs即可 由于是无向边 要记录当前的边是哪个边过来的
    for (int i = 0; i < idx; i ++) //枚举每个边即可
        if (is_bridge[i])
            d[id[e[i]]] ++;//给i的出边所在点连通分量的度数加一由于是无向边到出边的点又会反过来给i加上
    int cnt = 0;
    for (int i = 1; i <= dcc_cnt; i++)
        if (d[i] == 1) cnt ++;
    printf("%d\n", (cnt + 1) / 2);
    return 0;
}