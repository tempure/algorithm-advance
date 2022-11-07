/*
给定一棵由 n 个节点组成的树。树的节点编号为 1到n，其中 1 号节点为树的根节点。
每个节点上都标有某种颜色。第 i 个节点上的颜色为 ci。
如果在以节点 v 为根节点的子树中，没有任何颜色的出现次数超过颜色 c 的出现次数，那么我们称颜色 c 为该子树的主要颜色。
一些子树的主要颜色可能不止一种。
以节点 v 为根节点的子树由节点 v 以及到达根节点的路径中包含节点 v 的其它所有节点共同组成。
对于每个节点 v(1<=v<=n)，请你求出以该节点为根节点的子树的所有主要颜色之和。
输入格式:第一行包含整数 n。
第二行包含 n 个整数 ci，表示每个节点的颜色编号。
接下来 n−1 行，每行两个整数 x,y 表示节点 x 和 y 之间存在边。
注意，节点 1 为树的根节点。
输出格式:共一行，输出 n 个整数，其中第 i 个整数表示以节点 i 为根节点的子树的所有主要颜色之和。
*/
/*
先重链剖分，每次计算一个子树，只保留重子树的信息
意思就是先计算所有轻子树，最后计算重子树，然后将轻重合起来计算
重节点子树只会被计算一次，所有轻链不超过O(log)
每个点最多被重复计算log 总复杂度O(n*logn)
*/
typedef long long ll;
const int N = 100010, M = 2 * N;
int n;
int h[N], e[M], ne[M], idx;
int color[N], cnt[N], sz[N], son[N];
ll ans[N], sum;
int mx;
void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}
//重链剖分
int dfs_son(int u, int father) {
    sz[u] = 1;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (j == father) continue;
        sz[u] += dfs_son(j, u);
        if (sz[j] > sz[son[u]]) son[u] = j;
    }
    return sz[u];
}
void update(int u, int father, int sign, int pson) {
    int c = color[u];
    cnt[c] += sign;
    if (cnt[c] > mx) mx = cnt[c], sum = c;
    else if (cnt[c] == mx) sum += c;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (j == father || j == pson) continue;
        update(j, u, sign, pson);
    }
}
void dfs(int u, int father, int op) {
    //先计算所有轻子树
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (j == father || j == son[u]) continue;
        dfs(j, u, 0);
    }
    //如果有重子树 直接更新当前树
    if (son[u]) dfs(son[u], u, 1);
    update(u, father, 1, son[u]); //避开son[u]

    ans[u] = sum;
    if (!op) update(u, father, -1, 0), sum = mx = 0; //当前树的父节点不是重的，那就直接清空整个子树
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &color[i]);
    memset(h, -1, sizeof h);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b), add(b, a);
    }
    dfs_son(1, -1);
    dfs(1, -1, 1);
    for (int i = 1; i <= n; i++) printf("%lld ", ans[i]);
    return 0;
}