/*
给定一棵树，树中包含 n 个结点（编号1~n）和 n−1 条无向边，每条边都有一个权值。
现在请你找到树中的一条最长路径。
换句话说，要找到一条路径，使得使得路径两端的点的距离最远。
注意：路径中可以只包含一个点。
输入格式:第一行包含整数 n。
接下来 n−1 行，每行包含三个整数 ai,bi,ci，表示点 ai 和 bi 之间存在一条权值为 ci 的边。
输出格式:输出一个整数，表示树的最长路径的长度。
*/
int n;
const int N = 10010;
const int M = 2 * N; //边数 无向边 两遍加
//最长路径 也叫树的直径
//做法: 遍历每一个点 然后求出穿过这个点的所有路径 中最长的
//具体求法：求出距离某节点最远的2个叶节点 然后加起来 不断更新
int h[N], ne[M], e[M], w[M], idx;
int ans;
void add(int a, int b, int x) {
    e[idx] = b;
    w[idx] = x;
    ne[idx] = h[a];
    h[a] = idx ++;
}
int dfs(int u, int father) {
    int dist = 0;  //表示当前点往下走的最大长度
    //求出所有挂在这个root上的最长和第二长的距离
    int d1 = 0, d2 = 0;
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (j == father) continue;
        int d = dfs(j, u) + w[i]; //u是j的父节点
        dist = max(dist, d); //用子节点更新dist
        if (d >= d1) d2 = d1, d1 = d; //比最大值大 那就把最大值换位第二大值
        else if (d > d2) d2 = d; //比最大的小 但是比第二大的大 就换位第二大的值
    }
    ans = max(ans, d1 + d2);
    return dist;
}
int main() {
    memset(h, -1 , sizeof h);
    cin >> n;
    for (int i = 0 ; i < n - 1; i++) { //共有n-1条边
        int a, b, x;
        cin >> a >> b >> x;
        add(a, b , x);
        add(b, a, x);
    }
    dfs(1, -1);  //第一个参数是根节点 由于是连通图 任意一个点都可以为root 这里取1号随意
    //dfs的第二参数是父节点，是为了让遍历的顺序 从上往下 根节点设为-1即可 一个不存咋的数
    cout << ans << endl;
    return 0;
}