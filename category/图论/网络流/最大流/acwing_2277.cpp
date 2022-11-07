#include <bits/stdc++.h>
using namespace std;



/*
最大流判定：

题意:给定一个无向图，找出T条没有公共边的从1~N的路径，且要让所有路径中最长的边尽可能短
输出这个最长的边权。

做法: 二分最长的边，对于每个二分的状态，大于这个值的所有边都从图中删掉，就是只用边权小于当前二分值的边
剩余问题就转换为：当前图中是否存在T条没有公共边的路径，且都能从起点走到终点。
对于这个转换之后的问题，解决方法是：当前图的所有边权都是1，求一遍最大流，如果最大流F>=T，那么符合，继续二分即可。
因为每条边的边权都是1, 也就是每条边只能走一次, 从源点流向汇点的一条流流量为1的流就是一个路径，和证明欧拉路径有共同思路。


为什么要求最大流：贪心的思维，因为我们要尽可能求出T条，而从源点S流出的一条边就是一条路径的起点 ，那么最多的路径也就对应了最大流了。
*/

//点数边数小于10W，一般可以考虑网络流的Dinic
const int N = 210, M = 80010, INF = 0x3f3f3f3f;

int n, m, K;   //K是往返的次数
int h[N], e[M], f[M], w[M], ne[M], idx; //w是边权长度
int q[N], d[N], cur[N], S, T;

void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
    e[idx] = a, w[idx] = c, ne[idx] = h[b], h[b] = idx ++;
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


bool check(int mid) {
    //长度大于mid的边全部删掉
    for (int i = 0; i < idx; i++)
        if (w[i] > mid) f[i] = 0; //容量设为0就是删边
        else f[i] = 1;
    return dinic() >= K;
}

int main() {
    scanf("%d%d%d", &n , &m, &K);
    S = 1, T = n;  //这里的T是汇点 不要和题目中的T混淆

    memset(h, - 1, sizeof h);
    while (m --) {
        int a, b, c;
        scanf("%d%d%d", &a, &b , &c);
        add(a, b, c); //流量在后边算 这里加的是边权
    }

    //二分边权
    int l = 1, r = 1e6;
    while (l < r) {
        int mid = l + r >> 1;
        if (check(mid)) r = mid; //符合就二分更小的边权
        else l = mid + 1;
    }

    printf("%d\n", r);

    return 0;
}
