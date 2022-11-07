/*
有 N 个物品和一个容量是 V 的背包。
物品之间具有依赖关系，且依赖关系组成一棵树的形状。如果选择一个物品，则必须选择它的父节点。
每件物品的编号是 i，体积是 vi，价值是 wi，依赖的父节点编号是 pi。物品的下标范围是 1…N。
求解将哪些物品装入背包，可使物品总体积不超过背包容量，且总价值最大。输出最大价值。
输入格式
第一行有两个整数 N，V，用空格隔开，分别表示物品个数和背包容量。
接下来有 N 行数据，每行数据表示一个物品。
第 i 行有三个整数 vi,wi,pi，用空格隔开，分别表示物品的体积、价值和依赖的物品编号。
如果 pi=−1，表示根节点。 数据保证所有物品构成一棵树。
*/
const int N = 110;
int h[N], ne[N], e[N];
int idx;
int v[N], w[N];
int n, m;
int f[N][N];
void add(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx ++;
}
void dfs(int u) { //遍历u为根的子树
    for (int i = h[u]; ~i; i = ne[i]) {
        int son = e[i];
        dfs(e[i]);
        // 分组背包
        for (int j = m - v[u]; j >= 0; j--) //循环体积 分组
            for (int k = 0; k <= j; k++) //决策
                f[u][j] = max(f[u][j], f[u][j - k] + f[son][k]);
    }
    //将u加进去
    for (int i = m; i >= v[u]; i--) f[u][i] = f[u][i - v[u]] + w[u];
    for (int i = 0; i < v[u]; i++) f[u][i] = 0;
}
//f[u][j] 表示 u 为root的子树中选 总体积不超过j的方案
int main() {
    scanf("%d%d", &n, &m);
    memset(h, -1 , sizeof h);
    int root;
    for (int i = 1; i <= n; i++) {
        int p;
        scanf("%d%d%d", &v[i], &w[i], &p);
        if (p == -1) root = i;
        else add(p, i); //有向边

    }
    dfs(root);
    printf("%d\n", f[root][m]) ;
    return 0;
}