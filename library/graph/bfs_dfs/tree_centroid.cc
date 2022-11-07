/*
树的重心：DFS
给定一颗树，树中包含n个结点（编号1~n）和n-1条无向边。找到树的重心，并输出将重心删除后，剩余各个连通块中点数的最大值。
重心定义：重心是指树中的一个结点，如果将这个点删除后，剩余各个连通块中点数的最大值最小，那么这个节点被称为树的重心。
第一行包含整数n，表示树的结点数。接下来n-1行，每行包含两个整数a和b，表示点a和点b之间存在一条边。
输出一个整数m，表示将重心删除后，剩余各个连通块中点数的最大值。
数据范围1 <= n <= 1e5
*/
int ans = 0x3f3f3f3f;   //最终答案
const int N = 100010;
int e[2 * N], ne[2 * N], h[N], idx;//无向图边开2倍
int v[N]; //记忆化
int pos;  //重心位置
int sz[N];  //每个节点为根的子树的大小
int n;
//注意 一棵树的重心不唯一
void add(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx ++;
}
void dfs(int x) {
    v[x] = 1; sz[x] = 1;
    int maxpart = 0;  //删掉x后分成的最大子树的大小
    for (int i = h[x]; i != -1; i = ne[i]) {
        int y = e[i];
        if (v[y]) continue;
        dfs(y);
        sz[x] += sz[y];
        maxpart = max(maxpart, sz[y]);  //要把x删掉了 所以看一下和x相接的节点的子树权重
    }
    maxpart = max(maxpart, n - sz[x]);
    if (maxpart < ans) {
        ans = maxpart;
        pos = x; //重心位置
    }
}
int main() {
    int a, b; cin >> n;
    memset(h, -1 , sizeof h); //切记初始化要在加边之前
    for (int i = 0; i < n - 1; i++) {
        cin >> a >> b;
        add(a, b); add(b, a);
    }
    dfs(1); //从任意起点开始都可以  搜索顺序不重要
    cout << ans << endl;
    return 0;
}