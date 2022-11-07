#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
typedef vector<int> vi;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
mt19937 mrand(random_device{}());
const ll mod = 1000000007;
int rnd(int x) { return mrand() % x;}
ll mulmod(ll a, ll b) {ll res = 0; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = (res + a) % mod; a = 2 * a % mod;} return res;}
ll powmod(ll a, ll b) {ll res = 1; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = res * a % mod; a = a * a % mod;} return res;}
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a;}
//head

/*
最大流关键边：
伊基是一个小国 – 凤凰国的国王。
凤凰国是如此之小，以至于只有一个城市负责日常商品的生产，并使用公路网将商品运送到首都。
伊基发现本国最大的问题在于运输速度太慢了。
因为伊基以前是 ACM/ICPC 的参赛者，他意识到这其实是一个最大流问题。
他编写了一个最大流程序，并计算出了当前运输网络的最大运输能力。
他对运输速度的现状十分不满，并希望能够提高国家的运输能力。
提高运输能力的方法很简单，伊基将在运输网络中重建一些道路，以使这些道路具有更高的运输能力。
但是不幸的是，凤凰国的财力有限，道路建设经费只够重建一条道路。
伊基想要知道共有多少条道路可以纳入重建道路候选名单。
这些道路需要满足，将其重建后，国家的总运输能力能够增加。
输入格式
第一行包含 N 和 M，分别表示城市和道路的数量。
接下来 M 行，每行包含三个整数 a,b,c，表示存在一条道路从城市 a 通往城市 b，且运输能力为 c。
所有道路都是有方向的。
城市编号从 0 到 N−1。生产日常商品的城市为 0 号城市，首都为 N−1 号城市。
输出格式
输出一个整数 K，表示存在 K 条道路，对其中每条道路进行重建都会增加运输网络的运输能力。
数据范围
1<=N<=500,
1<=M<=5000,
0<=a,b<=N,
0<=c<=100
输入样例：
2 1
0 1 1
输出样例：
1
*/

/*
意思就是增加一个边能让整个图的最大流变大，就是一个关键边，求所有关键边的数量
首先当前最大流的图里面，不满的边直接不用考虑，因为增大了容量依然还是流不满，被前边的容量小的边卡脖子了
所以只需要考虑满流的边即可

考虑简单路径 s-u-v-t 如果su和vt边都没有满流，只有uv满流，那么uv边就是关键边
所以从源点能到的边正向搜，从汇点开始反向搜能到的点，一个路径类比满足上述条件就记录答案
*/

const int N = 510, M = 5010 * 2, INF = 0x3f3f3f3f;
int n, m, S, T;
int h[N], e[M], ne[M];
int q[N], f[M], d[N], cur[N], idx;
bool vis_s[N], vis_t[N]; //能到S和能到T的点

void add(int a, int b, int c) {
    e[idx] = b, f[idx] = c, ne[idx] = h[a], h[a] = idx ++;
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
    while (bfs()) while (flow = find(S, INF)) r += flow;
    return r;
}

void dfs(int u, bool st[], int t) {
    st[u] = true; //标记已经走过
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = i ^ t; //i^t 作用是从S搜是正向边 从T搜是反向边
        int ver = e[i];
        if (f[j] && !st[ver]) //当前邻边没有满流并且没有被搜过
            dfs(ver, st, t);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    S = 0, T = n - 1;
    memset(h, -1, sizeof h);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c);
    }

    dinic();
    dfs(S, vis_s, 0); //不需要反向边
    dfs(T, vis_t, 1); //从汇点反向搜需要用到反向边 因为汇点开始走的边都是反向边，而关键边是正向边

    int res = 0;
    for (int i = 0; i < m * 2; i += 2)
        //一个边是满流并且起点能到S，终点能到T，就是一条关键边
        if (!f[i] && vis_s[e[i ^ 1]] && vis_t[e[i]]) //!f[i]就是满流，此时f是残留网络的流量
            res++;

    printf("%d\n", res);

    return 0;
}