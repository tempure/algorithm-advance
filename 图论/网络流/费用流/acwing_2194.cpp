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
负载均衡问题:
先求出所有货物的平均值，将所有仓库分为2类，货物大于平均值和和小于平均值的
S向所有大于平均值的仓库连边，容量为a[i] - 平均值，费用为0
每个点向左右2点连边，容量为INF， 费用为1，由于是环形 ，特判一下即可
所有小于平均值的仓库向T连边，容量为平均值 - a[i],费用为0
等于平均值的仓库不用处理
因为要满足所有边都是满流才能解决问题，满流一定是最大流，同时也是最小费用，所以问题就是求最小费用最大流

注意一点:在费用流问题中，无向边必须建2次，不像最大流建一次即可，最大流的流量是可以合并的，但是费用流不行
费用流的2条正向边可能一正一负，不能合并，2点之间，加上残留网络的边，必须要建4倍边
此题是有向图不用考虑这个问题
*/

const int N = 110, M = 6 * N + 10, INF = 0x3f3f3f3f;

int n, S, T;
int a[N]; //每个仓库的货物量
int h[N], e[M], f[M], w[M], ne[M], idx;
int q[N], d[N], pre[N], incf[N];
bool st[N];


void add(int a, int b, int c, int d) {
    e[idx] = b, f[idx] = c, w[idx] = d, ne[idx] = h[a], h[a] = idx ++;
    e[idx] = a, f[idx] = 0, w[idx] = -d, ne[idx] = h[b], h[b] = idx ++;
}

bool spfa() {
    int hh = 0, tt = 1;
    memset(d, 0x3f, sizeof d);
    memset(incf, 0, sizeof incf);
    q[0] = S, d[S] = 0, incf[S] = INF;
    while (hh != tt) {
        int t = q[hh++];
        if (hh == N) hh = 0;
        st[t] = false;

        for (int i = h[t]; i != -1; i = ne[i]) {
            int ver = e[i];
            if (f[i] && d[ver] > d[t] + w[i]) {
                d[ver] = d[t] + w[i];
                pre[ver] = i;
                incf[ver] = min(f[i], incf[t]);
                if (!st[ver]) {
                    q[tt++] = ver;
                    if (tt == N) tt = 0;
                    st[ver] = true;
                }
            }
        }
    }
    return incf[T] > 0; //如果大于0说明S可以走到T 不然就不连通
}

int EK(int & flow, int & cost) {
    flow = cost = 0;
    while (spfa()) {
        int t = incf[T]; //当前找到的新的增广路的流量
        flow += t, cost += t * d[T];
        for (int i = T; i != S; i = e[pre[i] ^ 1]) {
            f[pre[i]] -= t;
            f[pre[i] ^ 1] += t;
        }
    }

    return cost;
}

int main() {
    scanf("%d", &n);
    S = 0, T = n + 1;
    memset(h, -1, sizeof h);

    int tot = 0; //记录总量 求平均值

    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        tot += a[i];
        //向左右连边
        add(i, i < n ? i + 1 : 1, INF, 1); //如果是n号点 就向1号点连边
        add(i, i > 1 ? i - 1 : n, INF, 1); //如果是1号点 就向n号点连边
    }

    tot /= n;

    for (int i = 1; i <= n; i++)
        if (tot < a[i]) add(S, i, a[i] - tot, 0);
        else if (tot > a[i]) add(i, T, tot - a[i], 0);

    int flow, cost;
    printf("%d\n", EK(flow, cost));

    return 0;
}

