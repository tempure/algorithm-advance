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


const int N = 1010, M = 250010 + 1010;
const int INF = 0x3f3f3f3f;

int n, S, T;
int h[N], e[M], f[M], ne[M], idx;
int q[N], d[N], cur[N];
int g[N], w[N];  //g是 dp的状态数组

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
    scanf("%d", &n);
    S = 0, T = n * 2 + 1;

    memset(h, - 1, sizeof h);
    for (int i = 1; i <= n; i++) scanf("%d", &w[i]);
    int s = 0;  //最大值
    for (int i = 1; i <= n; i++) {
        add(i, i + n, 1); //入点出点连边
        g[i] = 1;
        for (int j = 1; j < i; j++)
            if (w[j] <= w[i])
                g[i] = max(g[i], g[j] + 1);

        for (int j = 1; j < i; j++) //拆点
            if (w[j] <= w[i] && g[j] + 1 == g[i])
                add(n + j, i, 1);

        s = max(s, g[i]);
        //1 ~n 入点 n + 1 ~ 2n 出点
        if (g[i] == 1) add(S, i, 1);
        // else if (g[i] == s) add(n + i, T, 1);
    }

    for (int i = 1; i <= n; i++)
        if (g[i] == s) add(n + i, T, 1);

    printf("%d\n", s);

    if (s == 1) printf("%d\n%d\n", n, n); //第三个问题特判只有一个元素的情况
    //因为 如果只有一个元素，那么图中的所有点解除限制之后边权都是INF
    else {
        int res = dinic();
        printf("%d\n", res);

        //第三个问题，解除第一个点和第n个点的限制
        for (int i = 0; i < idx; i += 2) {
            int a = e[i ^ 1], b = e[i];
            if (a == S && b == 1) f[i] = INF;
            else if (a == 1 && b == n + 1) f[i] = INF;//第一个点的入点和出点解除
            else if (a == n && b == n + n) f[i] = INF; //第n个点的入点和出点解除
            else if (a == n + n && b == T) f[i] = INF;
        }
        printf("%d\n", res + dinic());
    }

    return 0;
}