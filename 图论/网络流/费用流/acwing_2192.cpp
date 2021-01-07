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
S向所有残酷连边，容量为仓库货物数量，费用为0
所有商店向T连边，容量为需要出售的数量，费用为0
每个仓库向所有商店连边，容量为INF，费用为c

费用 = 流量 * 路径长度
注意:由于建图时候路径长度就是单位费用，所以费用本质上就是流量(货物数量) * 单位费用
每次spfa求最短路，就是在求最长的单位费用是哪条路径
S和所有仓库，以及所有商店和T之间的路径长度，也就是费用w[]都是0，所以这2段路程不会影响到最短路

求最大费用的方法：将w[]数组元素取负，再求最短路，求出的就是负值的最长路
最后取反输出答案即可
*/

const int N = 160, M = 5150 * 2 + 10, INF = 0x3f3f3f3f;

int n, m, S, T;
int h[N], e[M], ne[M], f[M], w[M], idx;
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
    scanf("%d%d", &m, &n);
    S = 0, T = m + n + 1;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= m; i++) {
        int a;
        scanf("%d", &a);
        add(S, i, a, 0);
    }

    for (int i = 1; i <=  n; i++) {
        int b;
        scanf("%d", &b);
        add(m + i, T, b, 0);
    }

    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++) {
            int c;
            scanf("%d", &c);
            add(i, m + j, INF, c);
        }

    int flow, cost;
    printf("%d\n", EK(flow, cost));

    //取反w[] 以及恢复原图
    for (int i = 0; i < idx; i += 2) {
        f[i] += f[i ^ 1], f[i ^ 1] = 0;
        w[i] = -w[i], w[i ^ 1] = - w[i ^ 1];
    }
    //最大费用
    printf("%d\n", -EK(flow, cost));


    return 0;
}