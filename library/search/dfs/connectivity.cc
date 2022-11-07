/*
迷宫可以看成是由 n∗n 的格点组成，每个格点只有2种状态，.和#，前者表示可以通行后者表示不能通行。
第1行是测试数据的组数 k，后面跟着 k 组输入。
每组测试数据的第1行是一个正整数 n，表示迷宫的规模是 n∗n 的。
接下来是一个 n∗n 的矩阵，矩阵中的元素为.或者#。
再接下来一行是 4 个整数 ha,la,hb,lb，描述 A 处在第 ha 行, 第 la 列，B 处在第 hb 行, 第 lb 列。
注意到 ha,la,hb,lb 全部是从 0 开始计数的
输入样例：
2
3
.##
..#
#..
0 0 2 2
5
.....
###.#
..#..
###..
...#.
0 0 4 0
输出样例:
YES
NO
*/
//dfs只能保证连通性 不能求出以及保证最短路 优点是代码短 时间复杂度都一样 线性搜一次
const int N = 110;
char g[N][N];
bool st[N][N];
int n;
int xa, ya, xb, yb;
int dx[4] = { -1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
bool dfs(int x, int  y) {
    if (g[x][y] == '#') return 0; //终点可能是障碍物 这一步要先于下一行判断
    if (x == xb && y == yb) return 1;
    st[x][y] = 1;
    for (int i = 0; i < 4; i++) {
        int a = x + dx[i], b = y + dy[i];
        if (a < 0 || a >= n || b < 0 || b >= n) continue;
        if (st[a][b]) continue;
        // if((g[a][b]) == '#') continue;
        if (dfs(a, b)) return 1;
    }
    return false;
}
int main() {
    int t;
    cin >> t;
    while (t --) {
        cin >> n;
        for (int i = 0 ; i < n; i++) cin >> g[i];
        memset(st, 0, sizeof st);
        cin >> xa >> ya >> xb >> yb;
        if (dfs(xa, ya)) puts("YES"); //xa ya能否走到目标点
        else puts("NO");
    }
    return 0;
}