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
建图技巧：
将所有顾客建点，设置虚拟源点和虚拟汇点
对于每个顾客，枚举所有他的钥匙的猪舍，如果一个猪舍是第一次打开，那么就从S向这个顾客连边，边权就是猪舍的猪的个数
如果不是第一次打开，那么就从上一次打开这个猪舍的人向当前顾客连边，容量INF
意思就是猪可以作为顾客之间流动的货币，有向边保证了流动的有序性
最后每个顾客都给汇点T连边，边权为其想买的猪的数量
求最大流就是猪场可以卖出的猪的最大数量
*/

const int N = 110, M = (1e5 + 110) * 2, INF = 0x3f3f3f3f;

int n, m, S, T;
int h[N], e[M], ne[M], f[M], idx;
int q[N], d[N], cur[N];
int w[1010]; //每个猪舍猪的数量
int last[1010]; //每个猪舍上一次开是哪个人


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
    scanf("%d%d", &m, &n);
    S = 0, T = n + 1;
    memset(h, -1, sizeof h);

    for (int i = 1; i <= m; i++) scanf("%d", &w[i]);
    for (int i = 1; i <= n; i++) {
        int a, b;
        scanf("%d", &a);
        while (a --) { //a把钥匙
            int id;
            scanf("%d", &id);
            if (!last[id]) add(S, i, w[id]); //第一次打开猪舍，那么就源点向顾客连边权
            else add(last[id], i, INF); //上一个人向当前顾客连INF
            last[id] = i;  //更新当前猪舍的最后一个被打开的人是谁
        }
        scanf("%d", &b);
        add(i, T, b);
    }
    printf("%d\n", dinic());

    return 0;
}
