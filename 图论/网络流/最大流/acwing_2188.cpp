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
无源汇上下界可行流：假设每条边流量上界是cu下界是cr
建立新图 流量下界是0，新的上界是cu-cr，边上的流量也减去cr 这样就转化为只有上界的可行流
但是对于一个点，出边的流量减去和入边的流量减去的不是同一个值，就不一定满足流量守恒
所以建立源点S，对于每个点，根据流入流出总量向汇点和源点连边，所有出边流量和所有入边流量求和对比，采取多退少补
用c入和c出代表新图中该点相比原来的守恒情况，“少进来”的流量和“少出去的流量”，如果c入>c出，也就是少进来的更多
那么就要用源点来补充，反之就是少出去的更多，需要向汇点连边流出多余的，代码维护A[]记录每个点的c入减去c出的值 以正负来决定向源点还是汇点连边
这样就满足了流量守恒，可以用常规的下界为0的最大流解决。

定理:新图的一个最大流，对应原图的一个可行流。因为连边的时候，采取了多退少补的策略
而且源点向一个点连的边，既是容量也是流量，而且这个少补一定要满足，所以源点的出边必定满流
所以只有当新图是最大流，对应的才是原图的一个上下界限制的可行流。
*/

const int N = 210, M = (10200 + N) * 2, INF = 0x3f3f3f3f;

int n, m, S, T;
int h[N], e[M], ne[M], idx, f[M], l[M]; //l记录下界
int q[N], d[N], cur[N];
int A[N]; //记录每个点的入边流量和和出边流量和的差（正负)

void add(int a, int b, int c, int d) {
    e[idx] = b, f[idx] = d - c, l[idx] = c,  ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, f[idx] = 0, ne[idx] = h[b], h[b] = idx++; //反向边下界用不到
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
    scanf("%d%d", &n, &m);
    S = 0, T = n + 1; //随便两个范围之外的点

    memset(h, -1, sizeof h);
    for (int i = 0; i < m; i++) {
        int a, b, c, d;
        scanf("%d%d%d%d", &a, &b, &c, &d);
        add(a, b, c, d);
        A[a] -= c, A[b] += c; //同时更新该点的出入流量总和情况 用于后边处理
    }

    int tot = 0; //源点到所有点的连边的流量之和 判断满流
    for (int i = 1; i <= n; i++)
        if (A[i] > 0) add(S, i, 0, A[i]), tot += A[i]; //少流入的更多，源点补充流出
        else if (A[i] < 0) add(i, T, 0, -A[i]); //少流出的更多 多余的向汇点流去

    if (dinic() != tot) puts("NO");
    else {
        puts("YES");
        for (int i = 0; i < m * 2; i += 2)
            printf("%d\n", f[i ^ 1] + l[i]); //最后要加上减去的下界 此时的f记录的是残留图
        //原图中的流量 是此时残留图的反向边的权值
    }

    return 0;
}