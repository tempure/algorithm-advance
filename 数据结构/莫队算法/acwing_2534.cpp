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
树上莫队模板:
1.离散化
2.求欧拉序列
3.求lca
4.将询问转换为欧拉序列的区间询问:
如果lca(a,b) == a那么a,b之间的路径就是a第一次出现的位置到b第一次出现的位置中只出现一次的树的节点的编号
否则就是last[a]到first[b]
5.朴素莫队处理即可

误区：找路径是先找出“点编号”的路径，和权值没有关系，然后在路径上再对权值进行莫队。
*/

const int N = 100010;

int n, m, len;
int w[N]; //节点的权值
int h[N], e[N], ne[N], idx;
int depth[N], f[N][16];
int top, first[N], last[N]; //last[]节点第一次出现在欧拉序列中的位置 last最后一次出现位置
int cnt[N], st[N]; //cnt点权值出现的次数 st[]一个点的编号出现的奇偶性
int ans[N]; //答案
int seq[N]; //欧拉序列
int que[N]; //bfs宽搜队列
vi nums;  //离散化

struct Query {
    int id, l, r, p; //p是否加上lca的标记
} q[N];

void add_edge(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

//求出欧拉序列 u是树的节点编号
void dfs(int u, int father) {
    seq[++top] = u; //top是欧拉徐列的下标
    first[u] = top;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (j != father) dfs(j, u); //防止搜反向边
    }
    seq[++top] = u; //递归子树结束后二次进入序列
    last[u] = top;
}

//bfs处理求lca的树节点的深度
void bfs() {
    memset(depth, 0x3f, sizeof depth);
    depth[0] = 0, depth[1] = 1;
    int hh = 0, tt = 0;
    que[0] = 1;
    while (hh <= tt) {
        int t = que[hh++];
        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (depth[j] > depth[t] + 1) {
                depth[j] = depth[t] + 1;
                f[j][0] = t;
                for (int k = 1; k <= 15; k ++)
                    f[j][k] = f[f[j][k - 1]][k - 1];
                que[++tt] = j;
            }
        }
    }
}

//倍增求LCA
int lca(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    for (int k = 15; k >= 0; k--)
        if (depth[f[a][k]] >= depth[b])
            a = f[a][k]; //将a跳到和b同样的深度
    if (a == b) return a;
    for (int k = 15; k >= 0; k--)
        if (f[a][k] != f[b][k]) {
            a = f[a][k];
            b = f[b][k];
        }
    return f[a][0];
}

int get(int x) {
    return x / len;
}

bool cmp(const Query &a, const Query &b) {
    int i = get(a.l), j = get(b.l);
    if (i != j) return i < j;
    return a.r < b.r;
}

//删去一个数，由于是异或操作，和add()一个相同的数是一样的效果
void add(int x, int &res) {
    st[x] ^= 1;
    if (st[x] == 0) {
        cnt[w[x]] --; //注意cnt里面是权值
        if (!cnt[w[x]]) res--;
    }
    else {
        if (!cnt[w[x]]) res ++;
        cnt[w[x]] ++;
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &w[i]);
        nums.pb(w[i]);
    }
    sort(all(nums));
    nums.erase(unique(all(nums)), nums.end());
    for (int i = 1; i <= n; i++)
        w[i] = lower_bound(all(nums), w[i]) - nums.begin();

    memset(h, -1, sizeof h);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        add_edge(a, b), add_edge(b, a);
    }

    dfs(1, -1);
    bfs();

    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        if (first[a] > first[b]) swap(a, b);
        int p = lca(a, b);
        if (a == p) q[i] = {i, first[a], first[b]};
        else q[i] = {i, last[a], first[b], p};
    }

    len = sqrt(top);
    sort(q, q + m, cmp);

    for (int k = 0, i = 0, j = 1, res = 0; k < m; k++) {
        int id = q[k].id, l = q[k].l, r = q[k].r, p = q[k].p;
        while (i < r) add(seq[++i], res);
        while (i > r) add(seq[i--], res);
        while (j < l) add(seq[j++], res);
        while (j > l) add(seq[--j], res);
        if (p) add(p, res);
        ans[id] = res;
        if (p) add(p, res);//加上p之后要删掉p 因为每个p都有标记的不能重复
    }
    for (int i = 0; i < m; i++) printf("%d\n", ans[i]);

    return 0;
}