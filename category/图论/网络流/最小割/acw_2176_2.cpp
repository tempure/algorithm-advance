#include <bits/stdc++.h>
using namespace std;

/*2021 9.11 update

最大权闭合图输出答案，和二分图最小点权覆盖集注意区分：

最大权闭合图直接考虑一个简单的环模型，其中左半部分和S相连，边权为正，右半部分为负，和T相连
考虑一般的，负数总权值和绝对值小于正数总权值和，不然最大权就是0，直接不选就是最优。

此时的最小割就是右边负权值点和T相连的边，就是割边, 这些边权都是0，被榨干了
那必然此时左半部分和S连的边都不是0流量，中间的边流量都是INF

最大权闭合图的权值和 = 所有点总权值和 - 最小割

那么必然是要选上左边这些点的，要从流量非空的边开始DFS，同时也能搜到右边那些点，但是搜不到T

也可以解释为原来写的那个思路：

>最大权闭合图输出方案方法的原理:
>当选择一个正权点的收益 > 他所连接的负权点的消费时，源点连接这个正权点的边就不会满流
>因此从源点出发跑一个 dfs ，只走没有满流（残留网络还有流量）的边
>抵达的正权点都是要被选择的,同时所有被选择的正权点所连接的所有负权点也是要被选择的
>这样的一对正负点对的点权和为正，就会对闭合子图点权和产生正的贡献，贪心的思维。
*/


const int N = 110, M = 5210, INF = 0x3f3f3f3f;

int n, m, S, T;
int h[N], e[M], f[M], ne[M], idx;
int q[N], d[N], cur[N];
bool st[N]; //dfs 寻找方案

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

void dfs(int u) {
    st[u] = true;
    for (int i = h[u]; i != -1; i = ne[i]) {
        if (!st[e[i]] && f[i])
            dfs(e[i]);
    }
}

int main() {
    scanf("%d%d", &m, &n);
    S = 0, T = n + m + 1;
    memset(h, - 1, sizeof h);

    getchar(); //第一行最后的回车吞掉 要用sstream读一行 因为实验的仪器个数未知1

    int tot = 0; //所有收益和
    for (int i = 1; i <= m; i++) {
        int w, id;
        string line;
        getline(cin, line);

        stringstream ssin(line);
        ssin >> w;
        add(S, i, w);
        while (ssin >> id) add(i, m + id, INF); //每个实验向其所需要的仪器连边
        tot += w;
    }

    for (int i = 1; i <= n; i++) { //所有仪器向T连边
        int p;
        scanf("%d", &p);
        add(m + i, T, p);
    }

    int res = dinic();
    dfs(S);

    for (int i = 1; i <= m; i++) //输出所有的实验
        if (st[i]) printf("%d ", i);

    puts("");

    for (int i = m + 1; i <= m + n; i++) //输出所有的仪器
        if (st[i]) printf("%d ", i -  m);

    puts("");

    //输出净收益
    printf("%d\n", tot - res);

    return 0;
}
