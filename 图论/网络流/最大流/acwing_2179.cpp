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

//圆桌问题 二分图多重匹配
//左边点集为每个单位的所有人 右边为每个桌子
//S向左边每个单位连接权值为单位的人数的边 T向右边连接是桌子的容纳人数
//这样建图 边初始就是网络的容量
//最大流等于总人数 就是一个可行的最大流 也就是可行方案


const int N = 430, M = (150 * 270 + N) * 2; //反向边
const int INF = 0x3f3f3f3f;

int n, m, S, T;
int h[N], ne[M], e[M], idx, f[M];
int q[N], d[N], cur[N];

void add(int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], f[idx] = c, h[a] = idx ++;
    e[idx] = a, ne[idx] = h[b], f[idx] = 0, h[b] = idx ++;
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
                d[ver] = d[t] + 1;
                cur[ver] = h[ver];
                if (ver == T) return true;
                q[++tt] = ver;
            }
        }
    }
    return false;
}

int find(int u, int limit) {
    if (u == T) return limit;
    int flow = 0;
    for (int i = cur[u]; i != -1 && flow < limit; i = ne[i]) {
        cur[u] = i;
        int ver = e[i];
        if (d[ver] == d[u] + 1 && f[i]) {
            int t = find(ver, min(f[i], limit - flow));
            if (!t) d[ver] = -1;
            f[i] -= t, f[i ^ 1] += t, flow += t;
        }
    }
    return flow;
}

int dinic() {
    int r = 0, flow;
    while (bfs()) while (flow = find(S, INF)) r += flow;
    return r;
}

int main() {
    scanf("%d%d", &m, &n);
    S = 0, T = m + n + 1; //源点和汇点
    memset(h, -1, sizeof h);

    //原点0 左边点集1-m 右边m+1-m+n 汇点m+n+1
    int tot = 0;
    for (int i = 1; i <= m; i++) {
        int c; scanf("%d", &c);
        add(S, i, c);
        tot += c; //总人数
    }
    for (int i = 1; i <= n; i++) {
        int c; scanf("%d", &c);
        add(m + i, T, c);
    }

    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            add(i, m + j, 1);

    if (dinic() != tot) puts("0");
    else {
        puts("1");
        for (int i = 1; i <= m; i++) {
            //遍历每个点对面匹配的点输出
            for (int j = h[i]; j != -1; j = ne[j])
                if (e[j] > m && e[j] <= m + n && !f[j]) //满流也就是匹配的边才会输出 残留图中是0
                    printf("%d ", e[j] - m);
            puts("");
        }
    }
}