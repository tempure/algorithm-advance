/*
第一行包含两个整数 N 和 M。
接下来 N 行，每行包含 M 个字符，字符为”W”或”.”，用以表示矩形土地的积水状况，字符之间没有空格。
*/
#define x first
#define y second
const int N = 1010;
typedef pair<int, int> pii;
int n, m;
char g[N][N];
const int M = N * N;
bool st[N][N];
pii q[M];
void bfs(int sx, int sy) {
    int hh = 0, tt = 0;  //初始化
    q[0] = {sx, sy};
    st[sx][sy] = true;
    while (hh <= tt) {
        pii t = q[hh++];
        for (int i = t.x - 1; i <= t.x + 1; i++) //八连通遍历
            for (int j = t.y - 1; j <= t.y + 1; j++) {
                // 是中心点自己 跳过 已经标记过了 在函数开头
                if (i == t.x && j == t.y) continue;
                if (i < 0 || i >= n || j < 0 || j >= m)
                    continue; // 越界
                //是否已经标记过 以及是否不是水洼
                if (g[i][j] == '.' || st[i][j]) continue;
                q[++tt] = {i, j};
                st[i][j] = true;
            }
    }
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%s", g[i]);
    int cnt = 0;
    for (int i = 0;  i < n; i++) //逐行bfs
        for (int j = 0 ; j < m; j++)
            if (g[i][j] == 'W' && !st[i][j]) {
                bfs(i, j);
                cnt ++;
            }
    printf("%d\n", cnt);
    return 0;
}

/*
山峰山谷问题:第一行包含一个正整数 n，表示地图的大小
接下来一个 n×n 的矩阵，表示地图上每个格子的高度 w
共一行，包含两个整数，表示山峰和山谷的数量。
输入样例:
5
5 7 8 3 1
5 5 7 6 6
6 6 6 2 8
5 7 2 5 8
7 1 0 1 7
输出样例:
3 3
*/
#define x first
#define y second
const int N = 1010, M = N * N;
typedef pair<int, int> pii;
int n;
int h[N][N];
pii q[M];
bool st[N][N];
//注意是高度相同 的连通块 再进行周围的判断 一个连通块的元素肯定都是一样的一个连通块周围所有元素 都比连通块高 那就是山谷 反之就是山峰
//bfs函数调用一次就会遍历一整个连通块
void bfs(int sx, int sy, bool & has_heigher, bool & has_lower) {
    int hh = 0, tt = 0;
    q[0] = {sx, sy};
    st[sx][sy] = true;
    while (hh <= tt) {
        pii t = q[hh++];
        for (int i = t.x - 1; i <= t.x + 1; i++)
            for (int j = t.y - 1; j <= t.y + 1; j++) {
                //这个判断可有可无 如果不加 后边会在st判断时候 不会入队
                if (i == t.x && j == t.y) continue;
                if (i < 0 || i >= n || j < 0 || j >= n) continue;
                //只要周围的点高度和中心点不一样，那就不在同一个连通块里
                //高度相同的 就直接不会进入下面的if判断
                if (h[i][j] != h[t.x][t.y]) {
                    if (h[i][j] > h[t.x][t.y]) has_heigher = 1;
                    else has_lower = 1;
                }
                else if (!st[i][j]) {
                    q[++tt] = {i, j};
                    st[i][j] = 1;
                }
            }
    }
}
int main() {
    scanf("%d", &n);
    for (int i = 0 ; i < n; i++)
        for (int j = 0 ; j  < n; j++)
            scanf("%d" , &h[i][j]);
    int peak = 0, valley = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0 ; j < n; j++)
            if (!st[i][j]) {
                bool has_heigher = false, has_lower = false;
                bfs(i , j, has_heigher, has_lower);
                //遍历整个连通块之后 周围没有比当前连通块高的就是山峰
                //反之是山谷 或者是一整个连通块 那就都算 都+1
                if (!has_heigher) peak++;
                if (!has_lower) valley ++;
            }
    printf("%d %d\n", peak, valley);
    return 0;
}