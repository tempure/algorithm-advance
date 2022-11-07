#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;


//https://www.acwing.com/video/1976/
//记录状态较多，要分类讨论，凸多边形状态切入

int f[16][226][16][16][2][2], a[16][16], b[16][16], n, m, t, i, j, k, l, r, x, y, p, q, ans, now, ai, al, ar, ax, ay;
char cl[16][226][16][16][2][2], cr[16][226][16][16][2][2], dx[16][226][16][16][2][2], dy[16][226][16][16][2][2];

inline void update(int dat, int L, int R, int X, int Y)
{
    if (dat < f[i][j][l][r][x][y]) return;
    f[i][j][l][r][x][y] = dat;
    cl[i][j][l][r][x][y] = L, cr[i][j][l][r][x][y] = R;
    dx[i][j][l][r][x][y] = X, dy[i][j][l][r][x][y] = Y;
}

void print(int i, int j, int l, int r, int x, int y)
{
    if (!j) return;
    print(i - 1, j - (r - l + 1), cl[i][j][l][r][x][y], cr[i][j][l][r][x][y], dx[i][j][l][r][x][y], dy[i][j][l][r][x][y]);
    for (j = l; j <= r; j++) printf("%d %d\n", i, j);
}

int main()
{
    cin >> n >> m >> t;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
        {
            scanf("%d", &a[i][j]);
            b[i][j] = b[i][j - 1] + a[i][j];
        }
    memset(f, 0xcf, sizeof(f));
    for (i = 1; i <= n; i++)
        for (j = 1; j <= t; j++)
            for (l = 1; l <= m; l++)
                for (r = l; r <= m; r++)
                {
                    if ((k = r - l + 1) > j) break;
                    now = b[i][r] - b[i][l - 1];
                    // 这一行是第一次选，获得now的收益，“上一行”没选，记为[m,0]表示不存在
                    // 左右边界增减情况任意，例如：整个图形是一个倒三角形，左右边界一直递减，没有递增过，也是凸的
                    for (x = 0; x < 2; x++)
                        for (y = 0; y < 2; y++) update(now, m, 0, x, y);
                    // 边界处于扩张状态，上次必须也是扩张
                    x = y = 1;
                    for (p = l; p <= r; p++)
                        for (q = p; q <= r; q++)
                            update(f[i - 1][j - k][p][q][1][1] + now, p, q, 1, 1);
                    // 边界处于收缩状态，上次可以是收缩，也可以是扩张（这次拐弯变为收缩）
                    x = y = 0;
                    for (p = 1; p <= l; p++)
                        for (q = r; q <= m; q++)
                        {
                            update(f[i - 1][j - k][p][q][0][0] + now, p, q, 0, 0);
                            update(f[i - 1][j - k][p][q][1][0] + now, p, q, 1, 0);
                            update(f[i - 1][j - k][p][q][0][1] + now, p, q, 0, 1);
                            update(f[i - 1][j - k][p][q][1][1] + now, p, q, 1, 1);
                        }
                    x = 1, y = 0;
                    for (p = l; p <= r; p++)
                        for (q = r; q <= m; q++)
                        {
                            update(f[i - 1][j - k][p][q][1][0] + now, p, q, 1, 0);
                            update(f[i - 1][j - k][p][q][1][1] + now, p, q, 1, 1);
                        }
                    x = 0, y = 1;
                    for (p = 1; p <= l; p++)
                        for (q = l; q <= r; q++)
                        {
                            update(f[i - 1][j - k][p][q][0][1] + now, p, q, 0, 1);
                            update(f[i - 1][j - k][p][q][1][1] + now, p, q, 1, 1);
                        }
                }
    for (i = 1; i <= n; i++)
        for (l = 1; l <= m; l++)
            for (r = l; r <= m; r++)
                for (x = 0; x < 2; x++)
                    for (y = 0; y < 2; y++)
                        if (ans < f[i][t][l][r][x][y])
                        {
                            ans = f[i][t][l][r][x][y];
                            ai = i, al = l, ar = r, ax = x, ay = y;
                        }
    cout << "Oil : " << ans << endl;
    print(ai, t, al, ar, ax, ay);
    return 0;
}