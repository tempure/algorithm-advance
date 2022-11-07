#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 2010, INF = 1e8;

int n, m, X;
int s1[N], s2[N];
int a[N], b[N];

//a[i] 长度为i的最小区间和 b[]同理

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i ++ )
    {
        int x;
        scanf("%d", &x);
        s1[i] = s1[i - 1] + x;
    }

    for (int i = 1; i <= m; i ++ )
    {
        int x;
        scanf("%d", &x);
        s2[i] = s2[i - 1] + x;
    }

    for (int len = 1; len <= n; len ++ ) //预处理 O(N^2)
    {
        a[len] = INF;
        for (int i = 1; i + len - 1 <= n; i ++ )
        {
            int j = i + len - 1;
            a[len] = min(a[len], s1[j] - s1[i - 1]);
        }
    }

    for (int len = 1; len <= m; len ++ )
    {
        b[len] = INF;
        for (int i = 1; i + len - 1 <= m; i ++ )
        {
            int j = i + len - 1;
            b[len] = min(b[len], s2[j] - s2[i - 1]);
        }
    }

    scanf("%d", &X);

    int res = 0;
    for (int i = 1, j = m; i <= n; i ++ ) //枚举长度
    {
        while (j && b[j] > X / a[i]) j -- ;
        res = max(res, i * j);
    }

    printf("%d\n", res);
    return 0;
}