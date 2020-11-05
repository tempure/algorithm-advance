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

//此题也可以spfa差分约束跑负环 但是需要栈优化 而且可能会被卡掉
//用强连通分量可以线性复杂度稳过掉

//因为所有的环必然在强连通分量中 此问题有解的前提是图中没有正环 不然不存在最长路
//也就是说会正环出现 a >= b, b >=c, c >= a这种矛盾关系
//同理 如果一个强连通分量中有一个正边权的边 那么必然存在正环 直接意味着无解

//如果有解 那么一个强连通分量内的边权 全部都是0 意思是每个强连通分量内的点到起点的距离都一样的
//那么就进行缩点 然后在拓扑图上直接求和即可

//注意还要一个虚拟原点 又每个边权都>=1 设虚拟原点为x[0] 那么x[i] >= x[0] + 1 每个点向虚拟远点连边权为1的边

const int N = 100010, M = 600010;  //每个点对的关系 最坏是都相等，然后加上虚拟原点的边 一共开3倍
//然后要建缩点后的图 所以需要6倍的边数

int n, m;
int h[N], e[M], ne[M], w[M], idx;
int hs[N]; //缩点图的表头
int dfn[N], low[N], timestamp;
int stk[N], top;
bool in_stk[N];
int id[N], scc_cnt, sz[N]; //答案加上每个连通分量内点的个数 * 距离 所以需要维护size
int dist[N]; //最长路


void add(int h[], int a, int b, int c) {
    e[idx] = b;
    ne[idx] = h[a];
    w[idx] = c;
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
        else if (in_stk[j])  low[u] = min(low[u], dfn[j]);
    }

    if (dfn[u] == low[u]) {
        ++scc_cnt;
        int y;
        do {
            y = stk[top--];
            in_stk[y] = false;
            id[y] = scc_cnt;
            sz[scc_cnt]++;
        } while (y != u);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);
    memset(hs, -1, sizeof hs);

    //虚拟原点连边
    for (int i = 1; i <= n; i++) add(h, 0, i, 1);

    while (m --) {
        int t, a, b;
        scanf("%d%d%d", &t, &a, &b);
        if (t == 1) add(h, b, a, 0), add(h, a, b, 0);
        else if (t == 2) add(h, a, b, 1);
        else if (t == 3) add(h, b, a, 0);
        else if (t == 4) add(h, b, a, 1);
        else add(h, a, b, 0);
    }

    tarjan(0); //0号点可以到其他所有点

    bool success = true;
    //建新的缩点图
    for (int i = 0; i <= n; i++) {
        for (int j = h[i]; j != -1; j = ne[j]) {
            int k = e[j];
            int a = id[i], b = id[k];
            if (a == b) {
                if (w[j] > 0) { //存在正边 无解
                    success = false;
                    break;
                }
            }
            else add(hs, a, b, w[j]);
        }
        if (!success) break; //如果一个分量不成立那么直接退出即可 无解
    }

    if (!success) puts("-1");
    else {
        for (int i = scc_cnt; i; i --) //反向就是拓扑序
            for (int j = hs[i]; j != -1; j = ne[j]) {
                int k = e[j];
                dist[k] = max(dist[k], dist[i] + w[j]);
            }
        ll res  = 0;
        for (int i = 1; i <= scc_cnt; i++) res += 1ll * dist[i] * sz[i];
        printf("%lld\n", res);
    }

    return 0;
}