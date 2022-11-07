#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
using pdd = pair<double, double>;

/*
https://blog.csdn.net/qq_43580151/article/details/99053417
https://blog.csdn.net/qq_34731703/article/details/53965684
*/

/*
关于要先加上所有环的边权，然后再重新更新指向环内的点的边权的原因：

定理1：对于一个连通图中所有的环，也就是每次迭代找出的所有环，这些环必然没有哦相交的重合的边，因为每个点的前驱点必然唯一
定理2：在所有的环中，每个环只去掉一个边（未必是最大的边），一定可以构成最小树形图

考虑缩点后环，存在指向这个环上一个点A的点B，那么为了构成最小树形图，必然要去掉A在环内的入边，才能使得A入度为1，而且要破环
这样先加上所有环的边权，然后遇到指向环上点的某些点，边权为该点入边边权减去环上点入边的边权，恰好抵消，也就是相当于减去了环上那个点的入边权
注意在缩点过程中，直接用的是SCC之间的最短距离来更新，也就是只记录SCC之间的最短边，这样就把一个SCC中的所有边除了那个破环的边权全部加上，
然后把缩点后的新图当作下一次迭代的图，其实在破环的过程中，是对所有指向这个环的入边进行取min来计算最小的破环代价，因为无论在环的任何一个位置破开
都不影响树的结构，都可以构成树。
*/

const int N = 110;
const double INF = 0x3f3f3f3f;
int n, m;
pdd q[N];
bool g[N][N];
double d[N][N], bd[N][N]; //bd is backup array
int pre[N]; //each point's previous point
int dfn[N], low[N], ts, stk[N], top; //tarjan
int id[N], cnt; // 缩点
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

bool check_connect() { //有向图不连通直接无解
    memset(st, 0, sizeof st);
    dfs(1);
    for (int i = 1; i <= n; i++)
        if (!st[i]) return false;
    return true;
}

void tarjan(int u) {
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
            y = stk[top--], ins[y] = false, id[y] = cnt;
        } while (y != u);
    }
}

double edmonds() {
    double res = 0;
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

void solve() {
    while (cin >> n >> m) {
        for (int i = 1; i <= n; i++)
            cin >> q[i].x >> q[i].y;
        memset(g, 0, sizeof g);
        while (m --) {
            int a, b;
            cin >> a >> b;
            if (a != b && b != 1) g[a][b] = true; //ignore edges that point to the root, 1 is root
        }
        if (!check_connect()) puts("poor snoopy");
        else printf("%.2lf\n", edmonds());
    }
}

int main() {
    solve();
    return 0;
}