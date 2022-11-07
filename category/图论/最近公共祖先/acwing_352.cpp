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


//倍增LCA 树上差分

const int N = 100010, M = N * 2; //这里只算树边 无向边 非树边不需要加入图中 直接在线处理

int n, m;
int h[N], e[M], ne[M], w[M], idx;
int depth[N], fa[N][17];
int q[N];
int d[N]; //存储每个点差分的值

int ans = 0; //全局答案 用dfs更新

void add(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx ++;
}

void bfs() {
    memset(depth, 0x3f, sizeof depth);
    depth[0] = 0, depth[1] = 1; //1号默认为root
    int hh = 0, tt = 0;
    q[0] = 1;

    while (hh <= tt) {
        int t = q[hh++];
        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (depth[j] > depth[t] + 1) {
                depth[j] = depth[t] + 1;
                q[++tt] = j;
                fa[j][0] = t;
                for (int k = 1; k <= 16; k++)
                    fa[j][k] = fa[fa[j][k - 1]][k - 1];
            }
        }
    }
}

int lca(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    for (int k = 16; k >= 0; k --)
        if (depth[fa[a][k]] >= depth[b])
            a = fa[a][k];
    if (a == b) return a;

    for (int k = 16; k >= 0; k--)
        if (fa[a][k] != fa[b][k]) {
            a = fa[a][k];
            b = fa[b][k];
        }

    return fa[a][0];
}

int dfs(int u, int father) { //当前节点为根的子树所有点的权值和
    int res = d[u];
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (j != father) {
            int s = dfs(j, u);
            if (s ==  0) ans += m;
            else if (s == 1) ans ++;
            res += s;
        }
    }
    return res;
}

int main() {
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b); add(b, a);
    }

    bfs(); //预处理dpeth和fa数组


    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        int p = lca(a, b);
        d[a] += 1, d[b] += 1, d[p] -= 2;
    }

    dfs(1, -1);
    printf("%d\n", ans);

    return 0;
}