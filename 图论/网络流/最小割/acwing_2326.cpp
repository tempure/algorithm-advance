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
二分图最大权独立集 = 所有点权 - 最小点权覆盖集
一个定理：一个有向图中，独立集的补集肯定是覆盖集

分析此题，有2个性质，第一个是显然只能在偶数秒拿到宝石，因为偶数秒的时候，会把周围的清空，导致无论如何
走过去到奇数秒都不会有宝石。第二个性质是绝对不可能同时拿到2个相邻格子的宝石，这个根据第一个性质是显然的。

对于格子，显然是可以二染色的，所以可以转换为二分图模型。对于每个格子，向其相邻的所有格子连边，对于每条边
的2个端点，都只能取得一个点的宝石，最后所有选择的格子，这些格子构成一个独立集。

虚拟源点S向所有横纵坐标和为奇数的点连边，边权为点权，所有和为偶数的点向虚拟汇点连边，边权为点权，每个点向周围4个点连边，边权为INF。

一个误区：最后求出的最大独立集，是可能同时包含左边集合的点和右边集合的点，假设所有横纵坐标和为奇数的点染色，偶数的不染色
但是最后的答案可能同时选择染色的和不染色的，但是都保持一个原则，这些格子构成一个独立集，之间不会有边。
*/

const int N = 10010, M = 60010, INF = 0x3f3f3f3f;

int n, m, S, T;
int h[N], e[M], ne[M], f[M], idx;
int q[N], d[N], cur[N];

int get(int x, int y) {
    //横纵坐标都从1开始 返回该点累加加点过程中的编号
    return (x - 1) * m + y;
}

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
    scanf("%d%d", &n, &m);
    S = 0, T = n * m + 1;
    memset(h, -1, sizeof h);

    int tot = 0; //所有点权和
    int dx[] = { -1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};

    for (int i =  1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            int w;
            scanf("%d", &w);
            if (i + j & 1) { //横纵坐标和为奇数
                add(S, get(i, j), w);
                for (int k = 0; k < 4; k++) {
                    int x = i + dx[k], y = j + dy[k];
                    if (x >= 1 && x <= n && y >= 1 && y <= m)
                        add(get(i, j), get(x, y), INF); //相邻点连边

                    //细节：奇数点向所有周围的偶数点连边了，偶数就不需要重复连边了
                }
            } else add(get(i, j), T, w); //另外一个集合

            tot += w;
        }

    printf("%d\n", tot - dinic());

    return 0;
}