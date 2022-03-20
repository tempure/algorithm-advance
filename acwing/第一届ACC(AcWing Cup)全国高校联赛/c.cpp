#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 5010;

int n, m, k;
LL s[N], f[N][N];

//f[i][j] i是最后一个区间结尾，共选了j个区间的最优值

int main()
{
    scanf("%d%d%d", &n, &m, &k);

    for (int i = 1; i <= n; i ++ )
    {
        int x;
        scanf("%d", &x);
        s[i] = s[i - 1] + x;
    }

    memset(f, -0x3f, sizeof f);
    for (int i = 0; i <= n; i ++ ) f[i][0] = 0;

    for (int j = 1; j <= k; j ++ )
    {
        LL maxf = 0;
        for (int i = j * m; i <= n; i ++ )
        {
            maxf = max(maxf, f[i - m][j - 1] + s[i] - s[i - m]); //这个maxf直接线性更新最后加进来的就行了
            //因为随着i的增大，前面算过的j个区间就不用再算了，只需要和最后一个新加进来的区间比较大小就行了
            f[i][j] = maxf;
        }
    }

    LL res = 0;
    for (int i = 1; i <= n; i ++ )
        res = max(res, f[i][k]);

    printf("%lld\n", res);
    return 0;
}