#include <bits/stdc++.h>
using namespace std;

/*
2021 9.4 update
注意饮料的编号，注释那里原来的版本少了个1
此类分配问题，如果不是二分图，可以直接考虑最大流求多分图匹配问题,此题就是三分图

考虑如果每个牛可以多进多出边，那么就不能满足题目的 “给每头奶牛分配一种食物和一种饮料” 条件，所以必须把牛的点拆开
拆点后注意编号问题，以及数组的点数计算问题
*/


//==============================old content=====================================================

/*
最大流拆点求解三分图匹配：

将食物，牛，饮料都分别看成一竖排，再加上源点S和汇点T
源点S向所有食物连边，所有饮料向T连边，每个牛匹配的食物向牛连边
每个牛向其匹配的饮料向后连边

这样看起来就有点像Dinic求二分图匹配了，但是却不能直接在这个图上求最大流得出匹配数量
因为对于二分图匹配，每个点都是“多进单出”或者“单进多出”，也就是满足了每个点只会和一个点匹配
但是此题中间的牛对应的点会多进多出，所以不能直接Dinic

拆点:将每个牛对应的点拆分为入点和出点，入点连接左边所有该牛匹配的食物，出点连接右边所有匹配的出点的食物
入点和出点之间连接一条边权为1的边，这样对于每个牛而言，就只能匹配一种食物和饮料了
*/

const int N = 410, M = 41000, INF = 0x3f3f3f3f;
int n, F, D, S, T;
int h[N], e[M], ne[M], f[M], idx;
int q[N], d[N], cur[N];

//建图点的顺序：所有牛的入点1~n，所有牛的出点n + 1 ~ 2n, 食物2n + 1~ 2n + F, 饮料2n + F + 1 ~ 2n + F  + 1 + D


void add(int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], f[idx] = c, h[a] = idx ++;
    e[idx] = a, f[idx] = 0, ne[idx] = h[b], h[b] = idx ++;
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


int main() {
    scanf("%d%d%d", &n, &F, &D);
    S = 0, T = n * 2 + F + D + 1;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= F; i++) add(S, n * 2 + i, 1); //源点向所有食物连边
    for (int i = 1; i <= D; i++) add(2 * n + F + i, T, 1); //饮料向汇点连边
    for (int i = 1; i <= n; i++) {
        add(i, n + i, 1); //牛的拆点后的入点到出点连边权为1的边
        int a, b, t;
        scanf("%d%d", &a, &b);
        while (a --) {
            scanf("%d", &t);
            add(n * 2 + t, i, 1); //牛匹配的食物向牛的入点连边
        }
        while (b --) {
            scanf("%d", &t);
            add(i + n, n * 2 + F + t, 1); //牛的出点向牛匹配的饮料连边
        }
    }
    printf("%d\n", dinic());

    return 0;
}