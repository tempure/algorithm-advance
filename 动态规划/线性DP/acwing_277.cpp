#include <cstring>
#include <iostream>
#include <algorithm>

//https://www.acwing.com/solution/content/5240/
//https://www.acwing.com/video/428/
//https://www.acwing.com/video/1975/


/*
这个集合划分方案很少见，看蓝书的方法，我的理解就是，由于所有人减去1之后答案不变
那就直接把最后一个减到1，最后计算答案的时候再加回来减去的
这样减去1的目的，按照lyd的讲解，目的是为了降低复杂度，因为f[i][j] = f[i][j-i]可以直接递推
*/

using namespace std;

typedef pair<int, int> PII;

const int N = 31, M = 5010;

int n, m;
PII g[N];
int s[N];
int f[N][M];
int ans[N];

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i ++ )
    {
        cin >> g[i].first;
        g[i].second = i;
    }
    sort(g + 1, g + n + 1);
    reverse(g + 1, g + n + 1);

    for (int i = 1; i <= n; i ++ ) s[i] = s[i - 1] + g[i].first;

    memset(f, 0x3f, sizeof f);
    f[0][0] = 0;

    for (int i = 1; i <= n; i ++ )
        for (int j = 1; j <= m; j ++ )
        {
            if (j >= i) f[i][j] = f[i][j - i];
            for (int k = 1; k <= i && k <= j; k ++ )
                f[i][j] = min(f[i][j], f[i - k][j - k] + (s[i] - s[i - k]) * (i - k));
        }

    cout << f[n][m] << endl;

    int i = n, j = m, h = 0;
    while (i && j)
    {
        if (j >= i && f[i][j] == f[i][j - i]) j -= i, h ++ ;
        else
        {
            for (int k = 1; k <= i && k <= j; k ++ )
                if (f[i][j] == f[i - k][j - k] + (s[i] - s[i - k]) * (i - k))
                {
                    for (int u = i; u > i - k; u -- )
                        ans[g[u].second] = 1 + h;
                    i -= k, j -= k;
                    break;
                }

        }
    }

    for (int i = 1; i <= n; i ++ ) cout << ans[i] << ' ';
    cout << endl;

    return 0;
}