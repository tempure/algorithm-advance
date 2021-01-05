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
最小割/拆点：

每一个不连通图的状态，都意味着至少有一个点对不能互相到达，那么所有不能互相到达的点对的状态，肯定包含了所有不连通图的状态
这也证明了此题可以转换为最小割求解。

枚举所有的点对作为ST，每个点拆点，然后就将去除点转换为去除边
拆点内部的边权为1，其余所有边权都是INF
由于是无向图，拆点的出边入边之间也要连边，边权同样INF
这样建图的目的在于，最小割只会在边权为1的边中产生，也就是只会在拆点的边中产生
而且这种建图的去除“边”和题目的去除“点”是等价的，因为将一个拆点的边和其两端的出入点看作一个整体
去除这个点就等价于去除这个整体，也就相当于去除这个拆点的边，让图不连通。

最后所有的ST点对求出的最小割取min即可。
*/

const int N = 110, M = 5210, INF = 0x3f3f3f3f;

int n, m, S, T;
int h[N], e[M], ne[M], f[M], idx;
int q[N], d[N], cur[N];

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
    while (cin >> n >> m) {
        memset(h, -1, sizeof h);
        idx = 0;
        for (int i = 0; i < n; i++) add(i, n + i, 1); //拆点内部的边
        while (m --) {
            int a, b;
            scanf(" (%d,%d)", &a, &b);
            add(n + a, b, INF); //a出->b入 双向边
            add(n + b, a, INF); //b出->a入
        }
        int res = n; //注意n初始最大就是选所有点
        //因为如果所有ST对中，初始都有一条INF的边，那么就无解，求出的最小割大于等于INF, 此时直接输出n就是res
        for (int i = 0; i < n; i++) //枚举S，T
            for (int j = 0; j < i; j++) {
                S = n + i; //源点是i的出点
                T = j; //汇点是j的入点
                for (int k = 0; k < idx; k += 2) { //枚举每一对ST都还原网络
                    f[k] += f[k ^ 1];
                    f[k ^ 1] = 0;
                }
                res = min(res, dinic());
            }
        printf("%d\n", res);
    }
    return 0;
}