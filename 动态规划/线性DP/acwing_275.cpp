#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

//https://www.acwing.com/solution/content/3954/
//https://www.acwing.com/solution/content/12389/
//最优解一定不会在相同的格子相遇，相同直接跳过，不会更新答案

using namespace std;

const int N = 55;

int n, m;
int g[N][N];
int f[N * 2][N][N];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i ++ )
        for (int j = 1; j <= m; j ++ )
            scanf("%d", &g[i][j]);

    for (int k = 2; k <= n + m; k ++ )
        for (int i = max(1, k - m); i <= n && i < k; i ++ )
            for (int j = max(1, k - m); j <= n && j < k; j ++ )
                for (int a = 0; a <= 1; a ++ )
                    for (int b = 0; b <= 1; b ++ )
                    {
                        int t = g[i][k - i];
                        if (i != j || k == 2 || k == n + m)
                        {
                            t += g[j][k - j];
                            f[k][i][j] = max(f[k][i][j], f[k - 1][i - a][j - b] + t);
                        }
                    }

    printf("%d\n", f[n + m][n][n]);

    return 0;
}