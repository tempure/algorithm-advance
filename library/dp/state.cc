/*
给定一张 n 个点的带权无向图，点从 0~n-1 标号，求起点 0 到终点 n-1 的最短Hamilton路径。 Hamilton路径的定义是从 0 到 n-1 不重不漏地经过每个点恰好一次。
输入格式:第一行输入整数n。
接下来n行每行n个整数，其中第i行第j个整数表示点i到j的距离（记为a[i,j]）。
对于任意的x,y,z，数据保证 a[x,x]=0，a[x,y]=a[y,x] 并且 a[x,y]+a[y,z]>=a[x,z]。
输出格式
输出一个整数，表示最短Hamilton路径的长度。
*/
const int N = 20, M = 1 << N ;
int w[N][N];
int f[M][N];  // f[i][j] 表示所有从0走到j 走过的所有点是二进制表示的i的路径
int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> w[i][j];
    memset(f, 0x3f, sizeof f);
    f[1][0] = 0; //最初是第0位 第0位的状态就是1
    for (int i = 0 ; i < 1 << n; i++)
        for (int j = 0; j < n; j++)
            if (i >> j & 1)
                for (int k = 0; k < n; k++) //枚举转移的点 也就是倒数第二个点
                    if ((i - (1 << j)) >> k & 1) //包含第k位
                        f[i][j] = min(f[i][j], f[i - (1 << j)][k] + w[k][j]);
    cout << f[(1 << n) - 1][n - 1] << endl;
    return 0;
}