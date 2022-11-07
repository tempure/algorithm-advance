/*例题：电路维修
第一行包含一个整数T，表示测试数据的数目。
对于每组测试数据，第一行包含正整数R和C，表示行数和列数。
之后R行，每行C个字符，字符是"/"和"\"中的一个，表示方向
输入样例：
1
3 5
\\/\\
\\///
/\\\\
输出样例：
1
*/
typedef pair<int, int> pii;
//一个点的横纵坐标和是奇数 就不能到达 偶数就可以到达
//这个图的边权只有0和1，能走就是1，不能走就是0
//将0插入队头，1插入队尾，这样才能保住队列的单调性
const int N = 510, M = N * N;
int n, m;
char g[N][N];
int dist[N][N];
bool st[N][N];  //判重
int bfs() {
    deque<pii> q;
    //每个点会入队多次
    int hh = 0, tt = 0;
    memset(st, 0, sizeof st);
    memset(dist, 0x3f, sizeof dist);
    char cs[] = "\\/\\/"; //每个点顺时针旋转四个方向的边
    //每个点对角线可以走到的4个点, 点->点
    int dx[4] = { -1, -1, 1, 1}, dy[4] = { -1, 1, 1, -1};
    //每个点 周围的4个斜线的坐标转换 点->线
    int ix[4] = { -1, -1, 0, 0}, iy[4] = { -1, 0, 0, -1};
    dist[0][0] = 0;
    q.push_back({0, 0});
    while (q.size()) {
        auto t = q.front();
        q.pop_front();
        int x = t.x, y = t.y;
        if (x == n && y == m) return dist[x][y];
        if (st[x][y]) continue;
        st[x][y] = true;
        for (int i = 0 ; i < 4; i++) {
            int a = x + dx[i], b = y + dy[i]; //周围的四个点
            if (a < 0 || a > n || b < 0 || b > m) continue; //格点是边数+1 注意边界
            int ga = x + ix[i], gb = y + iy[i]; //周围的四条边
            int w = ( g[ga][gb] != cs[i] ); //能直达就是0 需旋转就是1
            int d = dist[x][y] + w;
            if (d <= dist[a][b]) {
                dist[a][b] = d;
                if (!w) q.push_front({a, b});//边权是0入队头
                else q.push_back({a, b}); //边权是1就加入队尾
            }
        }
    }
    return -1;  //不会被执行到
}
int main() {
    int t; scanf("%d", &t);
    while (t -- ) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i ++ ) scanf("%s", g[i]);
        int t = bfs();
        if (n + m & 1 || t == 0x3f3f3f3f || t == -1) puts("NO SOLUTION");
        else printf("%d\n", bfs());
    }
    return 0;
}