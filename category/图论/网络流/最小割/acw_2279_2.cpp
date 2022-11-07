#include <bits/stdc++.h>
using namespace std;

//2021.9.7=====================new content==========================

/*
细节补充：
- 双向边：在网络流中的双向边一定要注意建图的时候，反向边流量和正向边都是初始容量
- 贪心：删掉了最小割的边之后，转换后的图中，可能是会有负权值的边的，选上一定会让答案更小
- 公式转换中C就是割集的大小，就是边的数量，所以才可以转换


WHY？- 二分的最大边界，sigma(we)/C, 这个函数的最大值感觉不太好确定啊，C=1，W是最大边权
的话，不一定是最大值？？？？ 好像一定是最大值耶！！！

考虑分母增加1，但是分子增加的只能是<=最大边权的值，所以一定不会更优，所以最大值一定就是最大边权
*/

//============================old content

/*
01分数规划 浮点数最大流 二分
考虑分数规划。存在一个平均值不大于xx的割集等价于：
∃C,∑e∈C w(e) / |C| <= x
⇒∃C,∑e∈C (w(e)−x) <= 0
故存在一个平均值不大于x的割集⇔将边权全部减少x后，最小割权值不超过0
二分答案+最小割即可
注意图中会出现负权边，没法直接最大流，但最小割中必然包含所有负权边，提前选上即可。
所有负权边先加上，然后剩下的就是正边，然后求最小割即可
*/


const int N = 100, M = 810, INF = 0x3f3f3f3f;
const double eps = 1e-8; //二分eps

int n, m, S, T;
int h[N], e[M], ne[M], w[M], idx;
double f[M];  //二分浮点数 λ  边的流量是小数
int q[N], d[N], cur[N];

void add(int a, int b, int c) {
    // 建双向边
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
    e[idx] = a, w[idx] = c; ne[idx] = h[b], h[b] = idx ++;
}

bool bfs() {
    int hh = 0, tt = 0;
    memset(d, -1, sizeof d);

    q[0] = S, d[S] = 0, cur[S] = h[S];
    while (hh <= tt) {
        int t = q[hh++];
        for (int i = h[t]; i != -1; i = ne[i]) {
            int ver = e[i];
            if (d[ver] == -1 && f[i] > 0) {
                d[ver] = d[t] + 1;
                cur[ver] = h[ver];
                if (ver == T) return true;
                q[++tt] = ver;
            }
        }
    }
    return false;
}

double find(int u, double limit) {
    if (u == T) return limit;
    double flow = 0;
    for (int i = cur[u]; i != -1 && flow < limit; i = ne[i]) {
        cur[u] = i;
        int ver = e[i];
        if (d[ver] == d[u] + 1 && f[i] > 0) {
            double t = find(ver, min(f[i], limit -  flow));
            if (t < eps) d[ver] = -1;
            f[i] -= t, f[i ^ 1] += t, flow += t;
        }
    }
    return flow;
}

double dinic(double mid) { //mid就是λ 在dinic里面建图
    double res = 0;
    for (int i = 0; i < idx; i += 2)
        if (w[i] <= mid) { //此时的边权为负数 直接加上 然后删掉这条边
            res += w[i] - mid;
            f[i] = f[i ^ 1] = 0; //删掉负权边
        } else f[i] = f[i ^ 1] = w[i] - mid;

    double r = 0, flow;
    while (bfs()) while (flow = find(S, INF)) r += flow;
    return res + r;
}

int main() {
    scanf("%d%d%d%d", &n, &m, &S, &T);
    memset(h, -1, sizeof h);

    while (m --) {
        int a, b, c;
        scanf("%d%d%d", &a, &b , &c);
        add(a, b, c);
    }

    double l = 0, r = 1e7;  //二分答案 mid
    while (r - l > eps) {
        double mid = (l + r) / 2;
        if (dinic(mid) < 0) r = mid;
        else l = mid;
    }

    printf("%.2lf\n", r);

    return 0;
}