/*
表示墙壁，0表示可以走的路，只能横着走或竖着走，不能斜着走，要求编程序找出从左上角到右下角的最短路线。
0, 1, 0, 0, 0,
0, 1, 0, 1, 0,
0, 0, 0, 0, 0,
0, 1, 1, 1, 0,
0, 0, 0, 1, 0,
第一行包含整数 n。接下来 n 行，每行包含 n 个整数 0 或 1，表示迷宫。输出从左上角到右下角的最短路线，如果答案不唯一，输出任意一条路径均可。
按顺序，每行输出一个路径中经过的单元格的坐标，左上角坐标为 (0,0)，右下角坐标为 (n−1,n−1)。
*/
typedef pair<int , int > pii;
#define x first
#define y second
const int N = 1010, M = N * N;
int g[N][N];
int n;
pii pre[N][N];  //储存路径 当前节点 是由哪一个点转移过来的
pii q[M];
//输出路径的问题，一般从终点往起点搜，然后记录前驱
void bfs(int sx, int sy) {
    int dx[4] = { -1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
    int hh = 0, tt = 0;
    q[0] = {sx, sy};
    memset(pre, -1, sizeof pre);
    while (hh <= tt) {
        pii t = q[hh++];
        for (int i = 0 ; i < 4 ; i++) {
            int a = t.x + dx[i], b = t.y + dy[i];
            if (a < 0 || a >= n || b < 0 || b >= n) continue;
            if (g[a][b]) continue; // 1不能走
            if (pre[a][b].x != -1) continue;
            q[++tt] = {a, b};
            pre[a][b] = t; //(a,b) 是从t转移过来的
        }
    }
}
int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &g[i][j]);
    bfs(n - 1, n - 1); //bfs一次就可以了 反向搜 然后从头输出
    pii end(0, 0);
    while (1) {
        printf("%d %d\n", end.x, end.y);
        if (end.x == n - 1 && end.y == n - 1) break;
        end = pre[end.x][end.y];
    }
    return 0;
}
/*
马走日问题：位置用’K’来标记，障碍的位置用’*’来标记，草的位置用’H’来标记。输出一个整数，表示跳跃的最小次数。
输入样例:10 11
..........
....*.....
..........
...*.*....
.......*..
..*..*...H
*.........
...*...*..
.K........
...*.....*
..*....*..
输出样例：
5
*/
typedef pair<int, int> pii;
#define x first
#define y second
const int N = 155, M = N * N;
int n, m;
char g[N][N];
pii q[M];
bool st[N][N];
int dist[N][N]; //记录次数
int bfs() {
    //日字形的周围的点 共有8个 顺时针对应xy即可
    int dx[8] = { -2, -1, 1, 2, 2, 1, -1, -2};
    int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};
    int sx, sy;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (g[i][j] == 'K')
                sx = i, sy = j;
    int hh = 0, tt = 0;
    q[0] = {sx, sy};
    memset(dist, -1 , sizeof dist);
    dist[sx][sy] = 0;
    while (hh <= tt) {
        auto t = q[hh++];
        for (int i = 0 ; i < 8; i++) {
            int a = t.x + dx[i], b = t.y + dy[i];
            if (a < 0 || a >= n || b < 0 || b >= m) continue;
            if (g[a][b] == '*') continue;
            if (dist[a][b] != -1) continue; //被遍历过了
            if (g[a][b] == 'H') return dist[t.x][t.y] + 1; //已经找到
            dist[a][b] = dist[t.x][t.y] + 1;
            q[++tt] = {a, b};
        }
    }
    return -1;  //题目保证有解 所以写不写无所谓 前边已经返回了
}
int main() {
    cin >> m >> n;
    for (int i = 0 ; i < n; i++) cin >> g[i];
    cout << bfs() << endl;
    return 0;
}

/*
农夫和牛都位于数轴上，农夫起始位于点 N，牛位于点 K。农夫有两种移动方式：
从 X 移动到 X−1 或 X+1，每次移动花费一分钟
从 X 移动到 2∗X，每次移动花费一分钟
假设牛没有意识到农夫的行动，站在原地不动。农夫最少要花多少时间才能抓住牛？输入:共一行，包含两个整数N和K。
*/
const int N = 2e5 + 10;
int n, k;
int q[N];
int dist[N];
//注意n和k的大小关系是不确定的
int bfs() {
    memset(dist, -1 , sizeof dist);
    dist[n] = 0;
    q[0] = n;
    //相当于每次转移一层，每层都进行三种走法的尝试
    //最先到达k的走法 则是最树的最短路
    int hh = 0, tt = 0;
    while (hh <= tt) {
        int t = q[hh++];
        if (t == k) return dist[k];
        if (t + 1 < N && dist[t + 1] == -1) {
            dist[t + 1] = dist[t] + 1;
            q[++tt] = t + 1;
        }
        if (t - 1 >= 0 && dist[t - 1] == -1) {
            dist[t - 1] = dist[t] + 1;
            q[++tt] = t - 1;
        }
        if (t * 2 < N && dist[t * 2] == -1) {
            dist[t * 2] = dist[t] + 1;
            q[++tt] = t * 2;
        }
    }
    return -1;
}
int main() {
    cin >> n >> k;
    cout << bfs() << endl;
    return 0;
}