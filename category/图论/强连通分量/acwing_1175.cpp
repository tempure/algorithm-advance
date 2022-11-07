#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
typedef vector<int> vi;
typedef long long ll;
typedef pair<int, int> pii;
mt19937 mrand(random_device{}());
const ll mod = 1000000007;
int rnd(int x) { return mrand() % x;}
ll mulmod(ll a, ll b) {ll res = 0; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = (res + a) % mod; a = 2 * a % mod;} return res;}
ll powmod(ll a, ll b) {ll res = 1; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = res * a % mod; a = a * a % mod;} return res;}
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a;}
//snippet-head

//半连通定义:对于分量中的两点 只要存在一个能到另外一个点即可 满足强连通的单向性即可
//导出字图定义之和点有关 和边无关 2个点之间的边要么不选 要么全部选  所以需要判重边
//而且此题卡时间 需要用哈希判重边
//第一问解法：先缩点 然后寻找缩点后的最长链 并且这个链上不能有分支 然后统计该链所有缩点前的小点个数和即可
//第二问DP 按照拓扑序递推

const int N = 100010, M = 2000010; //要建一个缩点后的新图 所以开2倍数

int n, m, MOD;
int h[N], hs[N], e[M], ne[M], idx;
int dfn[N], low[N], timestamp;
int stk[N], top;
bool in_stk[N];
int id[N], scc_cnt, sz[N];
int f[N], g[N]; //f记录每个点DP的最大值 g记录当前最大的方案值

void add(int h[], int a, int b) {
    e[idx] = b;
    ne[idx]  = h[a];
    h[a] = idx ++;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++timestamp;
    stk[++top] = u, in_stk[u] = true;

    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (!dfn[j]) {
            tarjan(j);
            low[u] = min(low[u], low[j]);
        }
        else if (in_stk[j]) low[u] = min(low[u], dfn[j]);
    }

    if (dfn[u] == low[u]) {
        ++scc_cnt;
        int y;
        do {
            y = stk[top--];
            in_stk[y] = false;
            id[y] = scc_cnt;
            sz[scc_cnt] ++;
        } while (y != u);
    }
}

int main() {
    memset(h, -1, sizeof h);
    memset(hs, -1, sizeof h); //缩点后的图的表头

    scanf("%d%d", &n, &m);
    scanf("%d", &MOD);

    while (m --) {
        int a, b;
        scanf("%d%d", &a, &b);
        add(h, a, b);
    }

    for (int i = 1; i <= n; i++)
        if (!dfn[i]) tarjan(i);

    //建立新图
    unordered_set<ll> S; //(u, v) -> u * 1e6 + v  可以这样哈希 因为u,v范围都是1e6以内
    for (int i = 1; i <= n; i++)
        for (int j = h[i]; j != -1; j = ne[j]) {
            int k = e[j];
            int a = id[i], b = id[k];
            ll hash = 1000000ll * a + b;
            if (a != b && !S.count(hash)) {
                add(hs, a, b);
                S.insert(hash);
            }
        }

    //节点编号递减的顺序已经是拓扑序了
    for (int i = scc_cnt; i;  i -- ) {
        if (!f[i]) {
            f[i] = sz[i];
            g[i] = 1;
        }
        for (int j = hs[i]; j != -1; j = ne[j]) {
            int k = e[j];
            if (f[k] < f[i] + sz[k]) {
                f[k] = f[i] + sz[k];
                g[k] = g[i];
            }
            else if (f[k] == f[i] + sz[k])
                g[k] = (g[k] + g[i]) % MOD;
        }
    }

    int maxf = 0, sum = 0; //最长链 最大字图数目

    for (int i = 1; i <= scc_cnt; i++)
        if (f[i] > maxf) {
            maxf = f[i];
            sum = g[i];
        }
        else if (f[i] == maxf)
            sum = (sum + g[i]) % MOD;

    printf("%d\n", maxf);
    printf("%d\n", sum);

    return 0;
}