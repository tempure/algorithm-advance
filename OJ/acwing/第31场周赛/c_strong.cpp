#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define um unordered_map
#define pq priority_queue
#define sz(x) ((int)(x).size())
#define x first
#define y second
#define endl '\n'
typedef vector<int> vi;
#define ll LL
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int>PII;
mt19937 mrand(random_device{}());
const ll mod = 1000000007;
int rnd(int x) { return mrand() % x;}
ll mulmod(ll a, ll b) {ll res = 0; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = (res + a) % mod; a = 2 * a % mod;} return res;}
ll powmod(ll a, ll b) {ll res = 1; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = res * a % mod; a = a * a % mod;} return res;}
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a;}
//head


const int N = 1010, M = 10;

int n, m, Q;
PII point[N];
int h[N], e[N], ne[N], idx;
int q[N], depth[N], fa[N][M];
int bel[N]; //belong 每个点所属于的最小的圆

struct Circle
{
    int x, y, r;
} cir[N];

LL sqr(LL x)
{
    return x * x;
}

bool check(PII p, Circle c)
{
    LL dx = p.x - c.x;
    LL dy = p.y - c.y;
    if (sqr(dx) + sqr(dy) < sqr(c.r)) return true;
    return false;
}

void add(int a, int b)  // 添加一条边a->b
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

void bfs(int root)  // 预处理倍增数组
{
    memset(depth, 0x3f, sizeof depth);
    depth[0] = 0, depth[root] = 1;  // depth存储节点所在层数
    int hh = 0, tt = 0;
    q[0] = root;
    while (hh <= tt)
    {
        int t = q[hh ++ ];
        for (int i = h[t]; ~i; i = ne[i])
        {
            int j = e[i];
            if (depth[j] > depth[t] + 1)
            {
                depth[j] = depth[t] + 1;
                q[ ++ tt] = j;
                fa[j][0] = t;  // j的第二次幂个父节点
                for (int k = 1; k <= 9; k ++ )
                    fa[j][k] = fa[fa[j][k - 1]][k - 1];
            }
        }
    }
}

int lca(int a, int b)  // 返回a和b的最近公共祖先
{
    if (depth[a] < depth[b]) swap(a, b);
    for (int k = 9; k >= 0; k -- )
        if (depth[fa[a][k]] >= depth[b])
            a = fa[a][k];
    if (a == b) return a;
    for (int k = 9; k >= 0; k -- )
        if (fa[a][k] != fa[b][k])
        {
            a = fa[a][k];
            b = fa[b][k];
        }
    return fa[a][0];
}


int main()
{
    scanf("%d%d%d", &n, &m, &Q);
    for (int i = 1; i <= n; i ++ ) scanf("%d%d", &point[i].x, &point[i].y);
    for (int i = 1; i <= m; i ++ )
        scanf("%d%d%d", &cir[i].r, &cir[i].x, &cir[i].y);

    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; i ++ )
        for (int j = 1; j <= m; j ++ )
            if (check(point[i], cir[j]))
                if (!bel[i] || cir[bel[i]].r > cir[j].r)
                    bel[i] = j; //预处理每个点所处的最小的圆

    for (int i = 1; i <= n; i ++ )
        if (!bel[i])
            bel[i] = m + 1; //没有被任何圆包含的点，让所有圆外的最大的空白区域当作一个圆

    for (int i = 1; i <= m; i ++ ) //圆之间连边，建树
    {
        int t = 0;
        for (int j = 1; j <= m; j ++ )
            if (cir[j].r > cir[i].r && check({cir[i].x, cir[i].y}, cir[j]))
                if (!t || cir[t].r > cir[j].r)
                    t = j;
        if (!t) add(m + 1, i); //如果这个圆不被任何圆包含，也就是上面的 check 过不去，那就和空白区域连边，有向边
        else add(t, i); //否则找出包含当前圆的最小的圆向其连边
    }

    bfs(m + 1); //预处理LCA,O(nlogn)

    while (Q -- )
    {
        int a, b;
        scanf("%d%d", &a, &b);
        a = bel[a], b = bel[b]; //找出该点所处的最小的圆，然后求最短路，注意包含该点的最小圆也算在答案内
        int p = lca(a, b);
        printf("%d\n", depth[a] + depth[b] - depth[p] * 2);
    }

    return 0;
}