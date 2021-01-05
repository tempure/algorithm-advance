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
二分图最大权独立集问题：
容易发现，对于一个点能攻击到的点，和该点的横坐标差值为1，纵坐标差值为2
所以横纵坐标之和的奇偶性肯定不同，奇数点为一个集合，偶数点为一个集合，就是二分图的模型。
题目求的就是互不攻击的骑士个数，也就是最大独立集。

虚拟源点S向奇数点连边，边权为1，偶数点向汇点T连边，边权为1，中间每个点向其周围的8个点连边，边权INF
连边的时候特判一下不能放的位置即可。
答案就是总点权和减去最大流。
*/

const int N = 40010, M = 400010, INF = 0x3f3f3f3f;

int n, m, S, T;
int h[N], e[M], f[M], ne[M], idx;
int q[N],  d[N], cur[N];
bool g[210][210]; //标记合法位置

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


int get(int x, int y) { //根据位置返回点的idx
    return (x - 1) * n + y;
}

int main() {
    scanf("%d%d", &n, &m);
    S = 0, T = n * n + 1;
    memset(h, -1, sizeof h);

    while (m --) { //标记不合法的位置
        int x, y;
        scanf("%d%d", &x, &y);
        g[x][y] = true;
    }

    int dx[] = { -2, -1, 1, 2, 2, 1, -1, -2};
    int dy[] = {1, 2, 2, 1, -1, -2, -2, -1};

    int tot = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j ++) {
            if (g[i][j]) continue;
            if (i + j & 1) {
                add(S, get(i, j), 1);
                for (int k = 0; k < 8; k++) {
                    int x = i + dx[k], y = j + dy[k];
                    if (x >= 1 && x <= n && y >= 1 && y <= n && !g[x][y])
                        add(get(i, j), get(x, y), INF);
                }
            }
            else add(get(i, j), T, 1);
            tot ++;
        }
    printf("%d\n", tot - dinic());

    return 0;
}
