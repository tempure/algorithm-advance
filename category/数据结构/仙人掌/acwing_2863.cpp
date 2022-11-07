#include <bits/stdc++.h>
using namespace std;

/*
先建圆方树，然后求lca, 还要维护所有点到圆方树root的距离
求出的lca如果是圆点，直接差分求距离即可
如果lca是方点，那么 需要特判一下，对环上的2条路径和取min
这里的路径和，用前缀和的思想维护
*/

const int N = 12010, M = N * 3; //原图双向边+圆方树单向边

int n, m, Q, new_n;
int h1[N], h2[N], e[M], w[M], ne[M], idx;
int dfn[N], low[N], cnt;
//s[]环的前缀和距离 stot[i] i所在环的边权和 fu[i] i的父节点 fw[i] i和父节点的边权
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
    add(h2, x, ++new_n, 0); //新图的点从n开始 每个环的根向方点连边 方点和圆点边权为0
    for (int k = y; k != x; k = fu[k]) {
        stot[k] = sum;
        add(h2, new_n, k, min(s[k], sum - s[k])); //方点向其他环上的点连边
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

void dfs_lca(int u, int father) { //求出所有点到整颗圆方树root的距离
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
        if (p <= n) printf("%d\n", d[a] + d[b] - d[p] * 2); //lca是圆点
        else {
            int da = d[a] - d[A], db = d[b] - d[B]; //环下边的2条路径长度
            int l = abs(s[A] - s[B]);
            int dm = min(l, stot[A] - l);
            printf("%d\n", da + dm + db);
        }
    }
    return 0;
}