#include <bits/stdc++.h>
using namespace std;

/*
求出每个点作为最高点 向下的最长路径和次长路径 加起来就是经过该点的最长路径 求出所有的路径来更新答案

建立圆方树之后，最高点分情况讨论，设最长路径d1 次长路径d2:
1.最高点如果是圆点，直接ans = max(ans, d1 + d2)
2.如果是方点，这里要注意不一定这个路径经过环的根，也许只是环上的一段劣弧
由于边权都是1，对于环上任意2点 x,y， 设f[i]表示点i向下的最长路径 那么经过xy的这条最长路径
长度为f[x] + f[y] + x - y, 这里的xy都是环上加点的下标 所以可以直接用差计算这段劣弧的长度

枚举所有的xy点对是O(n^2)的不可取，需要用到单调队列优化，也就是滑动窗口
对于一个x，求出一个向后长度为size/2的一段里面的y，使得f[x] + f[y] + x - y 最小，size是环的长度
公式改为 f[x] + x + f[y] - y; //将f[x] + x看作整体即可
*/

const int N = 100010, M = N * 3, INF = 0x3f3f3f3f;

int n, m, new_n;
int h1[N], h2[N], e[M], w[M], ne[M], idx;
int dfn[N], low[N], cnt;
int s[N], stot[N], fu[N], fw[N];
int d[N], f[N], q[N]; //d单调队列 q单调队列下标 f存该点到叶子节点的最长距离
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
            if (dfn[u] < low[j]) add(h2, u, j, w[i]);  //桥 连边
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
    int d1 = 0, d2 = 0; //以u为最高点 向下的最长距离和次长距离
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
        for (int i = 0; i < sz; i++) d[sz + i] = d[i]; //环复制一遍 展开为链

        int hh = 0, tt = -1;
        for (int i = 0; i < sz * 2; i ++) { //固定i 滑动窗口来更新
            if (hh <= tt && i - q[hh] > sz / 2) hh++; //队列元素小于环长度一半 保证是劣弧
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