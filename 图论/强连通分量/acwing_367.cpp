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

//SCC的一个主要作用就是可以把一个有向图转换为DAG处理

//Tarjan缩点+拓扑后 统计有多少个入度为0的点 假设是p个 出度为0的点假设是q个
//第一个问题: 至少需要的个数就是 p
//第二个问题转化为：最少需要加几条边才能将一个图变为一个强连通分量
//如果不是强连通分量，答案是max(p, q)  如果整个图只有一个点 那么答案就是0

const int N = 110, M = 10010;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], timestamp;
int stk[N], top;
bool in_stk[N];
int din[N], dout[N];
int id[N], scc_cnt;
int n;

void add(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
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
        } while (y != u);
    }
}

int main() {
    scanf("%d", &n);
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; i++) {
        int t;
        while (scanf("%d", &t) && t) add(i, t);
    }

    for (int i = 1; i <= n; i++)
        if (!dfn[i]) tarjan(i);

    //统计强连通分量的出入度
    for (int i = 1; i <= n; i++)
        for (int j = h[i]; j != -1; j = ne[j]) {
            int k = e[j];
            int a = id[i], b = id[k];
            if (a != b) {
                dout[a] ++;
                din[b] ++;
            }
        }

    //统计出入度为0的缩点
    int a = 0, b = 0;
    for (int i = 1; i <= scc_cnt; i++) { //注意是循环到scc_cnt即可 不是n
        if (!din[i]) a++;
        if (!dout[i]) b ++;
    }

    printf("%d\n", a);
    if (scc_cnt == 1) puts("0");
    else printf("%d\n", max(a, b));

    return 0;
}