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
覆盖集：一个点集，可以覆盖所有的边，覆盖是指一个边至少有一个端点在这个点集中

二分图最小点权覆盖集 要求点权都是非负的，因为网络流不能解决负值流量
左边集合的所有点与虚拟源点S连边，边权为点权，右边集合的所有点和汇点T连边，边权为点权
中间所有点保持自己原来的连边，边权INF，这样的目的是最小割一定不会包含中间的边

最小割的边要么和S相连，要么和T相连，对于中间的一条“线段”的两个端点，这两个端点和S与T的连边
最小割肯定只会有一条，因为只需要一条就可以断掉路径。而被选的这条，对应线段的那个端点，就是覆盖当前“线段”的点
而边权等于点权，所以最小割的值就是最小点权覆盖集的点权和。
*/

/*
对于本题，建立二分图是关键
假设一条有向边是a --> b 那么可以花费代价a-删去这条边，也可以花费代价b+删去这条
所以所有+号的点是一个点集，-号是一个点集，然后b+向a-连边，边权INF，这样就是二分图的最小点权覆盖问题
注意建图是一个点只会在图中最多出现2次，既有入边也有出边，那么就会在左右边都出现这个点
这个点的所有出边或者所有入边都在二分图中间显现出来，注意题意：一次删掉所有的出边或者入边，但是这个点没有被删掉
可以一次删掉出边，接着删掉入边，一个点是可以被操作2次的
然后求最小割就是点权和 答案

输出操作方案:从虚拟源点S出发，沿容量大于0的边走，所有能到的点是一个割集，到不了的是另外一个割集
假设2个割集是S和T，那么只考虑S到T的有向边就可以了，因为建图是双向建边
遍历所有的边，如果一个边是割边，和S连通但是和T不连通，那么就是+号操作, 同样和T连通和S不连通就是-号操作
*/

const int N = 210, M = (N + 5010) * 2 + 10, INF = 0x3f3f3f3f;

int n, m, S, T;
int h[N], e[M], f[M], ne[M], idx;
int q[N], d[N], cur[N];
bool st[N];

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
    for (int i = h[u]; i != -1; i = ne[i])
        if (f[i] && !st[e[i]])
            dfs(e[i]);
}

int main() {
    scanf("%d%d", &n, &m);
    //左边+号点是1-n, 右边-号点是n+1到2n
    S = 0, T = n * 2 + 1;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; i++) { //+号点
        int w;
        scanf("%d", &w);
        add(S, i, w);
    }

    for (int i = 1; i <= n; i++) { //-号点
        int w;
        scanf("%d", &w);
        add(n + i, T, w);
    }

    while (m --) {
        int a, b;
        scanf("%d%d", &a, &b);
        add(b, n + a, INF); //从左边b+向右边a-连边
    }

    printf("%d\n", dinic());

    //方案
    dfs(S);

    //统计操作数量
    int count = 0;
    for (int i = 0; i < idx; i += 2) {
        int a = e[i ^ 1]; //起点 就是反向边的终点
        int b = e[i]; //终点

        if (st[a] && !st[b]) //只能搜到一个端点，那就是一条割边
            count++;
    }

    printf("%d\n", count);

    //所有+号操作
    for (int i = 0; i < idx; i += 2) {
        int a = e[i ^ 1], b = e[i];
        if (st[a] && !st[b]) {
            if (a == S) printf("%d +\n", b); //该边的起点是S同时是割边，那么就是加号操作
        }
    }
    //-号操作
    for (int i = 0; i < idx; i += 2) {
        int a = e[i ^ 1], b = e[i];
        if (st[a] && !st[b]) {
            if (b == T) printf("%d -\n", a - n); //该边的终点是S同时是割边，那么就是减号操作
        }
    }
}
