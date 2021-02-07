#include <bits/stdc++.h>
using namespace std;

/*
点分治模板题 求出路径长度<=k的路径个数
注意，不一定为二叉树，多叉树同样可以求
每次求出重心为root然后递归子树，接着删掉重心 复杂度O(N*(logN)^2)

三种路径：
1.路径两个端点都在同一颗子树中
2.两个端点在不同的2棵子树中
3.一个端点恰好是重心，另外一个端点在子树中

第一种路径直接递归子树即可，第二种是求出所有子树到重心的距离，然后
双指针匹配求出数量，同时减去2个端点都在同一颗子树，这种路径有一个到lca重复的边，不符合“路径” 要减掉 这就是容斥的思路
第三种就直接每次求出一颗子树到重心的路径长度之后遍历一次加上即可
*/

const int N = 10010, M = N * 2; //无向边

int n, m ; //m就是k
int h[N], e[M], w[M], ne[M], idx;
bool st[N];
int p[N], q[N]; //p[]是当前递归的所有子树的所有点到重心的距离 q保存所有子到重心的距离

void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

int get_size(int u, int fa) { //求当前子树大小
    if (st[u]) return 0;
    int res = 1;
    for (int i = h[u]; i != -1; i = ne[i])
        if (e[i] != fa)
            res += get_size(e[i], u);
    return res;
}

//此处并不是要求出重心，而且求出符合复杂度的一个点做为重心即可
int get_wc(int u, int fa, int tot, int &wc) { //返回子树大小 重心存在wc中
    //tot是所有子树+重心的大小
    if (st[u]) return 0;
    int sum = 1, ms = 0; //sum是u的所有子树+u的大小，ms保存删掉u后的最大子树大小
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (j == fa) continue;
        int t = get_wc(j, u,  tot, wc);
        ms = max(ms, t); //更新最大子树
        sum += t;
    }
    ms = max(ms, tot - sum); //还要和u的父亲树来比较大小
    if (ms <= tot >> 1) wc = u;
    return sum;
}

void get_dist(int u, int fa, int dist, int &qt) { //求出u的子树所有节点到u的距离
    if (st[u]) return;
    q[qt++] = dist;
    for (int i = h[u]; i != -1; i = ne[i])
        if (e[i] != fa)
            get_dist(e[i], u, dist + w[i], qt);
}

int get(int a[], int k) { //所有的路径在a[]中，双指针求出符合的路径条数
    sort(a, a + k);
    int res = 0;
    for (int i = k - 1, j = -1; i >= 0 ; i--) {
        while (j + 1 < i && a[j + 1] + a[i] <= m)j ++;
        j = min(j, i - 1);
        res += j + 1;
    }
    return res;
}

int calc(int u) {
    if (st[u]) return 0; //u已经被删掉
    int res = 0;
    get_wc(u, -1, get_size(u, -1), u); //得到当前树的重心保存在u
    st[u] = true; //删除重心

    int pt = 0; //p[]下标
    for (int i = h[u]; i != -1; i = ne[i]) { //遍历u的每个子树
        int j = e[i], qt = 0; //qt是q[]下标
        get_dist(j, -1, w[i], qt);
        res -= get(q, qt); //减去在同一个子树中的2个点的路径数量 这些都不是“路径” 不合法
        for (int k = 0; k < qt; k++) { //加上直接到重心的距离就<=k的点
            if (q[k] <= m) res ++;
            p[pt++] = q[k];
        }
    }
    res += get(p, pt);

    //递归处理子树
    for (int i = h[u]; i != -1; i = ne[i])
        res += calc(e[i]);
    return res;
}

int main() {
    while (scanf("%d%d", &n, &m), n || m) {
        memset(st, 0, sizeof st);
        memset(h, -1, sizeof h);
        idx = 0;

        for (int i = 0; i < n - 1; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            add(a, b, c), add(b, a, c);
        }
        printf("%d\n", calc(0));
    }
    return 0;
}