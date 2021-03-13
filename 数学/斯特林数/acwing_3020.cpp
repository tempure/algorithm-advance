#include <bits/stdc++.h>
using namespace std;

/*
转化为第一类斯特林数

让最高的第n个作为中间的分界线，那么左边需要有a-1个部分，右边需要有b-1个部分
每个部分内部都是一个排列，但是分界线左边最高的在每部分的最左边，右边最高的在该部分的最右边
每部分最高的不变，其余的随意排列，假设该部分有a[i]个，那么该部分单独的排列方案为(a[i]-1)!
这恰好就是将n-1个数分成a+b-2个圆排列，在此基础上分为左右两块，再乘组合数c[a+b-2][a-1]即可
乘组合数，直观理解就是:对于每一种圆排列的分法，都要分为左右2块
*/

typedef long long ll;
const int N = 50010, M = 210, mod = 1e9 + 7;

int f[N][M], c[M][M]; //f[]斯特林数 c[]组合数

int main() {
    f[0][0] = 1;
    //斯特林数预处理
    for (int i = 1; i < N; i++)
        for (int j = 1; j < M; j++)
            f[i][j] = (f[i - 1][j - 1] + (ll)(i - 1) * f[i - 1][j]) % mod;

    //组合数预处理
    for (int i = 0; i < M; i++)
        for (int j = 0; j <= i; j++)
            if (!j) c[i][j] = 1;
            else c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;

    int T;
    scanf("%d", &T);
    while (T --) {
        int n, a, b;
        scanf("%d%d%d", &n, &a, &b);
        printf("%lld\n", (ll)f[n - 1][a + b - 2]*c[a + b - 2][a - 1] % mod);
    }

    return 0;
}