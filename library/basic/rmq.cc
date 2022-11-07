//一维 预处理O(n*logn) 查询O(1)
const int N = 2e5 + 10;
const int M = 18; //区间长度log2取对数
//如果求区间最小 那么init和query函数的max改为min即可
int n, m; int w[N];
int f[N][M]; //f[i][j]从i开始长度为2^j的区间最值
void init() { //预处理
    for (int j = 0; j < M; j++)
        for (int i = 1; i + (1 << j) - 1 <= n; i++) {
            if (!j) f[i][j] = w[i]; //只有一个数 最大就是本身
            else f[i][j] = max(f[i][j - 1], f[i + (1 << j - 1)][j - 1]);
        }
}
int query(int l, int r) {
    int len = r - l + 1;
    int k = log(len) / log(2);  //下取整<math.h>
    return max(f[l][k], f[r - (1 << k) + 1][k]);
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &w[i]);

    init(); //预处理ST
    scanf("%d", &m); //m组询问
    while (m --) {
        int l, r;
        scanf("%d%d", &l, &r);
        printf("%d\n", query(l, r));
    }
    return 0;
}
//二维：预处理n*m*log*(n)*log(m) 查询O(1)
int val[310][310];//矩阵
int dp[310][310][9][9];//最大值
int mm[310];//二进制位数减一，使用前初始化
void initRMQ(int n, int m) {
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            dp[i][j][0][0] = val[i][j];
    for (int ii = 0; ii <= mm[n]; ii++)
        for (int jj = 0; jj <= mm[m]; jj++)
            if (ii + jj)
                for (int i = 1; i + (1 << ii) - 1 <= n; i++)
                    for (int j = 1; j + (1 << jj) - 1 <= m; j++) {
                        if (ii)dp[i][j][ii][jj] = max(dp[i][j][ii][jj], dp[i + (1 << (ii - 1))][j][ii - 1][jj]);
                        else dp[i][j][ii][jj] = max(dp[i][j][ii][jj], dp[i][j + (1 << (jj - 1))][ii][jj - 1]);
                    }
}
//查询矩形内的最大值 (x1<=x2,y1<=y2)
int rmq(int x1, int y1, int x2, int y2) {
    int k1 = mm[x2 - x1 + 1];
    int k2 = mm[y2 - y1 + 1];
    x2 = x2 - (1 << k1) + 1;
    y2 = y2 - (1 << k2) + 1;
    return max(max(dp[x1][y1][k1][k2], dp[x1][y2][k1][k2]), max(dp[x2][y1][k1][k2], dp[x2][y2][k1][k2]));
}
int main() {
//在外面对 mm 数组进行初始化
    mm[0] = -1;
    for (int i = 1; i <= 305; i++)
        mm[i] = ((i & (i - 1)) == 0) ? mm[i - 1] + 1 : mm[i - 1];
    int n, m;
    int Q;
    int r1, c1, r2, c2;
    while (scanf("%d%d", &n, &m) == 2) {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                scanf("%d", &val[i][j]);
        initRMQ(n, m);
        scanf("%d", &Q);
        while (Q--) { //Q组查询
            scanf("%d%d%d%d", &r1, &c1, &r2, &c2);
            if (r1 > r2)swap(r1, r2);
            if (c1 > c2)swap(c1, c2);
            int tmp = rmq(r1, c1, r2, c2);
            printf("%d\n", tmp);
        }
    }
    return 0;
}