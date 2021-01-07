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
S向第一行的所有点连边，容量为1，费用为0
最后有一行的点向汇点连边，容量为1，费用为0
规则1：拆点，点内部容量为1，费用为数字本身
规则2：放开点内部的边的限制容量为INF，最后一行向汇点容量也是INF
规则3：放开点和边的限制

只有点内部的拆点的边才有费用，其余边的费用全部是0
每次重新建图，跑最大费用流即可
S向第一行的点之间的边不能放开限制，因为第一行一个点只能用一次，也就是一个路径的开头唯一
*/

const int N = 1200, M = 4000, INF = 0x3f3f3f3f;

int n, m, S, T;
int h[N], e[M], f[M], w[M], ne[M], idx;
int q[N], d[N], pre[N], incf[N];
bool st[N];
int id[40][40], cost[40][40];


void add(int a, int b, int c, int d) {
    e[idx] = b, f[idx] = c, w[idx] = d, ne[idx] = h[a], h[a] = idx ++;
    e[idx] = a, f[idx] = 0, w[idx] = -d, ne[idx] = h[b], h[b] = idx ++;
}

//最长路版本spfa
bool spfa() {
    int hh = 0, tt = 1;
    memset(d, 0xcf, sizeof d);
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

//返回费用模板
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
    return cost; //返回最小费用
}

int main() {
    int cnt = 0;
    scanf("%d%d", &m, &n);
    S = ++cnt;
    T = ++cnt;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m + i - 1; j ++) {
            scanf("%d", &cost[i][j]);
            id[i][j] = ++cnt;
        }

    int flow, costs;

    //规则1 建图
    memset(h, - 1, sizeof h);
    idx = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m + i - 1; j ++) {
            add(id[i][j] * 2, id[i][j] * 2 + 1, 1, cost[i][j]); //出入点建边
            if (i == 1) add(S, id[i][j] * 2, 1, 0); //第一行与S建边
            if (i == n) add(id[i][j] * 2 + 1, T, 1, 0);
            if (i < n) { //向左右下建边
                add(id[i][j] * 2 + 1, id[i + 1][j] * 2, 1, 0);
                add(id[i][j] * 2 + 1, id[i + 1][j + 1] * 2, 1, 0);
            }
        }
    printf("%d\n", EK(flow, costs));

    //规则2 建图 放开点的限制
    memset(h, - 1, sizeof h);
    idx = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m + i - 1; j ++) {
            add(id[i][j] * 2, id[i][j] * 2 + 1, INF, cost[i][j]); //出入点建边
            if (i == 1) add(S, id[i][j] * 2, 1, 0); //第一行与S建边
            if (i == n) add(id[i][j] * 2 + 1, T, INF, 0);
            if (i < n) { //向左右下建边
                add(id[i][j] * 2 + 1, id[i + 1][j] * 2, 1, 0);
                add(id[i][j] * 2 + 1, id[i + 1][j + 1] * 2, 1, 0);
            }
        }
    printf("%d\n", EK(flow, costs));

    //规则3 建图 放开点和边的限制
    memset(h, - 1, sizeof h);
    idx = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m + i - 1; j ++) {
            add(id[i][j] * 2, id[i][j] * 2 + 1, INF, cost[i][j]); //出入点建边
            if (i == 1) add(S, id[i][j] * 2, 1, 0); //第一行与S建边
            if (i == n) add(id[i][j] * 2 + 1, T, INF, 0);
            if (i < n) { //向左右下建边
                add(id[i][j] * 2 + 1, id[i + 1][j] * 2, INF, 0);
                add(id[i][j] * 2 + 1, id[i + 1][j + 1] * 2, INF, 0);
            }
        }
    printf("%d\n", EK(flow, costs));

    return 0;
}
