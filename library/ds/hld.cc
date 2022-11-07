/*给定一棵树包含 n 个节点（编号1~n）第 i 个节点的权值为ai。初始时，1号节点为树的根节点。对该树进行m次操作，操作分为以下4种类型：
1 u v k，修改路径上节点权值，将节点u和节点v之间路径上的所有节点（包括这两个节点）的权值增加k。
2 u k，修改子树上节点权值，将以节点u为根的子树上的所有节点的权值增加k。
3 u v，询问路径，询问节点u和节点v之间路径上的所有节点（包括这两个节点）的权值和。
4 u，询问子树，询问以节点u为根的子树上的所有节点的权值和。
树剖的过程只需2次dfs即可。
重子节点:一个树的子树中size最大的一个root就是该点的重子节点 如果有多个都是同样size 选一个即可
轻子节点: 除了唯一的重子节点之外，每个节点的其余子节点都是该点的轻子节点
重链：由重子节点构成的极大路径 树上的每个点都必然在一条重链里,一条重链的开头必然是一个轻子节点
性质：节点数为N的树，任意节点向上走到根经过的轻边数量不超过O(logN)
证明参考：https://zhuanlan.zhihu.com/p/319713720
一个轻点是一条重链的开头节点，也就是一条重链的top,所以任意树上一条路径都可以被划分为O(logN)条连续的重链区间
更新路径时，要用dep较大的点去向上跳来求出lca，理由：
假如要求两个节点的LCA，如果它们在同一条链上，那直接输出深度较小的那个节点就可以了。
否则，LCA要么在链头深度较小的那条链上，要么就是两个链头的父节点的LCA，但绝不可能在链头深度较大的那条链上。
作用：
1.单次O(logN)求lca
2.将树上的路径转化为O(logN)段连续区间,然后用线段树等数据结构维护区间操作实现路径修改/路径求和/子树修改/子树求和*/
typedef long long ll;
const int N = 100010, M = N * 2; //无向边
int n, m;
int w[N], h[N], e[M], ne[M], idx;
int id[N], nw[N], cnt; //id[i]是i编号节点的dfs序新编号 nw是新的编号对应的点权
int dep[N], sz[N]; //dep[]节点在树中的深度,树根深度为1, sz[]当前节点为根的子树的大小
int top[N]; //top[i]该点所在重链的深度最小的节点
int fa[N], son[N]; //父亲节点和每个点的重子节点
struct Tree {
    int l, r;
    ll add, sum; //lazy tag 以及当前区间的和
} tr[N * 4];
void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}
//第一次dfs 求出深度以及sz[] 以及求出重子节点son[]
void dfs1(int u, int father, int depth) {
    dep[u] = depth, fa[u] = father, sz[u] = 1;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (j == father) continue; //不搜反向边
        dfs1(j, u, depth + 1);
        sz[u] += sz[j];
        if (sz[son[u]] < sz[j]) son[u] = j;
    }
}
//第二次dfs 求出新的dfs序列 以及每条重链的top节点
void dfs2(int u, int t) {
    id[u] = ++cnt, nw[cnt] = w[u], top[u] = t;
    if (!son[u]) return; //叶节点
    dfs2(son[u], t); //先dfs完所有的重子节点
    //dfs轻子节点
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (j == fa[u] || j == son[u]) continue; //反向边以及搜过的重子节点跳过
        dfs2(j, j); //一个轻子节点的top是自身，因为轻节点必定是一条重链的开头
    }
}
void pushup(int u) {
    tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
}
void pushdown(int u) {
    auto &root = tr[u], &left = tr[u << 1], &right =  tr[u << 1 | 1];
    if (root.add) { //如果有lazytag
        left.add += root.add, left.sum += root.add * (left.r - left.l + 1);
        right.add += root.add, right.sum += root.add * (right.r - right.l + 1);
        root.add = 0; //清空当前节点的懒标记
    }
}
//线段树建树
void build(int u, int l, int r) {
    tr[u] = {l, r, 0, nw[r]}; //此处nw[r]和nw[l]都可以，本质是递归到叶子节点之后开始pushup
    if (l == r) return;
    int mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
    pushup(u);
}
//修改一个区间元素全部加上k
void update(int u, int l, int r, int k) {
    if (l <= tr[u].l && r >= tr[u].r) {
        tr[u].add += k;
        tr[u].sum += k * (tr[u].r - tr[u].l + 1);
        return;
    }
    pushdown(u);
    int mid = tr[u].l + tr[u]. r >> 1;
    if (l <= mid) update(u << 1, l, r, k);
    if (r > mid) update(u << 1 | 1, l, r, k);
    pushup(u);
}
//线段树查询区间和
ll query(int u, int l, int r) {
    if (l <= tr[u].l && r >= tr[u].r) return tr[u].sum;
    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1;
    ll res = 0;
    if (l <= mid) res += query(u << 1, l, r);
    if (r > mid) res += query(u << 1 | 1, l, r);
    return res;
}
//给路径(u,v)的树节点加上k
void update_path(int u, int v, int k) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        //u是较低的一个重链的节点
        update(1, id[top[u]], id[u], k); //直接给dfs序上的这一段更新
        u = fa[top[u]]; //u跳到当前重链top的上一个点 也就是下一段更高的重链
    }
    //现在两个节点的重链top节点是同一个节点 dep较小的点必然是其与dep较大的点的lca
    //此时更新lca与dep较大的点之间的路径即可
    if (dep[u] < dep[v]) swap(u, v);
    update(1, id[v], id[u], k);
}
//查询树上路径(u,v)的和与修改思路几乎一致
ll query_path(int u, int v) {
    ll res = 0;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        res += query(1, id[top[u]], id[u]);
        u = fa[top[u]];
    }
    if (dep[u] < dep[v]) swap(u, v);
    res += query(1, id[v], id[u]);
    return res;
}
//子树每个节点都加k
void update_tree(int u, int k) {
    update(1, id[u], id[u] + sz[u] - 1, k);
}
//查询子树和
ll query_tree(int u) {
    return query(1, id[u], id[u] + sz[u] - 1);
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &w[i]);
    memset(h, -1, sizeof h);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b), add(b, a);
    }
    dfs1(1, -1, 1); //求重子节点
    dfs2(1, 1); //求重链top节点 root的top就是自身
    build(1, 1, n);
    scanf("%d", &m);
    while (m --) {
        int t, u, v, k;
        scanf("%d%d", &t, &u);
        if (t == 1) {
            scanf("%d%d", &v, &k);
            update_path(u, v, k);
        }
        else if (t == 2) {
            scanf("%d", &k);
            update_tree(u, k);
        }
        else if (t == 3) {
            scanf("%d", &v);
            printf("%lld\n", query_path(u, v));
        }
        else printf("%lld\n", query_tree(u));
    }
    return 0;
}