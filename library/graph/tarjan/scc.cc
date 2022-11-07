/*
现在有 N 头牛，编号从 1 到 N，给你 M 对整数 (A,B)，表示牛 A 认为牛 B 受欢迎。
这种关系是具有传递性的，如果 A 认为 B 受欢迎，B 认为 C 受欢迎，那么牛 A 也认为牛 C 受欢迎。
求出有多少头牛被除自己之外的所有牛认为是受欢迎的。
输入格式
第一行两个数 N,M；
接下来 M 行，每行两个数 A,B，意思是 A 认为 B 是受欢迎的（给出的信息有可能重复，即有可能出现多个 A,B）。
*/
//如果暴力 可以在反图上遍历每个点是否能到其他所有点 复杂度O(N * (N + M)) 会超时
//Tarjan 强连通分量+缩点+拓扑图 拓扑图至少存在一个出度为0的点
//A认为B受欢迎，那么就从A向B连一条边
//对于缩点之后的拓扑图 如果存在2个及以上的出度为0的点 那么答案就是0 因为其中一个出度为0的点 肯定不会被另外一个出度为0的点欢迎
//如果只有一个出度为0的缩点 那么就是答案 这个缩点代表的强连通分量里面的缩点之前的点的个数就是答案
//没必要建立缩点之后的拓扑图 只需要遍历一下强连通分量 然后统计出边即可
const int N = 10010, M = 50010;
int n, m;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], timestamp; //时间戳 low数组
int stk[N], top;  //栈和栈顶
bool in_stk[N]; //每个点是否在栈中
int id[N], scc_cnt, sz[N];  //每个点所属的强连通分量编号 强连通分量的总数 每个点所在强连通分量的点的数量
int dout[N]; //记录每个强连通分量的出度
void add(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx ++;
}
void tarjan(int u) {
    dfn[u] = low[u] = ++timestamp; //初始化时间戳 和low数组 然后后期更新low数组
    stk[++top] = u, in_stk[u] = true; //入栈
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (!dfn[j]) {
            tarjan(j);
            low[u] = min(low[u], low[j]);
        }
        else if (in_stk[j]) low[u] = min(low[u], dfn[j]); //如果已经在栈中了 就直接拿来更新low
    }
    if (dfn[u] == low[u]) { //找到强连通分量
        ++ scc_cnt; //数量+1
        int y;
        do {
            y = stk[top--];
            in_stk[y] = false;
            id[y] = scc_cnt;
            sz[scc_cnt]++;
        } while (u != y); //弹出栈顶到u的所有元素 这些元素就组成一个强连通分量
    }
}
int main() {
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);
    while (m --) {
        int a, b ;
        scanf("%d%d", &a, &b);
        add(a, b);
    }
    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            tarjan(i);
    //统计所有点的出度 同是处理缩边后的图的连通分量的出度
    for (int i = 1; i <= n; i++)
        for (int j = h[i]; j != -1; j = ne[j]) {
            int k = e[j];
            int a = id[i], b = id[k];
            if (a != b) dout[a]++; //a b是两个不同强连通分量的编号 那么就在这个缩点图里面 a的出度加一
        }
    int zeros = 0, sum = 0; //出度为0的分量个数 以及所有这样分量内小的点的总数量
    for (int i = 1; i <= scc_cnt; i++)
        if (!dout[i]) {
            zeros ++;
            sum += sz[i];
            if (zeros > 1) { //没有符合条件的牛
                sum = 0;
                break;
            }
        }
    printf("%d\n", sum);
    return 0;
}
/*
恒星的亮度最暗是 1
现在对于 N 颗我们关注的恒星，有 M 对亮度之间的相对关系已经判明。
你的任务就是求出这 N 颗恒星的亮度值总和至少有多大。
输入格式
第一行给出两个整数 N 和 M。
之后 M 行，每行三个整数 T, A, B，表示一对恒星(A, B)之间的亮度关系。恒星的编号从 1 开始。
如果 T = 1，说明 A 和 B 亮度相等。
如果 T = 2，说明 A 的亮度小于 B 的亮度。
如果 T = 3，说明 A 的亮度不小于 B 的亮度。
如果 T = 4，说明 A 的亮度大于 B 的亮度。
如果 T = 5，说明 A 的亮度不大于 B 的亮度。
*/
//此题也可以spfa差分约束跑负环 但是需要栈优化 而且可能会被卡掉
//用强连通分量可以线性复杂度稳过掉
//因为所有的环必然在强连通分量中 此问题有解的前提是图中没有正环 不然不存在最长路
//也就是说会正环出现 a >= b, b >=c, c >= a这种矛盾关系
//同理 如果一个强连通分量中有一个正边权的边 那么必然存在正环 直接意味着无解
//如果有解 那么一个强连通分量内的边权 全部都是0 意思是每个强连通分量内的点到起点的距离都一样的
//那么就进行缩点 然后在拓扑图上直接求和即可
//注意还要一个虚拟原点 又每个边权都>=1 设虚拟原点为x[0] 那么x[i] >= x[0] + 1 每个点向虚拟远点连边权为1的边
const int N = 100010, M = 600010;  //每个点对的关系 最坏是都相等，然后加上虚拟原点的边 一共开3倍
//然后要建缩点后的图 所以需要6倍的边数
int n, m;
int h[N], e[M], ne[M], w[M], idx;
int hs[N]; //缩点图的表头
int dfn[N], low[N], timestamp;
int stk[N], top;
bool in_stk[N];
int id[N], scc_cnt, sz[N]; //答案加上每个连通分量内点的个数 * 距离 所以需要维护size
int dist[N]; //最长路
void add(int h[], int a, int b, int c) {
    e[idx] = b;
    ne[idx] = h[a];
    w[idx] = c;
    h[a] = idx ++;
}
void tarjan(int u) {
    dfn[u] = low[u] = ++timestamp;
    stk[++top] = u, in_stk[u] = true;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (!dfn[j]) {
            tarjan(j);
            low[u] = min(low[u], low[j]);
        }
        else if (in_stk[j])  low[u] = min(low[u], dfn[j]);
    }
    if (dfn[u] == low[u]) {
        ++scc_cnt;
        int y;
        do {
            y = stk[top--];
            in_stk[y] = false;
            id[y] = scc_cnt;
            sz[scc_cnt]++;
        } while (y != u);
    }
}
int main() {
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);
    memset(hs, -1, sizeof hs);
    //虚拟原点连边
    for (int i = 1; i <= n; i++) add(h, 0, i, 1);
    while (m --) {
        int t, a, b;
        scanf("%d%d%d", &t, &a, &b);
        if (t == 1) add(h, b, a, 0), add(h, a, b, 0);
        else if (t == 2) add(h, a, b, 1);
        else if (t == 3) add(h, b, a, 0);
        else if (t == 4) add(h, b, a, 1);
        else add(h, a, b, 0);
    }
    tarjan(0); //0号点可以到其他所有点
    bool success = true;
    //建新的缩点图
    for (int i = 0; i <= n; i++) {
        for (int j = h[i]; j != -1; j = ne[j]) {
            int k = e[j];
            int a = id[i], b = id[k];
            if (a == b) {
                if (w[j] > 0) { //存在正边 无解
                    success = false;
                    break;
                }
            }
            else add(hs, a, b, w[j]);
        }
        if (!success) break; //如果一个分量不成立那么直接退出即可 无解
    }
    if (!success) puts("-1");
    else {
        for (int i = scc_cnt; i; i --) //反向就是拓扑序
            for (int j = hs[i]; j != -1; j = ne[j]) {
                int k = e[j];
                dist[k] = max(dist[k], dist[i] + w[j]);
            }
        ll res  = 0;
        for (int i = 1; i <= scc_cnt; i++) res += 1ll * dist[i] * sz[i];
        printf("%lld\n", res);
    }
    return 0;
}