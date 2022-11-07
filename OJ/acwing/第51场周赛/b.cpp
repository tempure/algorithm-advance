#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1010, M = N * N;

int n, m;
int p[M], s[M];
char g[N][N];
int dx[4] = { -1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

int get(int x, int y)
{
    return x * m + y;
}

int find(int x)
{
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i ++ ) scanf("%s", g[i]);
    for (int i = 0; i < n * m; i ++ ) p[i] = i, s[i] = 1;

    for (int i = 0; i < n; i ++ )
        for (int j = 0; j < m; j ++ )
            if (g[i][j] == '.')
                for (int k = 0; k < 4; k ++ )
                {
                    int x = i + dx[k], y = j + dy[k];
                    if (x >= 0 && x < n && y >= 0 && y < m && g[x][y] == '.')
                    {
                        int a = get(i, j), b = get(x, y);
                        a = find(a), b = find(b);
                        if (a != b)
                        {
                            s[b] += s[a];
                            p[a] = b;
                        }
                    }
                }

    for (int i = 0; i < n; i ++ )
    {
        for (int j = 0; j < m; j ++ )
            if (g[i][j] == '.') printf(".");
            else
            {
                int fathers[4], cnt = 0;
                for (int k = 0; k < 4; k ++ )
                {
                    int x = i + dx[k], y = j + dy[k];
                    if (x >= 0 && x < n && y >= 0 && y < m && g[x][y] == '.')
                    {
                        int a = get(x, y);
                        fathers[cnt ++ ] = find(a);
                    }
                }

                int sum = 1;
                if (cnt)
                {
                    sort(fathers, fathers + cnt);
                    cnt = unique(fathers, fathers + cnt) - fathers;
                    for (int k = 0; k < cnt; k ++ )
                        sum += s[fathers[k]];
                }

                printf("%d", sum % 10);
            }
        puts("");
    }

    return 0;
}

// 作者：yxc
// 链接：https://www.acwing.com/activity/content/code/content/3460193/
// 来源：AcWing
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。