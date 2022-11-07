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
此题实际上我感觉很难，要对最小割理解很到位.....

将每一个点的标号都用二进制来表示，两个点之间异或，只有1和0异或会对边权产生贡献
而且对于所有点，各个位之间都是互相独立的，对答案的贡献也是互不干扰的，所以可以对每一位分开计算
每一个二进制位都从新建图求最小割，一共31位。

为什么是最小割: 如果2个点之间有边，建图的时候就连边，边权为1，然后根据所有点当前二进制位是0还是1
将考虑当前二进制位的所有点分为2个集合，如果是1就向汇点连边，如果是0就向源点连边
意思就是，如果一个边的两个点假设当前二进制位都是1，那么就都向源点连边，那么这个边的两个点就在同一个集合中连
这个边也就是不会是这2个集合的割，也就不会对答案产生贡献，这就证明了只有处在不同集合的2个点之间的边才会对答案产生贡献
那么求一个最小的割，就用了“最少的边” 将集合分为2个部分，使得答案最小，这个过程中，会将没有初始标号的点进行自动“分类”
而不是人为去计算这些点的标号是多少，因为Dinic的算法过程会解决这一问题，也就是相当于求出了一个最佳的“对没有标号的点和已经标号的点进行分类”
决策，求出所有的位，然后加上二进制位的贡献，每一位都求最小割 ，也就是每一位的贡献都最小，那么最终的答案必然也就是最小的。
*/

#define x first
#define y second

const int N = 510, M = (3000 + N * 2) * 2, INF = 0x3f3f3f3f;

int n, m, k, S, T;
int h[N], e[M], ne[M], f[M], idx;
int q[N], d[N], cur[N];
int p[N]; //每个点的编号
pii edges[3010]; //存下所有的边

void add(int a, int b, int c1, int c2) { //c1正向边流量 c2反向边的流量
    e[idx] = b, f[idx] = c1, ne[idx] = h[a], h[a] = idx ++;
    e[idx] = a, f[idx] = c2, ne[idx] = h[b], h[b] = idx ++;
}

void build(int k) {
    memset(h, -1, sizeof h);
    idx = 0;
    for (int i = 0; i < m; i++) {
        int a = edges[i].x, b = edges[i].y;
        add(a, b, 1, 1);
    }

    for (int i = 1; i <= n; i++) //枚举所有点的第k位
        if (p[i] >= 0) { //当
            if (p[i] >> k & 1) add(i, T, INF, 0); //是1 就向汇点连边
            else add(S, i, INF, 0); //是0 源点向其连边
        }
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

ll dinic(int k) {
    build(k);
    int r = 0, flow;
    while (bfs()) while (flow = find(S, INF)) r += flow;
    return r;
}

int main() {
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);

    S = 0, T = n + 1;

    //读入所有的边
    for (int i = 0; i < m; i++) scanf("%d%d", &edges[i].x, &edges[i].y);

    scanf("%d", &k);
    memset(p, -1, sizeof p); //初始为-1 之后负数的点就是没有标号的
    while (k --) {
        int a, b;
        scanf("%d%d", &a, &b);
        p[a] = b;
    }

    ll res = 0;
    //31位 每一位求一次最大流 假设第k位进制位最大流是m, 对于答案的贡献就是m * 2 ^ k
    for (int i = 0; i <= 30; i++) res += dinic(i) << i;
    printf("%lld", res);

    return 0;
}