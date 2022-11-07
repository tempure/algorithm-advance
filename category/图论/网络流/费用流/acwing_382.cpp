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
K取方格数问题
每个点拆点，但是拆点有技巧，点内部要连2条边
一条的容量为1，费用为点权c，代表这个点被当前路径选择掉了，对答案产生贡献
另外一条边容量INF,费用为0，代表一个已经被选过的点的存在，但会被其他很多路径选择，对答案没贡献

虚拟S向左上角入点连边，容量k，费用0，右下角出点向T连边，容量k，费用0
*/

const int N = 5010, M = 20010, INF = 0x3f3f3f3f;

int n, k, S, T;
int h[N], e[M], ne[M], f[M], w[M], idx;
int q[N], d[N], pre[N], incf[N];
bool st[N];

int get(int x, int y, int t) { //0代表入点 1代表出点
    //每个点的入点编号为2 * x 出点为 2 * x + 1
    return (x * n + y) * 2 + t;
}

void add(int a, int b, int c, int d) {
    e[idx] = b, f[idx] = c, w[idx] = d, ne[idx] = h[a], h[a] = idx ++;
    e[idx] = a, f[idx] = 0, w[idx] = -d, ne[idx] = h[b], h[b] = idx ++;
}

bool spfa() {
    int hh = 0, tt = 1;
    memset(d, 0xcf, sizeof d); //注意是求最大费用
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
    return cost;
}

int main() {
    scanf("%d%d", &n, &k);
    S = 2 * n * n, T = S + 1; //ST编号随便设，只要不和图中的点重合即可
    memset(h, - 1, sizeof h);
    add(S, get(0, 0, 0), k, 0); //虚拟S向左上角的点入点连边
    add(get(n - 1, n - 1, 1), T, k, 0); //右下角出点向T连边
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            int c; scanf("%d", &c);
            add(get(i, j, 0), get(i, j, 1), 1, c); //点内部连第一条边
            add(get(i, j, 0), get(i, j, 1), INF, 0);
            if (i + 1 < n) add(get(i, j, 1), get(i + 1, j, 0), INF, 0); //每个点向下连边
            if (j + 1 < n) add(get(i, j, 1), get(i, j + 1, 0), INF, 0); //向右连边
        }

    printf("%d\n", EK());

    return 0;
}