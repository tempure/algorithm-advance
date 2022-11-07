/*
给定一个N行M列的01矩阵A，A[i][j] 与 A[k][l] 之间的曼哈顿距离定义为：
dist(A[i][j],A[k][l])=|i−k|+|j−l|
输出一个N行M列的整数矩阵B，其中：
B[i][j]=min{1 <= x <= N,1 <= y <= M,A[x][y]=1[dist(A[i][j],A[x][y])]}
输入:
第一行两个整数n,m。接下来一个N行M列的01矩阵，数字之间没有空格。
输出格式:一个N行M列的矩阵B，相邻两个整数之间用一个空格隔开 1 <= N,M <= 1000
输入样例:
3 4
0001
0011
0110
输出样例：
3 2 1 0
2 1 0 0
1 0 0 1
*/
typedef pair<int, int> pii;
#define x first
#define y second
const int N = 1010, M = N * N;
char g[N][N]; //读入没有空格 注意
int n, m;
pii q[M];
int dist[N][N];
//题意就是每个点到最近的1的距离，如果为1自己距离那本身就是0
//多源BFS 求出离每个点最近的起点的距离
//先把所有1入队，然后根据这些点开始向外扩张，最终bfs全图
void bfs() {
    memset(dist, -1, sizeof dist);
    int hh = 0, tt = -1; //开始队内没有元素 不能写成tt = 0
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (g[i][j] == '1') {
                dist[i][j] = 0;  //先把所有是1的点入队 保持距离的单调性
                q[++tt] = {i, j};
            }
    int dx[4] = { -1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
    while (hh <= tt) {
        auto t = q[hh++];
        for (int i = 0 ; i < 4; i++) {
            int a = t.x + dx[i], b = t.y + dy[i];
            if (a < 0 || a >= n || b < 0 || b >= m) continue;
            if (dist[a][b] != -1) continue;
            dist[a][b] = dist[t.x][t.y] + 1;
            q[++tt] = {a, b};
        }
    }
}
int main() {
    scanf("%d%d", &n , &m);
    for (int i = 0 ; i < n; i++) scanf("%s", g[i]);
    bfs();
    for (int i = 0; i < n; i++) {
        for (int j = 0 ; j < m; j++)
            printf("%d ", dist[i][j]);
        printf("\n");
    }
    return 0;
}