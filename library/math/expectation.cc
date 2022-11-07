/*
给出一个有向无环的连通图，起点为1，终点为N，每条边都有一个长度。
数据保证从起点出发能到达图中所有的点，所有的点也都能到终点
到达每一个顶点时，如果有K条离开该点的道路，绿豆蛙可以选择任意一条道路离开该点，并且走向每条路的概率为 1/K 。
现在绿豆蛙想知道，从起点走到终点所经过的路径总长度的期望是多少？
输入格式:第一行: 两个整数 N， M，代表图中有N个点、M条边。
第二行到第 1+M 行: 每行3个整数 a, b, c，代表从a到b有一条长度为c的有向边。
输出格式
输出从起点到终点路径总长度的期望值，结果四舍五入保留两位小数。
数据范围1<=N≤1e5,1<=M<=2N
*/
const int N = 1e5 + 10, M = 2 * N;
int n, m;
int h[N], e[M], w[M], ne[M], idx;
int dout[N]; //出度
double f[N]; //DP
void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a];
    h[a] = idx ++;
}
double dp(int u) {
    if (f[u] >= 0) return f[u]; //记忆化
    if (u == n) return f[u] = 0; //终点
    f[u] = 0; //当前点先初始置为0 然后再加
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        f[u] += (w[i] + dp(j)) / dout[u];  //递归反向搜
    }
    return f[u];
}
int main() {
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c);
        dout[a]++;
    }
    memset(f, -1, sizeof f);
    printf("%.2lf\n", dp(1));
    return 0;
}
/*
把一副扑克牌(54张)随机洗开，倒扣着放成一摞。
然后从上往下依次翻开每张牌，每翻开一张黑桃、红桃、梅花或者方块，就把它放到对应花色的堆里去。
问得到A张黑桃、B张红桃、C张梅花、D张方块需要翻开的牌的张数的期望值E是多少？
如果翻开的牌是大王或者小王,将会把它作为某种花色的牌放入对应堆中,使得放入之后E的值尽可能小。
输入格式:输入仅由一行，包含四个用空格隔开的整数，A,B,C,D。
输出格式
输出需要翻开的牌数的期望值E，四舍五入保留3位小数。
如果不可能达到输入的状态，输出-1.000。
*/
const int N = 14;
const double INF = 1e20;
int A, B, C, D;
double f[N][N][N][N][5][5];
double dp(int a, int b, int c, int d, int x, int y) {
    double &v = f[a][b][c][d][x][y];
    if (v >= 0) return v; //记忆化
    int as = a + (x == 0) + (y == 0);
    int bs = b + (x == 1) + (y == 1);
    int cs = c + (x == 2) + (y == 2);
    int ds = d + (x == 3) + (y == 3);
    if (as >= A && bs >= B && cs >= C && ds >= D) return v = 0; //终点
    if (a > 13 || b > 13 || c > 13 || d > 13) return v = INF; //输入有误数据
    int sum = a + b + c + d + (x != 4) + (y != 4); //当前已经翻开的牌总数
    v = 1;  //初始化当前状态 开始计算
    sum = 54 - sum; //剩余牌数
    if (sum <= 0) return v = INF;
    if (a < 13) v += (13.0 - a) / sum * dp(a + 1, b, c, d, x, y);
    if (b < 13) v += (13.0 - b) / sum * dp(a, b + 1, c, d, x, y);
    if (c < 13) v += (13.0 - c) / sum * dp(a, b, c + 1, d, x, y);
    if (d < 13) v += (13.0 - d) / sum * dp(a, b, c, d + 1, x, y);
    if (x == 4) {
        double t = INF;
        for (int i = 0; i < 4; i++) t = min(t, 1.0 / sum * dp(a, b, c, d, i, y));
        v += t;
    }
    if (y == 4) {
        double t = INF;
        for (int i = 0; i < 4; i++) t = min(t, 1.0 / sum * dp(a, b, c, d, x, i));
        v += t;
    }
    return v;
}
int main() {
    cin >> A >> B >> C >> D;
    memset(f, -1, sizeof f);
    double  t = dp(0, 0, 0, 0, 4, 4);
    if (t > INF / 2) t = -1;
    printf("%.3lf\n", t);
    return 0;
}