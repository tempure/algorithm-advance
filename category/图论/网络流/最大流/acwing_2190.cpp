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
有源汇上下界最小流：
方法和有源汇上下流最大流一样，求完新图满流之后的s-t图残余流量，减去t到s的最大流即可
*/
const int N = 50010, M = (N + 125003) * 2;// 边数是点数+题目的边数 然后总体*2 因为新的S和T要向所有点连边维持流量守恒
const int INF = INT_MAX;
int n, m, S, T;
int h[N], e[M], ne[M], f[M]; //f是残留网络权值
int idx, q[N], d[N], cur[N], A[N]; //A是入边流量和减去出边流量和 cur当前弧优化

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
    int s, t; //题目给定的源点汇点 S T 为新加
    scanf("%d%d%d%d", &n, &m, &s, &t);
    memset(h, -1, sizeof h);
    S = 0, T = n + 1;
    while (m --) {
        int a, b, c, d;
        scanf("%d%d%d%d", &a, &b, &c, &d);
        add(a, b, d - c); //边权为上界减去下界
        A[a] -= c, A[b] += c;
    }

    int tot = 0;
    for (int i = 1; i <= n; i++)
        if (A[i] > 0) add(S, i, A[i]), tot += A[i];
        else if (A[i] < 0) add(i, T, -A[i]);
    add(t, s, INF); //加新边 构成无源汇图
    if (dinic() < tot) puts("No Solution"); //没有满流 无解
    else {
        int res = f[idx - 1]; //加上新加的边的反向边的残余流量 然后去掉
        S = t, T = s;//直接改变源汇点 就是相当于去掉了S T还有其余的边

        f[idx - 1] = f[idx - 2] = 0; //删去新加的边 新边是最后加的 idx就是最后的2个(正反向边)
        printf("%d\n", res - dinic()); //减去终点t到起点s最大流即可
    }
    return 0;
}
