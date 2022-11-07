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
最小割最大权闭合图:
建立虚拟源点S和汇点T，如果点权为正就向源点S连边，边权为点权，如果点权为负就向汇点连边，但是边权依然为正数值大小等于点权
除了源汇点之外的所有点之间边权都是INF
此图的最大权闭合图权值和 = 所有权值为正的点权值和 - 最小割(最大流)

此定理的理解很直观，有很多角度都可以讲通。首先上述建图之后，所有闭合子图的流量都只能来源于源点S
此时图中的一个割集可以是所有与源点S连接的边，这个割集一定是一个割，同时也是最大流
因为闭合图可以简单理解为一个有“环”性质的图，注意这里的图说的是原图，没有加上源汇点和那些后加的边
也就是一个“内部流量循环”的图结构，而加上S，T以及边之后，这个“循环”的流量只能完全来自于S，全部流向T。

继续讨论这个环:如果环上正点权和大于负点权和的绝对值，那么最大流就是负权点的绝对值之和了，因为前面很大但是被后边的边卡脖子了
首先有最大闭合子图就是整个环，环的权值也等于正点权和减去负点权和的绝对值，也恰好就是正点权值和减去最大流。
反之如果正点的点权和小于负点权和的绝对值，那么最大流就是正点权和，此时最大闭合图答案就是0。

对于最大闭合子图，由定理可知显然最大闭合子图的点权值和不可能为负，因为最坏情况下就是空集，空集也是子图。
*/

/*
对于此题，所有中转站的点权都是-pi, 意思是建站需要花费pi，然后每个用户群向其需要的2个中转站连边，用户群的点权为+ci
代表收益ci，用户群和中转站之间的边权为INF, 可以发现此时就是一个闭合图，然后要求最大权闭合图，就求出了最大收益
此算法过程也在实际上在寻找应该包含那些“用户群”，因为算法求的是“闭合图”，而闭合图一定满足题目的用户群和中转站的关系。

另外，此题只要求用户连接2个中转站，即使连接很多中转站，也满足闭合图的性质，也可以用最大权闭合图求解。有点杀鸡用牛刀的意思。
此题的最优解法是最大密度子图，可以在复杂度上常数优化，少建边和点。

答案就是所有用户的点权之和减去最大流。
*/

const int N = (50000 + 5000 + 10), M = (50000 * 3 + 5000 + 10) * 2;
const int INF = 0x3f3f3f3f;

int n, m, S, T;
int h[N], ne[M], e[M], idx;
int q[N], f[M], d[N], cur[N];

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

/*
在代码中并不需要体现点权值的正负，只需要建立正权的边即可
*/

int main() {
    scanf("%d%d", &n, &m);
    S = 0, T = n + m + 1; //一共有n + m个点
    //用户是1到m  中转站是m + 1到m + n
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; i++) {
        int p;
        scanf("%d", &p);
        //花费，向汇点连边
        add(m + i, T, p);
    }

    int tot = 0; // 正数点的权值和

    for (int i = 1; i <= m; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(S, i, c); //S向用户连边 权值为收益
        add(i, m + a, INF); //用户向中转站连边 权值INF
        add(i, m + b, INF);
        tot += c;
    }

    printf("%d\n", tot - dinic());


    return 0;
}