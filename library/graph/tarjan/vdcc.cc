/*
例题: Tarjan 判断割点
给定一个由 n 个点 m 条边构成的无向图，请你求出该图删除一个点之后，连通块最多有多少。输入包含多组数据。
每组数据第一行包含两个整数 n,m。
接下来 m 行，每行包含两个整数 a,b，表示 a,b 两点之间有边连接。
数据保证无重边。
点的编号从 0 到 n−1。
读入以一行 0 0 结束。
*/
//注意题目给的并以一定是连通图 所以 要先求一次所有连通块 然后分别处理每个连通块
//一共有cnt个连通块, 那么处理完一个连通块假设该连通块可以分为s个最多, 那么处理完该连通块的结果就是s + cnt - 1
//依次同样方法处理所有连通块即可
//求一个连通块的s: 判断割点
const int N = 10010, M = 30010;
int n, m;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], timestamp;
int root, ans;
void add(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx ++;
}
void tarjan(int u) {
    dfn[u] = low[u] = ++timestamp;
    int cnt = 0; //当前连通块中的cnt
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (!dfn[j]) {
            tarjan(j);
            low[u] = min(low[u], low[j]);
            if (low[j] >= dfn[u])
                cnt ++;
        }
        else low[u] = min(low[u], dfn[j]);
    }
    if (u != root && cnt) cnt ++; //u节点有cnt个子树 去掉u后 u的父亲连通块就会多出来 以及cnt个单独的子树
    ans = max(ans, cnt);
}
int main() {
    while (scanf("%d%d", &n, &m) , n || m) {
        memset(dfn, 0, sizeof dfn);
        memset(h, -1, sizeof h);
        idx = timestamp = 0;
        while (m --) {
            int a, b;
            scanf("%d%d", &a, &b);
            add(a, b); add(b, a);
        }
        int cnt = 0;
        ans = 0; //每次清空答案
        for (root = 0; root < n; root++) {
            if (!dfn[root]) {
                cnt ++;  //非连通图 tarjan还可以顺便求出连通块数量 因为tarjan的本质就是dfs
                tarjan(root);
            }
        }
        printf("%d\n", ans + cnt - 1);
    }
    return 0;
}
//例题:一个孤立的点也是一个v-DCC
/*
矿场搭建:某些挖煤点设立救援出口，使得无论哪一个挖煤点坍塌之后，其他挖煤点的工人都有一条道路通向救援出口。
请写一个程序，用来计算至少需要设置几个救援出口，以及不同最少救援出口的设置方案总数。
*/
/*
    一个图中至少要有2个救援出口 因为如果有1个 那么这个出口坏掉 就不能出去
    注意题意暗示 只会有一个挖煤点出事 而且不是连通图 有多个连通块 处理每个连通块的方案数 总的方案数 就是乘起来即可
    1) 如果一个连通块中没有割点 那么随便选2个即可 假设连通块点的数量是cnt 那么就是cnt选2
    2) 如果有割点 就要缩点 每个割点都至少属于2个v-DCC 假设缩点后的每个分量是一个大点
    2.1)如果一个大点的度数为1 也就是这个大点只和一个割点连通 那么就必须要在大点内部，而且不是割点的点中随便放一个
        因为割点坏掉，那么大点就内部封死了 方案数是cnt-1
    2.2)如果一个大点的度数大于1 那么无需在该大点内部 设置出口 忽略这个大点即可
    从缩点的过程来看 每个缩点后的大点的度数 就是这个分量内部的割点的个数 因为割点会被独立出去
    缩点的时候，每个割点都会向所有包含它的v-DCC连边
    从树的本质理解：缩点后的图是一个无环图 也就是一棵树，度数为0的点都是叶子节点
*/
const int N = 1010, M = 510;
int n, m;
int h[N], e[M], ne[M], idx;
int dfn[N], stk[N], low[N], top;
int timestamp;
int dcc_cnt;
vector<int> dcc[N];
bool cut[N]; //判断是否是割点
int root;
void add(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx ++;
}
void tarjan(int u) {
    dfn[u] = low[u] = ++timestamp;
    stk[++top] = u;

    if (u == root && h[u] == -1) {
        dcc_cnt ++; //孤立点
        dcc[dcc_cnt].push_back(u);
        return;
    }
    int cnt = 0;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (!dfn[j]) {
            tarjan(j);
            low[u] = min(low[u], low[j]);
            if (dfn[u] <= low[j]) {
                cnt ++; //u节点的子树的数量
                //判断割点
                if (u != root || cnt > 1) cut[u] = true;
                ++dcc_cnt;
                int y;
                do {
                    y = stk[top --];
                    dcc[dcc_cnt].push_back(y);
                } while (y != j); //注意此处
                dcc[dcc_cnt].push_back(u);
            }
        }
        else low[u] = min(low[u], dfn[j]);
    }
}
int main() {
    int t = 1;  // 输出样例计数器
    while (cin >> m && m) {
        for (int i = 1; i <= dcc_cnt; i++) dcc[i].clear();
        memset(h, -1 , sizeof h);
        idx = timestamp = n = dcc_cnt = top = 0;
        memset(dfn, 0, sizeof dfn);
        memset(cut, 0, sizeof cut);
        while (m --) {
            int a, b;
            cin >> a >> b;
            n = max(n, a), n = max(n, b);
            add(a, b); add(b, a);
        }
        for (root = 1; root <= n; root++) //以每个点为root深搜一次
            if (!dfn[root]) tarjan(root);
        ull res = 0; //最少需要的出口的数量
        ull num = 1; //方案数
        //求出割点的数量 遍历每一个dcc
        for (int i = 1; i <= dcc_cnt; i++) {
            int cnt = 0;
            for (int j = 0; j < sz(dcc[i]); j++)
                if (cut[dcc[i][j]])
                    cnt ++;
            //处理当前的dcc 分类讨论 注意要特判只有一个孤立点的情况
            if (cnt == 0) {
                if (sz(dcc[i]) > 1) res += 2, num *= sz(dcc[i]) * (sz(dcc[i]) - 1) / 2;
                else res ++;
            }
            else if (cnt == 1) {
                res ++;
                if (sz(dcc[i]) > 1) num *= sz(dcc[i]) - 1;
                else num *= 1;
            }
        }
        printf("Case %d: %llu %llu\n", t++, res, num);
    }
    return 0;
}