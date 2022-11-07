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
树上的点权的状态：安装=1 没有安装 = 0

本质上就是维护2个操作：
将一个节点到根节点的路径所有点置为1 以及将一棵子树的点全部置为0

计算修改的数量：计算修改前和修改后整棵树的和 相减即可
*/

const int N = 100010; //单向边

int n, m;
int h[N], e[N], ne[N], idx;
int id[N], cnt;
int dep[N], sz[N], top[N], fa[N], son[N];

struct Tree {
    int l, r, flag, sum; //lazytag -1表示没有, 0是置为0, 1是置为1 
} tr[N * 4];

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void dfs1(int u, int depth) { //单向边 father节点在加边的时候就可以知道了
    dep[u] = depth, sz[u] = 1;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        dfs1(j, depth + 1);
        sz[u] += sz[j];
        if (sz[son[u]] < sz[j]) son[u] = j;
    }
}

void dfs2(int u, int t) {
    id[u] = ++cnt, top[u] = t;
    if (!son[u]) return;
    dfs2(son[u], t);
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (j == son[u]) continue;
        dfs2(j, j);
    }
}

void pushup(int u) {
    tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
}

void pushdown(int u) {
    auto &root = tr[u], &left = tr[u << 1], &right = tr[u << 1 | 1];
    if (root.flag != -1) {
        left.sum = root.flag * (left.r - left.l + 1);
        right.sum = root.flag * (right.r - right.l + 1);
        left.flag = right.flag = root.flag;
        root.flag = -1;
    }
}

void build(int u, int l, int r) {
    tr[u] = {l, r, -1, 0}; //初始点权都是0 不用pushup
    if (l == r) return;
    int mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
}

//线段树更新区间
void update(int u, int l, int r, int k) {
    if (l <= tr[u].l && r >= tr[u].r) {
        tr[u].flag = k;
        tr[u].sum = k * (tr[u].r - tr[u].l + 1);
        return;
    }
    int mid = tr[u].l + tr[u].r >> 1;
    pushdown(u);
    if (l <= mid) update(u << 1, l, r, k);
    if (r > mid) update(u << 1 | 1, l, r, k);
    pushup(u);
}

void update_path(int u, int v, int k) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        update(1, id[top[u]], id[u], k);
        u = fa[top[u]];
    }
    if (dep[u] < dep[v]) swap(u, v);
    update(1, id[v], id[u], k);
}

void update_tree(int u, int k) {
    update(1, id[u], id[u] + sz[u] - 1, k);
}

int main() {
    scanf("%d", &n);
    memset(h, -1, sizeof h);
    for (int i = 2; i <= n; i++) {
        int p;
        scanf("%d", &p);
        p ++; //编号改为从1开始
        add(p, i);
        fa[i] = p;
    }
    dfs1(1, 1);
    dfs2(1, 1);
    build(1, 1, n);

    scanf("%d", &m);
    char op[20];
    int x;
    while (m --) {
        scanf("%s%d", op, &x);
        x ++;
        if (!strcmp(op, "install")) {
            int t = tr[1].sum; //整个树的权值和
            update_path(1, x, 1); //将到根的路径全部改为1
            printf("%d\n", tr[1].sum - t); //多出来的就是将0改为1的数量
        }
        else {
            int t = tr[1].sum;
            update_tree(x, 0); //将x为根的子树全部变为0
            printf("%d\n", t - tr[1].sum);
        }
    }

    return 0;
}