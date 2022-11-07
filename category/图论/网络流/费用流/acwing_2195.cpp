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
本质上和K取方格问题没有区别，只不过是多源汇，建立虚拟源点S向所有起点连边，容量为该点初始的机器人数量，费用0
所有终点向虚拟汇点T连边，容量为该点的机器人数量，费用0
由于费用都在边上，所以不需要拆点
同样每2个点之间连2条边，一条容量1费用c，另外一条容量INF费用0
最后求一次最大费用即可
*/

const int N = 260, M = 2000, INF = 0x3f3f3f3f;

int n, m, S, T; // m + 1行 n + 1 列

int h[N], e[M], ne[M], w[M], f[M], idx;
int q[N], d[N], pre[N], incf[N];
bool st[N];

int get(int x, int y) {
    return x * (m + 1) + y; //对于没有拆点的get函数，一般都是x * 行数 + y
}

void add(int a, int b, int c, int d) {
    e[idx] = b, f[idx] = c, w[idx] = d, ne[idx] = h[a], h[a] = idx ++;
    e[idx] = a, f[idx] = 0, w[idx] = -d, ne[idx] = h[b], h[b] = idx ++;
}

bool spfa() {
    int hh = 0, tt = 1;
    memset(d, 0xcf, sizeof d); //求最大费用
    memset(incf, 0, sizeof incf);
    q[0] = S, d[S] = 0, incf[S] = INF;
    while (hh != tt) {
        int t = q[hh++];
        if (hh == N) hh = 0;
        st[t] = false;

        for (int i = h[t]; i != -1; i = ne[i]) {
            int ver = e[i];
            if (f[i] && d[ver] < d[t] + w[i]) {
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

int EK() {
    int cost = 0;
    while (spfa()) {
        int t = incf[T]; //当前找到的新的增广路的流量
        cost += t * d[T];
        for (int i = T; i != S; i = e[pre[i] ^ 1]) {
            f[pre[i]] -= t;
            f[pre[i] ^ 1] += t;
        }
    }
    return cost; //返回最小费用
}

int main() {
    int A, B; //起点和终点数量
    scanf("%d%d%d%d", &A, &B, &n, &m);
    S = (n + 1) * (m + 1), T = S + 1;
    memset(h, - 1, sizeof h);
    for (int i = 0; i < n + 1; i ++) //所有列的边
        for (int j = 0; j < m; j++) {
            int c;
            scanf("%d", &c);
            add(get(i, j), get(i, j + 1), 1, c); //连2条边
            add(get(i, j), get(i, j + 1), INF, 0);
        }

    for (int i = 0; i < m + 1; i ++)
        for (int j = 0; j < n; j++) {
            int c;
            scanf("%d", &c);
            add(get(j, i), get(j + 1, i), 1, c);
            add(get(j, i), get(j + 1, i), INF, 0);
        }

    while (A --) {
        int k, x, y;
        scanf("%d%d%d", &k, &x, &y);
        add(S, get(x, y), k, 0);
    }

    while (B --) {
        int r, x, y;
        scanf("%d%d%d", &r, &x, &y);
        add(get(x, y), T, r, 0);
    }

    printf("%d\n", EK());

    return 0;
}